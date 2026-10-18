import { caixaVistaDeCima, carregarGlb, posicaoNoMundo } from './carregar_glb.js';
import { criarRenderizador } from './renderizador.js';

// Uma disciplina por sala, na ordem das salas; cada assunto é um livro do armário e aponta para a apresentação da aula, a partir da raiz do site.
const DISCIPLINAS_POR_SALA = [
  {
    nome: 'Algoritmos e Estruturas de Dados',
    assuntos: [
      { apresentacao: 'aula05_ponteiros_structs/apresentacao.html', titulo: 'Ponteiros e Structs', cor: '#c0392b' },
      { apresentacao: 'aula07_listas_pilhas_filas/apresentacao.html', titulo: 'Listas, Pilhas e Filas', cor: '#16a085' },
    ],
  },
  {
    nome: 'Programação Avançada',
    assuntos: [
      { apresentacao: 'programacao-avancada/aula-01/slides.html', titulo: 'Início do projeto e frameworks', cor: '#2980b9' },
      { apresentacao: 'programacao-avancada/aula-01.2/slides.html', titulo: 'Programação Orientada a Objetos com Python', cor: '#8e44ad' },
      { apresentacao: 'programacao-avancada/aula-01.3/slides.html', titulo: 'Concorrência, paralelismo e o modelo de execução do FastAPI', cor: '#d35400' },
      { apresentacao: 'programacao-avancada/aula-02/slides.html', titulo: 'Ciclo de vida de uma requisição', cor: '#27ae60' },
      { apresentacao: 'programacao-avancada/aula-03/slides.html', titulo: 'APIs REST e URIs', cor: '#f39c12' },
      { apresentacao: 'programacao-avancada/aula-04/slides.html', titulo: 'Banco de dados e ORMs', cor: '#7f8c8d' },
      { apresentacao: 'programacao-avancada/aula-05/slides.html', titulo: 'Users e autenticação com JWT', cor: '#2c3e50' },
      { apresentacao: 'programacao-avancada/aula-06/slides.html', titulo: 'Frontend com React e o consumo da API', cor: '#6c5ce7' },
    ],
  },
  { nome: 'Engenharia de IA', assuntos: [] },
];

// Mesma ordem do enum Parte em jogo.c.
const PARTES_DO_PERSONAGEM = ['Tronco', 'Cabeca', 'Braco_Esquerdo', 'Braco_Direito', 'Perna_Esquerda', 'Perna_Direita'];
const PREFIXOS_DE_OBSTACULO = ['Parede', 'Mesa', 'Cadeira', 'Armario', 'Banco', 'Planta'];
const ALCANCE_DA_MESA = 1.5;
const ALCANCE_DO_ARMARIO = 1.4;
const TECLAS_DE_DIRECAO = {
  KeyW: [0, -1], ArrowUp: [0, -1],
  KeyS: [0, 1], ArrowDown: [0, 1],
  KeyA: [-1, 0], ArrowLeft: [-1, 0],
  KeyD: [1, 0], ArrowRight: [1, 0],
};

const elementos = {
  tela: document.querySelector('#tela'),
  aviso: document.querySelector('#aviso'),
  dica: document.querySelector('#dica'),
  estante: document.querySelector('#estante'),
  tituloDaEstante: document.querySelector('#titulo-da-estante'),
  listaDeAssuntos: document.querySelector('#lista-de-assuntos'),
  livro: document.querySelector('#livro'),
  tituloDoLivro: document.querySelector('#titulo-do-livro'),
  apresentacao: document.querySelector('#apresentacao'),
};

async function iniciar() {
  const [jogo, faculdade, personagem, renderizador] = await Promise.all([
    carregarJogo('jogo.wasm'),
    carregarGlb('modelos/faculdade.glb'),
    carregarGlb('modelos/personagem.glb'),
    criarRenderizador(elementos.tela),
  ]);
  renderizador.perdido.then((motivo) => mostrarAviso(`A placa de vídeo foi desconectada (${motivo.message}). Recarregue a página.`));

  const objetosDoCenario = montarCenario(faculdade, jogo, renderizador);
  const salas = montarSalas(faculdade, objetosDoCenario);
  if (salas.length === 0) throw new Error('faculdade.glb não tem nenhum objeto Mesa_N.');
  salas.forEach(colocarLivroNaMesa);
  const acoes = registrarPontosDeInteracao(salas, jogo);
  const partes = montarPersonagem(personagem, jogo, renderizador);

  elementos.aviso.hidden = true;
  jogar({ jogo, renderizador, salas, acoes, partes });
}

async function carregarJogo(url) {
  const resposta = await fetch(url, { cache: 'no-cache' });
  if (!resposta.ok) throw new Error(`Não foi possível carregar ${url} (HTTP ${resposta.status}). Rode "make" na pasta game.`);
  const importacoes = { matematica: { sin: Math.sin, cos: Math.cos, atan2: Math.atan2 } };
  const { instance } = await WebAssembly.instantiateStreaming(resposta, importacoes);
  return instance.exports;
}

function matrizNaMemoria(jogo, endereco) {
  return new Float32Array(jogo.memory.buffer, endereco, 16);
}

function montarCenario(nos, jogo, renderizador) {
  const objetosPorNome = new Map();
  for (const no of nos) {
    objetosPorNome.set(no.nome, no.primitivas.map((primitiva) => renderizador.adicionarObjeto(primitiva, no.matriz)));
    if (!PREFIXOS_DE_OBSTACULO.some((prefixo) => no.nome.startsWith(prefixo))) continue;

    const caixa = caixaVistaDeCima(no);
    const coube = jogo.adicionar_obstaculo(caixa.xMin, caixa.zMin, caixa.xMax, caixa.zMax);
    if (!coube) throw new Error('Obstáculos demais para jogo.c; aumente MAX_OBSTACULOS.');
  }
  return objetosPorNome;
}

// Uma sala existe para cada Mesa_N do Blender, com Livro_Mesa_N, Cadeira_N e Armario_N de mesmo número.
function montarSalas(nos, objetosPorNome) {
  const nosPorNome = new Map(nos.map((no) => [no.nome, no]));
  const exigir = (nome) => {
    const no = nosPorNome.get(nome);
    if (!no) throw new Error(`faculdade.glb não tem o objeto ${nome}.`);
    return no;
  };

  return nos
    .map((no) => no.nome.match(/^Mesa_(\d+)$/)?.[1])
    .filter(Boolean)
    .map(Number)
    .toSorted((a, b) => a - b)
    .map((numero) => ({
      numero,
      disciplina: disciplinaDaSala(numero),
      livro: exigir(`Livro_Mesa_${numero}`),
      cadeira: exigir(`Cadeira_${numero}`),
      armario: exigir(`Armario_${numero}`),
      objetosDoLivro: objetosPorNome.get(`Livro_Mesa_${numero}`),
      indiceDoAssunto: 0,
    }));
}

function disciplinaDaSala(numero) {
  const disciplina = DISCIPLINAS_POR_SALA[numero - 1];
  if (!disciplina) throw new Error(`faculdade.glb tem a Sala ${numero}, mas DISCIPLINAS_POR_SALA não define a disciplina dela.`);
  return disciplina;
}

// Undefined quando a disciplina da sala ainda não tem conteúdos.
function assuntoAtual(sala) {
  return sala.disciplina.assuntos[sala.indiceDoAssunto];
}

function registrarPontosDeInteracao(salas, jogo) {
  const acoes = [];
  for (const sala of salas) {
    acoes[adicionarPontoDeInteracao(jogo, sala.livro, ALCANCE_DA_MESA)] = { tipo: 'mesa', sala };
    acoes[adicionarPontoDeInteracao(jogo, sala.armario, ALCANCE_DO_ARMARIO)] = { tipo: 'armario', sala };
  }
  return acoes;
}

function adicionarPontoDeInteracao(jogo, no, alcance) {
  const { x, z } = posicaoNoMundo(no);
  const indice = jogo.adicionar_ponto_de_interacao(x, z, alcance);
  if (indice < 0) throw new Error('Pontos de interação demais para jogo.c; aumente MAX_PONTOS_DE_INTERACAO.');
  return indice;
}

// Entrega ao WASM a pose de repouso de cada parte; ele devolve, a cada quadro, a matriz animada.
function montarPersonagem(nos, jogo, renderizador) {
  return PARTES_DO_PERSONAGEM.map((nomeDaParte, indice) => {
    const no = nos.find((candidato) => candidato.nome === nomeDaParte);
    if (!no) throw new Error(`personagem.glb não tem a parte ${nomeDaParte}.`);
    matrizNaMemoria(jogo, jogo.repouso_da_parte(indice)).set(no.matriz);
    return no.primitivas.map((primitiva) => renderizador.adicionarObjeto(primitiva, no.matriz));
  });
}

// O livro da mesa tem a cor do assunto atual; sem conteúdos na disciplina, a mesa fica vazia.
function colocarLivroNaMesa(sala) {
  const assunto = assuntoAtual(sala);
  sala.objetosDoLivro.forEach((objeto) => objeto.definirVisivel(assunto !== undefined));
  if (!assunto) return;

  const cor = [...corLinear(assunto.cor), 1];
  sala.objetosDoLivro.forEach((objeto) => objeto.definirCor(cor));
}

function jogar({ jogo, renderizador, salas, acoes, partes }) {
  const teclasPressionadas = new Set();
  let acaoNaDica;

  const algumaJanelaAberta = () => elementos.estante.open || elementos.livro.open;

  function interagir() {
    if (algumaJanelaAberta()) return;
    const acao = acoes[jogo.ponto_de_interacao_proximo()];
    if (!acao || !assuntoAtual(acao.sala)) return;
    teclasPressionadas.clear();
    if (acao.tipo === 'mesa') estudar(acao.sala);
    else abrirArmario(acao.sala);
  }

  function estudar(sala) {
    const assento = posicaoNoMundo(sala.cadeira);
    const livro = posicaoNoMundo(sala.livro);
    jogo.sentar(assento.x, assento.z, livro.x, livro.z);

    const assunto = assuntoAtual(sala);
    elementos.tituloDoLivro.textContent = `${sala.disciplina.nome} · ${assunto.titulo}`;
    elementos.apresentacao.src = `../${assunto.apresentacao}`;
    elementos.livro.showModal();
  }

  function abrirArmario(sala) {
    elementos.tituloDaEstante.textContent = `Armário · ${sala.disciplina.nome}`;
    const itens = sala.disciplina.assuntos.map((assunto, indice) =>
      criarItemDeAssunto(assunto, indice === sala.indiceDoAssunto, () => escolherAssunto(sala, indice)),
    );
    elementos.listaDeAssuntos.replaceChildren(...itens);
    elementos.estante.showModal();
  }

  function escolherAssunto(sala, indice) {
    sala.indiceDoAssunto = indice;
    colocarLivroNaMesa(sala);
    elementos.estante.close();
    estudar(sala);
  }

  function atualizarDica(acao) {
    if (acao === acaoNaDica) return;
    acaoNaDica = acao;
    elementos.dica.hidden = !acao;
    if (!acao) return;

    const { disciplina } = acao.sala;
    const assunto = assuntoAtual(acao.sala);
    elementos.dica.disabled = !assunto;
    if (!assunto) {
      elementos.dica.textContent = `${disciplina.nome}: ainda sem conteúdos`;
      return;
    }

    const texto = acao.tipo === 'mesa'
      ? ` Sentar e estudar: ${assunto.titulo}`
      : ` Escolher o assunto atual de ${disciplina.nome}`;
    const tecla = document.createElement('kbd');
    tecla.textContent = 'E';
    elementos.dica.replaceChildren(tecla, texto);
  }

  let instanteAnterior = performance.now();
  function desenharQuadro(instante) {
    const segundos = (instante - instanteAnterior) / 1000;
    instanteAnterior = instante;
    const [entradaX, entradaZ] = algumaJanelaAberta() ? [0, 0] : direcaoDasTeclas(teclasPressionadas);
    jogo.atualizar(segundos, entradaX, entradaZ, elementos.tela.clientWidth / elementos.tela.clientHeight);

    partes.forEach((objetos, indice) => {
      const matriz = matrizNaMemoria(jogo, jogo.matriz_da_parte(indice));
      objetos.forEach((objeto) => objeto.definirMatriz(matriz));
    });
    renderizador.desenhar(matrizNaMemoria(jogo, jogo.matriz_da_camera()));
    atualizarDica(algumaJanelaAberta() ? undefined : acoes[jogo.ponto_de_interacao_proximo()]);
    requestAnimationFrame(desenharQuadro);
  }

  window.addEventListener('keydown', (evento) => {
    if (algumaJanelaAberta()) return;
    if (Object.hasOwn(TECLAS_DE_DIRECAO, evento.code)) {
      evento.preventDefault();
      teclasPressionadas.add(evento.code);
    }
    if (evento.code === 'KeyE') interagir();
  });
  window.addEventListener('keyup', (evento) => teclasPressionadas.delete(evento.code));
  window.addEventListener('blur', () => teclasPressionadas.clear());
  elementos.dica.addEventListener('click', interagir);

  elementos.apresentacao.addEventListener('load', focarApresentacaoEFecharComEsc);
  elementos.livro.addEventListener('close', () => {
    jogo.levantar();
    elementos.apresentacao.src = 'about:blank';
  });

  requestAnimationFrame(desenharQuadro);
}

// Com o foco no iframe, as setas passam os slides; o Esc precisa ser ouvido lá dentro para fechar o livro.
function focarApresentacaoEFecharComEsc() {
  elementos.apresentacao.contentWindow.addEventListener('keydown', (evento) => {
    if (evento.key === 'Escape') elementos.livro.close();
  });
  elementos.apresentacao.focus();
}

function criarItemDeAssunto(assunto, ehOAtual, aoEscolher) {
  const botao = document.createElement('button');
  botao.type = 'button';
  botao.className = 'assunto';
  botao.textContent = assunto.titulo;
  botao.style.setProperty('--cor-do-livro', assunto.cor);
  botao.autofocus = ehOAtual;
  if (ehOAtual) botao.setAttribute('aria-current', 'true');
  botao.addEventListener('click', aoEscolher);

  const item = document.createElement('li');
  item.append(botao);
  return item;
}

function direcaoDasTeclas(teclas) {
  let x = 0;
  let z = 0;
  for (const tecla of teclas) {
    const [passoX, passoZ] = TECLAS_DE_DIRECAO[tecla];
    x += passoX;
    z += passoZ;
  }
  return [Math.sign(x), Math.sign(z)];
}

// Converte '#rrggbb' (sRGB) para cor linear, o espaço em que o shader faz a iluminação.
function corLinear(hexadecimal) {
  return [1, 3, 5].map((inicio) => {
    const canal = parseInt(hexadecimal.slice(inicio, inicio + 2), 16) / 255;
    return canal <= 0.04045 ? canal / 12.92 : ((canal + 0.055) / 1.055) ** 2.4;
  });
}

function mostrarAviso(mensagem) {
  elementos.aviso.textContent = mensagem;
  elementos.aviso.hidden = false;
}

iniciar().catch((erro) => {
  console.error(erro);
  mostrarAviso(erro.message);
});
