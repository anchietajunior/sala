BLENDER ?= /Applications/Blender.app/Contents/MacOS/Blender
# clang precisa do linker wasm-ld (macOS: brew install lld)
CC = clang
# Slides da sala 2: a pasta slides/ do projeto de Programação Avançada, com o reveal.js vendorado que eles usam.
SLIDES_DE_PROGRAMACAO_AVANCADA ?= ../../../progavancada/projeto/slides

all: jogo.wasm modelos/faculdade.glb modelos/personagem.glb

jogo.wasm: jogo.c
	$(CC) --target=wasm32 -O2 -Wall -Wextra -nostdlib -Wl,--no-entry -o $@ $<

modelos/%.glb: blender/%.blend blender/exportar_glb.py
	@mkdir -p modelos
	$(BLENDER) -b $< -P blender/exportar_glb.py -- $@

# Recria os .blend a partir dos scripts, DESCARTANDO o que foi editado à mão no Blender.
recriar-blend:
	$(BLENDER) -b --factory-startup -P blender/criar_faculdade.py -- blender/faculdade.blend
	$(BLENDER) -b --factory-startup -P blender/criar_personagem.py -- blender/personagem.blend

teste: jogo.wasm
	node teste_jogo.mjs

# Serve a raiz do repositório para que o jogo alcance ../aulaNN_*/apresentacao.html.
servir: all
	cd .. && python3 -m http.server 8000

# Monta o que vai para o ar: o jogo na raiz e, de cada aula, só a apresentação e suas imagens (nada de .md, .c ou gabaritos);
# os slides de Programação Avançada vão para dist/programacao-avancada, sem as fontes .svg dos diagramas.
dist: all
	rm -rf dist
	mkdir -p dist/modelos
	cp index.html main.js carregar_glb.js renderizador.js jogo.wasm dist/
	cp modelos/*.glb dist/modelos/
	rsync -a --exclude .DS_Store ../assets/ dist/assets/
	for apresentacao in ../aula*/apresentacao.html; do \
		aula=$$(basename $$(dirname $$apresentacao)); \
		mkdir -p dist/$$aula; \
		cp $$apresentacao dist/$$aula/; \
		if [ -d ../$$aula/img ]; then rsync -a --exclude .DS_Store ../$$aula/img dist/$$aula/; fi; \
	done
	rsync -a --exclude .DS_Store --exclude '*.svg' $(SLIDES_DE_PROGRAMACAO_AVANCADA)/ dist/programacao-avancada/

deploy: dist
	npx -y wrangler@4 deploy

.PHONY: all recriar-blend teste servir dist deploy
