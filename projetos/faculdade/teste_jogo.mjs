// Verifica a lógica de jogo.wasm sem navegador: colisão, deslize na parede, interação e sentar/levantar (uso: node teste_jogo.mjs).
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';

const PERNA_ESQUERDA = 4;
const QUADRO = 1 / 60;

async function carregarJogo() {
  const binario = await readFile(new URL('jogo.wasm', import.meta.url));
  const { instance } = await WebAssembly.instantiate(binario, { matematica: { sin: Math.sin, cos: Math.cos, atan2: Math.atan2 } });
  const jogo = instance.exports;
  const matriz = (endereco) => new Float32Array(jogo.memory.buffer, endereco, 16);
  for (let parte = 0; parte < 6; parte++) {
    matriz(jogo.repouso_da_parte(parte)).set([1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0.82, 0, 1]);
  }
  const posicao = () => {
    const perna = matriz(jogo.matriz_da_parte(PERNA_ESQUERDA));
    return { x: perna[12], y: perna[13], z: perna[14], frenteDaPerna: [perna[4], perna[5], perna[6]] };
  };
  const andar = (x, z, segundos) => {
    for (let t = 0; t < segundos; t += QUADRO) jogo.atualizar(QUADRO, x, z, 16 / 9);
  };
  return { jogo, posicao, andar };
}

const { jogo, posicao, andar } = await carregarJogo();

jogo.adicionar_obstaculo(-1, -3, 1, -2);
andar(0, -1, 2);
assert.ok(Math.abs(posicao().z - -1.7) < 0.07, `para antes da parede (raio 0.3): z = ${posicao().z}`);

andar(1, -1, 0.5);
assert.ok(posicao().x > 1, 'na diagonal, desliza rente à parede em vez de travar');
assert.ok(posicao().z > -1.8, 'mesmo deslizando, não atravessa a parede');

const mesa = jogo.adicionar_ponto_de_interacao(posicao().x, posicao().z - 1, 1.5);
const longe = jogo.adicionar_ponto_de_interacao(50, 50, 1.5);
assert.equal(jogo.ponto_de_interacao_proximo(), mesa, 'encontra o ponto dentro do alcance');
assert.notEqual(jogo.ponto_de_interacao_proximo(), longe);

const antesDeSentar = posicao();
jogo.sentar(5, 5, 5, 4);
andar(1, 0, 0.5);
assert.deepEqual([posicao().x, posicao().z], [5, 5], 'sentado, as teclas não movem o personagem');
assert.ok(Math.abs(posicao().y - 0.5) < 1e-5, 'o quadril desce até o assento');
assert.ok(posicao().frenteDaPerna[2] > 0.99, 'as pernas ficam na horizontal, apontando para a mesa (-z)');

jogo.levantar();
andar(0, 0, QUADRO);
assert.ok(Math.abs(posicao().x - antesDeSentar.x) < 1e-5, 'ao levantar, volta para onde estava');

console.log('jogo.wasm: tudo certo');
