"""Cria personagem.blend: um estudante em blocos, com cada membro num objeto próprio e a origem na articulação que o jogo gira.

Uso: blender -b --factory-startup -P criar_personagem.py -- personagem.blend
O personagem olha para -Y (vista frontal do Blender) e pisa em z = 0.
Os nomes dos membros são lidos pelo jogo (main.js e jogo.c): renomeá-los quebra a animação.
"""
import sys
from pathlib import Path

sys.path.append(str(Path(__file__).parent))
from pecas import Peca, arquivo_depois_do_traco, cena_vazia, colecao, criar_objeto, material, salvar


def membro(nome, articulacao, pecas_no_mundo, destino):
    """Cria o membro com origem na articulação, recebendo as peças em coordenadas do mundo."""
    pecas_locais = [
        peca._replace(centro=tuple(c - a for c, a in zip(peca.centro, articulacao)))
        for peca in pecas_no_mundo
    ]
    objeto = criar_objeto(nome, articulacao, pecas_locais, destino)
    chanfro = objeto.modifiers.new("Chanfro", "BEVEL")
    chanfro.width = 0.012
    chanfro.segments = 2
    chanfro.limit_method = "ANGLE"


def main():
    destino_do_arquivo = arquivo_depois_do_traco()
    cena_vazia()
    destino = colecao("Personagem")

    pele = material("Pele", "#d8a47f")
    cabelo = material("Cabelo", "#3b2a1e")
    olhos = material("Olhos", "#1d1d1d")
    camisa = material("Camisa", "#2c5d8a")
    calca = material("Calca", "#34495e")
    tenis = material("Tenis", "#f5f5f5")
    mochila = material("Mochila", "#c0392b")

    membro("Tronco", (0, 0, 0.82), [
        Peca("caixa", (0, 0, 1.12), (0.44, 0.24, 0.56), camisa),
        Peca("caixa", (0, 0, 0.86), (0.42, 0.23, 0.1), calca),
        Peca("caixa", (0, 0.19, 1.12), (0.34, 0.14, 0.4), mochila),
    ], destino)

    membro("Cabeca", (0, 0, 1.40), [
        Peca("caixa", (0, 0, 1.44), (0.12, 0.12, 0.08), pele),
        Peca("caixa", (0, 0, 1.63), (0.3, 0.3, 0.3), pele),
        Peca("caixa", (0, 0.01, 1.79), (0.32, 0.32, 0.08), cabelo),
        Peca("caixa", (0, 0.13, 1.66), (0.32, 0.07, 0.22), cabelo),
        Peca("caixa", (-0.07, -0.151, 1.64), (0.05, 0.02, 0.05), olhos),
        Peca("caixa", (0.07, -0.151, 1.64), (0.05, 0.02, 0.05), olhos),
    ], destino)

    for nome, x in (("Braco_Esquerdo", 0.29), ("Braco_Direito", -0.29)):
        membro(nome, (x, 0, 1.36), [
            Peca("caixa", (x, 0, 1.27), (0.13, 0.15, 0.22), camisa),
            Peca("caixa", (x, 0, 0.99), (0.11, 0.13, 0.34), pele),
        ], destino)

    for nome, x in (("Perna_Esquerda", 0.1), ("Perna_Direita", -0.1)):
        membro(nome, (x, 0, 0.82), [
            Peca("caixa", (x, 0, 0.47), (0.17, 0.2, 0.72), calca),
            Peca("caixa", (x, -0.03, 0.055), (0.18, 0.27, 0.11), tenis),
        ], destino)

    salvar(destino_do_arquivo)


if __name__ == "__main__":
    main()
