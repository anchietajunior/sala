// Desenha as malhas com WebGPU: luz do sol, luz ambiente do céu e antisserrilhado de 4 amostras.

const AMOSTRAS_POR_PIXEL = 4;
const COR_DE_FUNDO = { r: 0.09, g: 0.12, b: 0.16, a: 1 };
const BYTES_DO_OBJETO = 80; // matriz 4x4 (64 bytes) + cor RGBA (16 bytes)

const SHADER = /* wgsl */ `
struct Objeto {
  modelo: mat4x4f,
  cor: vec4f,
};

@group(0) @binding(0) var<uniform> vistaProjecao: mat4x4f;
@group(1) @binding(0) var<uniform> objeto: Objeto;

struct Saida {
  @builtin(position) posicao: vec4f,
  @location(0) normal: vec3f,
};

@vertex
fn vertice(@location(0) posicao: vec3f, @location(1) normal: vec3f) -> Saida {
  var saida: Saida;
  saida.posicao = vistaProjecao * objeto.modelo * vec4f(posicao, 1.0);
  saida.normal = (objeto.modelo * vec4f(normal, 0.0)).xyz;
  return saida;
}

@fragment
fn fragmento(@location(0) normal: vec3f) -> @location(0) vec4f {
  let n = normalize(normal);
  let sol = max(dot(n, normalize(vec3f(0.4, 1.0, 0.5))), 0.0);
  let ceu = 0.45 + 0.2 * n.y;
  let corLinear = objeto.cor.rgb * (ceu + 0.6 * sol);
  let corEmSrgb = pow(corLinear, vec3f(1.0 / 2.2));
  return vec4f(corEmSrgb, 1.0);
}
`;

export async function criarRenderizador(canvas) {
  if (!navigator.gpu) throw new Error('Este navegador não tem WebGPU. Use uma versão recente do Chrome, Edge ou Safari.');
  const adaptador = await navigator.gpu.requestAdapter();
  if (!adaptador) throw new Error('Nenhuma placa de vídeo compatível com WebGPU foi encontrada.');
  const dispositivo = await adaptador.requestDevice();

  const contexto = canvas.getContext('webgpu');
  const formato = navigator.gpu.getPreferredCanvasFormat();
  contexto.configure({ device: dispositivo, format: formato, alphaMode: 'opaque' });

  const modulo = dispositivo.createShaderModule({ code: SHADER });
  const pipeline = dispositivo.createRenderPipeline({
    layout: 'auto',
    vertex: {
      module: modulo,
      entryPoint: 'vertice',
      buffers: [
        { arrayStride: 12, attributes: [{ shaderLocation: 0, offset: 0, format: 'float32x3' }] },
        { arrayStride: 12, attributes: [{ shaderLocation: 1, offset: 0, format: 'float32x3' }] },
      ],
    },
    fragment: { module: modulo, entryPoint: 'fragmento', targets: [{ format: formato }] },
    primitive: { topology: 'triangle-list', cullMode: 'none' },
    depthStencil: { format: 'depth24plus', depthWriteEnabled: true, depthCompare: 'less' },
    multisample: { count: AMOSTRAS_POR_PIXEL },
  });

  const bufferDaCamera = dispositivo.createBuffer({ size: 64, usage: GPUBufferUsage.UNIFORM | GPUBufferUsage.COPY_DST });
  const grupoDaCamera = dispositivo.createBindGroup({
    layout: pipeline.getBindGroupLayout(0),
    entries: [{ binding: 0, resource: { buffer: bufferDaCamera } }],
  });

  const objetos = [];
  let texturasDeDesenho = null;

  function adicionarObjeto(primitiva, matriz) {
    const dadosDoObjeto = new Float32Array(BYTES_DO_OBJETO / 4);
    dadosDoObjeto.set(matriz, 0);
    dadosDoObjeto.set(primitiva.cor, 16);
    const bufferDoObjeto = dispositivo.createBuffer({ size: BYTES_DO_OBJETO, usage: GPUBufferUsage.UNIFORM | GPUBufferUsage.COPY_DST });
    const enviarParaGpu = () => dispositivo.queue.writeBuffer(bufferDoObjeto, 0, dadosDoObjeto);
    enviarParaGpu();

    const objeto = {
      visivel: true,
      vertices: criarBufferComDados(dispositivo, primitiva.posicoes, GPUBufferUsage.VERTEX),
      normais: criarBufferComDados(dispositivo, primitiva.normais, GPUBufferUsage.VERTEX),
      indices: criarBufferComDados(dispositivo, primitiva.indices, GPUBufferUsage.INDEX),
      formatoDosIndices: primitiva.indices instanceof Uint32Array ? 'uint32' : 'uint16',
      totalDeIndices: primitiva.indices.length,
      grupo: dispositivo.createBindGroup({
        layout: pipeline.getBindGroupLayout(1),
        entries: [{ binding: 0, resource: { buffer: bufferDoObjeto } }],
      }),
    };
    objetos.push(objeto);

    return {
      definirMatriz(novaMatriz) {
        dadosDoObjeto.set(novaMatriz, 0);
        enviarParaGpu();
      },
      definirCor(novaCor) {
        dadosDoObjeto.set(novaCor, 16);
        enviarParaGpu();
      },
      definirVisivel(visivel) {
        objeto.visivel = visivel;
      },
    };
  }

  function ajustarAoTamanhoDaTela() {
    const largura = Math.max(1, Math.round(canvas.clientWidth * devicePixelRatio));
    const altura = Math.max(1, Math.round(canvas.clientHeight * devicePixelRatio));
    if (texturasDeDesenho && canvas.width === largura && canvas.height === altura) return;

    canvas.width = largura;
    canvas.height = altura;
    texturasDeDesenho?.cor.destroy();
    texturasDeDesenho?.profundidade.destroy();
    const descricao = { size: [largura, altura], sampleCount: AMOSTRAS_POR_PIXEL, usage: GPUTextureUsage.RENDER_ATTACHMENT };
    texturasDeDesenho = {
      cor: dispositivo.createTexture({ ...descricao, format: formato }),
      profundidade: dispositivo.createTexture({ ...descricao, format: 'depth24plus' }),
    };
  }

  function desenhar(matrizDaCamera) {
    ajustarAoTamanhoDaTela();
    dispositivo.queue.writeBuffer(bufferDaCamera, 0, matrizDaCamera);

    const codificador = dispositivo.createCommandEncoder();
    const passo = codificador.beginRenderPass({
      colorAttachments: [{
        view: texturasDeDesenho.cor.createView(),
        resolveTarget: contexto.getCurrentTexture().createView(),
        clearValue: COR_DE_FUNDO,
        loadOp: 'clear',
        storeOp: 'discard',
      }],
      depthStencilAttachment: {
        view: texturasDeDesenho.profundidade.createView(),
        depthClearValue: 1,
        depthLoadOp: 'clear',
        depthStoreOp: 'discard',
      },
    });
    passo.setPipeline(pipeline);
    passo.setBindGroup(0, grupoDaCamera);
    for (const objeto of objetos.filter((candidato) => candidato.visivel)) {
      passo.setBindGroup(1, objeto.grupo);
      passo.setVertexBuffer(0, objeto.vertices);
      passo.setVertexBuffer(1, objeto.normais);
      passo.setIndexBuffer(objeto.indices, objeto.formatoDosIndices);
      passo.drawIndexed(objeto.totalDeIndices);
    }
    passo.end();
    dispositivo.queue.submit([codificador.finish()]);
  }

  return { adicionarObjeto, desenhar, perdido: dispositivo.lost };
}

// O WebGPU exige buffers com tamanho múltiplo de 4 bytes; uma quantidade ímpar de índices de 16 bits precisa de folga.
function criarBufferComDados(dispositivo, dados, uso) {
  const buffer = dispositivo.createBuffer({ size: Math.ceil(dados.byteLength / 4) * 4, usage: uso, mappedAtCreation: true });
  new dados.constructor(buffer.getMappedRange()).set(dados);
  buffer.unmap();
  return buffer;
}
