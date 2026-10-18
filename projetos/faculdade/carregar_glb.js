// Lê um arquivo .glb exportado pelo Blender e devolve seus nós com matriz no mundo e malhas prontas para a GPU.

const ASSINATURA_GLB = 0x46546c67; // "glTF" em little-endian
const COMPONENTES_POR_TIPO = { SCALAR: 1, VEC2: 2, VEC3: 3, VEC4: 4 };
const ARRAY_POR_COMPONENTE = { 5121: Uint8Array, 5123: Uint16Array, 5125: Uint32Array, 5126: Float32Array };
const BRANCO = [1, 1, 1, 1];

export async function carregarGlb(url) {
  const resposta = await fetch(url, { cache: 'no-cache' });
  if (!resposta.ok) throw new Error(`Não foi possível carregar ${url} (HTTP ${resposta.status}).`);
  const { gltf, binario } = separarJsonEBinario(await resposta.arrayBuffer(), url);
  const cena = gltf.scenes[gltf.scene ?? 0];
  return cena.nodes.flatMap((indice) => listarNos(gltf, binario, indice, matrizIdentidade()));
}

function multiplicar(a, b) {
  const resultado = new Array(16).fill(0);
  for (let coluna = 0; coluna < 4; coluna++) {
    for (let linha = 0; linha < 4; linha++) {
      for (let k = 0; k < 4; k++) resultado[coluna * 4 + linha] += a[k * 4 + linha] * b[coluna * 4 + k];
    }
  }
  return resultado;
}

// Caixa alinhada aos eixos que envolve o nó no mundo, vista de cima (plano XZ).
export function caixaVistaDeCima(no) {
  const caixa = { xMin: Infinity, zMin: Infinity, xMax: -Infinity, zMax: -Infinity };
  for (const { minimo, maximo } of no.primitivas) {
    for (const x of [minimo[0], maximo[0]]) {
      for (const y of [minimo[1], maximo[1]]) {
        for (const z of [minimo[2], maximo[2]]) {
          const [mundoX, , mundoZ] = transformarPonto(no.matriz, [x, y, z]);
          caixa.xMin = Math.min(caixa.xMin, mundoX);
          caixa.xMax = Math.max(caixa.xMax, mundoX);
          caixa.zMin = Math.min(caixa.zMin, mundoZ);
          caixa.zMax = Math.max(caixa.zMax, mundoZ);
        }
      }
    }
  }
  return caixa;
}

export function posicaoNoMundo(no) {
  return { x: no.matriz[12], y: no.matriz[13], z: no.matriz[14] };
}

function separarJsonEBinario(arquivo, url) {
  const leitor = new DataView(arquivo);
  if (leitor.getUint32(0, true) !== ASSINATURA_GLB) throw new Error(`${url} não é um arquivo .glb.`);
  const tamanhoDoJson = leitor.getUint32(12, true);
  const gltf = JSON.parse(new TextDecoder().decode(new Uint8Array(arquivo, 20, tamanhoDoJson)));
  const inicioDoBinario = 20 + tamanhoDoJson + 8;
  const tamanhoDoBinario = leitor.getUint32(20 + tamanhoDoJson, true);
  return { gltf, binario: arquivo.slice(inicioDoBinario, inicioDoBinario + tamanhoDoBinario) };
}

function listarNos(gltf, binario, indice, matrizDoPai) {
  const no = gltf.nodes[indice];
  const matriz = multiplicar(matrizDoPai, matrizLocal(no));
  const primitivas = no.mesh === undefined ? [] : gltf.meshes[no.mesh].primitives.map((p) => lerPrimitiva(gltf, binario, p));
  const filhos = (no.children ?? []).flatMap((filho) => listarNos(gltf, binario, filho, matriz));
  return [{ nome: no.name ?? `no_${indice}`, matriz, primitivas }, ...filhos];
}

function lerPrimitiva(gltf, binario, primitiva) {
  const acessorDePosicao = gltf.accessors[primitiva.attributes.POSITION];
  const material = gltf.materials?.[primitiva.material];
  return {
    posicoes: lerAcessor(gltf, binario, primitiva.attributes.POSITION),
    normais: lerAcessor(gltf, binario, primitiva.attributes.NORMAL),
    indices: lerIndices(gltf, binario, primitiva.indices),
    cor: material?.pbrMetallicRoughness?.baseColorFactor ?? BRANCO,
    minimo: acessorDePosicao.min,
    maximo: acessorDePosicao.max,
  };
}

function lerAcessor(gltf, binario, indice) {
  const acessor = gltf.accessors[indice];
  const vista = gltf.bufferViews[acessor.bufferView];
  const TipoDeArray = ARRAY_POR_COMPONENTE[acessor.componentType];
  const componentes = COMPONENTES_POR_TIPO[acessor.type];
  if (vista.byteStride && vista.byteStride !== componentes * TipoDeArray.BYTES_PER_ELEMENT) {
    throw new Error('Vértices intercalados não são suportados; exporte o .glb pelo script exportar_glb.py.');
  }
  const inicio = (vista.byteOffset ?? 0) + (acessor.byteOffset ?? 0);
  return new TipoDeArray(binario, inicio, acessor.count * componentes);
}

// O WebGPU só aceita índices de 16 ou 32 bits.
function lerIndices(gltf, binario, indice) {
  const indices = lerAcessor(gltf, binario, indice);
  return indices instanceof Uint8Array ? Uint16Array.from(indices) : indices;
}

function matrizLocal(no) {
  if (no.matrix) return no.matrix;
  const [x, y, z, w] = no.rotation ?? [0, 0, 0, 1];
  const [escalaX, escalaY, escalaZ] = no.scale ?? [1, 1, 1];
  const [posicaoX, posicaoY, posicaoZ] = no.translation ?? [0, 0, 0];
  return [
    (1 - 2 * (y * y + z * z)) * escalaX, 2 * (x * y + z * w) * escalaX, 2 * (x * z - y * w) * escalaX, 0,
    2 * (x * y - z * w) * escalaY, (1 - 2 * (x * x + z * z)) * escalaY, 2 * (y * z + x * w) * escalaY, 0,
    2 * (x * z + y * w) * escalaZ, 2 * (y * z - x * w) * escalaZ, (1 - 2 * (x * x + y * y)) * escalaZ, 0,
    posicaoX, posicaoY, posicaoZ, 1,
  ];
}

function matrizIdentidade() {
  return [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1];
}

function transformarPonto(m, [x, y, z]) {
  return [
    m[0] * x + m[4] * y + m[8] * z + m[12],
    m[1] * x + m[5] * y + m[9] * z + m[13],
    m[2] * x + m[6] * y + m[10] * z + m[14],
  ];
}
