"""Cria faculdade.blend: um corredor com três salas; cada sala tem mesa, cadeira, quadro, armário com livros e um livro sobre a mesa.

Uso: blender -b --factory-startup -P criar_faculdade.py -- faculdade.blend
Coordenadas do Blender: Z para cima, norte em +Y. O corredor fica ao sul (y entre -1.6 e 1.6) e as salas ao norte (y entre 1.8 e 8.8).
A câmera do jogo olha do sul para o norte: por isso a parede sul é uma mureta baixa e a cadeira fica ao norte da mesa,
deixando o personagem sentado de frente para a câmera.
"""
import random
import sys
from pathlib import Path

import bpy

sys.path.append(str(Path(__file__).parent))
from pecas import Peca, arquivo_depois_do_traco, cena_vazia, colecao, criar_objeto, material, salvar

ALTURA_DA_PAREDE = 2.4
ALTURA_DA_MURETA = 1.0
ESPESSURA_DA_PAREDE = 0.2
CENTROS_DAS_SALAS = (-8.2, 0.0, 8.2)
MEIA_LARGURA_DA_PORTA = 0.8

CORES = {
    "Grama": "#7fa65a",
    "Piso_Corredor": "#d9dde2",
    "Faixa": "#2c5d8a",
    "Piso_Sala": "#c8a27c",
    "Parede": "#f3efe6",
    "Batente": "#2c5d8a",
    "Madeira": "#8b5a2b",
    "Madeira_Escura": "#5e3b1d",
    "Cadeira": "#5a7a9a",
    "Lousa": "#2f4f3a",
    "Capa_Livro": "#c0392b",
    "Vaso": "#b5651d",
    "Folhagem": "#3f7d3a",
    "Placa": "#2c5d8a",
}
CORES_DOS_LIVROS = ("#c0392b", "#2c5d8a", "#27ae60", "#8e44ad", "#d35400", "#f1c40f", "#16a085", "#34495e")


def cor(nome):
    return material(nome, CORES[nome])


def parede(nome, x_inicio, y_inicio, x_fim, y_fim, destino, altura=ALTURA_DA_PAREDE):
    """Parede alinhada a um eixo, medida pela linha central entre o ponto inicial e o final."""
    tamanho_x = abs(x_fim - x_inicio) or ESPESSURA_DA_PAREDE
    tamanho_y = abs(y_fim - y_inicio) or ESPESSURA_DA_PAREDE
    centro = ((x_inicio + x_fim) / 2, (y_inicio + y_fim) / 2, 0)
    criar_objeto(nome, centro, [Peca("caixa", (0, 0, altura / 2), (tamanho_x, tamanho_y, altura), cor("Parede"))], destino)


def parede_com_uma_porta_por_sala(y, x_inicio, x_fim, destino):
    inicio_do_trecho = x_inicio
    for numero, centro in enumerate(CENTROS_DAS_SALAS, start=1):
        parede(f"Parede_Corredor_{numero}", inicio_do_trecho, y, centro - MEIA_LARGURA_DA_PORTA, y, destino)
        inicio_do_trecho = centro + MEIA_LARGURA_DA_PORTA
    parede(f"Parede_Corredor_{len(CENTROS_DAS_SALAS) + 1}", inicio_do_trecho, y, x_fim, y, destino)


def texto_no_chao(nome, texto, origem, destino):
    """Escreve o texto como malha deitada no chão, legível pela câmera do jogo."""
    curva = bpy.data.curves.new(nome, "FONT")
    curva.body = texto
    curva.size = 0.45
    curva.align_x = "CENTER"
    curva.align_y = "CENTER"
    curva.extrude = 0.003
    temporario = bpy.data.objects.new(nome, curva)
    bpy.context.scene.collection.objects.link(temporario)
    malha = bpy.data.meshes.new_from_object(temporario.evaluated_get(bpy.context.evaluated_depsgraph_get()))
    bpy.data.objects.remove(temporario)
    bpy.data.curves.remove(curva)

    malha.materials.append(cor("Placa"))
    objeto = bpy.data.objects.new(nome, malha)
    objeto.location = origem
    destino.objects.link(objeto)


def criar_corredor():
    destino = colecao("Corredor")
    criar_objeto("Gramado", (0, 3.5, 0), [Peca("caixa", (0, 0, -0.07), (44, 30, 0.1), cor("Grama"))], destino)
    criar_objeto("Piso_Corredor", (0, 0, 0), [Peca("caixa", (0, 0, -0.05), (24.8, 3.6, 0.1), cor("Piso_Corredor"))], destino)
    criar_objeto("Faixa_Corredor", (0, 0, 0), [Peca("caixa", (0, 0, 0.005), (24.0, 0.4, 0.01), cor("Faixa"))], destino)

    parede("Parede_Sul", -12.4, -1.7, 12.4, -1.7, destino, altura=ALTURA_DA_MURETA)
    parede("Parede_Norte", -12.4, 8.9, 12.4, 8.9, destino)
    parede("Parede_Oeste", -12.3, -1.6, -12.3, 8.8, destino)
    parede("Parede_Leste", 12.3, -1.6, 12.3, 8.8, destino)
    parede("Parede_Entre_Salas_1", -4.1, 1.8, -4.1, 8.8, destino)
    parede("Parede_Entre_Salas_2", 4.1, 1.8, 4.1, 8.8, destino)
    parede_com_uma_porta_por_sala(1.7, -12.2, 12.2, destino)

    for numero, centro in enumerate(CENTROS_DAS_SALAS, start=1):
        assento = Peca("caixa", (0, 0, 0.45), (1.6, 0.45, 0.06), cor("Madeira"))
        pes = [Peca("caixa", (lado * 0.7, 0, 0.21), (0.06, 0.4, 0.42), cor("Madeira_Escura")) for lado in (-1, 1)]
        criar_objeto(f"Banco_{numero}", (centro, -1.3, 0), [assento, *pes], destino)

    for numero, x in enumerate((-11.6, 11.6), start=1):
        vaso = Peca("cilindro", (0, 0, 0.25), (0.5, 0.5, 0.5), cor("Vaso"))
        folhagem = Peca("esfera", (0, 0, 0.85), (0.9, 0.9, 0.9), cor("Folhagem"))
        criar_objeto(f"Planta_{numero}", (x, -1.05, 0), [vaso, folhagem], destino)


def pecas_do_armario(numero):
    """Estante de 1.6 m com quatro prateleiras cheias de livros, sorteados com a mesma semente a cada execução."""
    largura, profundidade, altura, tabua = 1.6, 0.4, 2.0, 0.03
    madeira = cor("Madeira_Escura")
    livros = [material(f"Livro_{indice}", hexadecimal) for indice, hexadecimal in enumerate(CORES_DOS_LIVROS, start=1)]
    alturas_das_tabuas = (tabua / 2, 0.5, 1.0, 1.5, altura - tabua / 2)

    pecas = [
        Peca("caixa", (0, profundidade / 2 - tabua / 2, altura / 2), (largura, tabua, altura), madeira),
        Peca("caixa", (-(largura / 2 - tabua / 2), 0, altura / 2), (tabua, profundidade, altura), madeira),
        Peca("caixa", (largura / 2 - tabua / 2, 0, altura / 2), (tabua, profundidade, altura), madeira),
    ]
    pecas += [Peca("caixa", (0, 0, z), (largura, profundidade, tabua), madeira) for z in alturas_das_tabuas]

    sorteio_fixo_da_sala = random.Random(numero)
    limite_direito = largura / 2 - tabua - 0.02
    for z_da_tabua in alturas_das_tabuas[:-1]:
        base = z_da_tabua + tabua / 2
        x = -limite_direito
        while True:
            espessura = sorteio_fixo_da_sala.uniform(0.05, 0.09)
            if x + espessura > limite_direito:
                break
            altura_do_livro = sorteio_fixo_da_sala.uniform(0.26, 0.40)
            capa = sorteio_fixo_da_sala.choice(livros)
            pecas.append(Peca("caixa", (x + espessura / 2, -0.04, base + altura_do_livro / 2), (espessura, 0.26, altura_do_livro), capa))
            vao = 0.08 if sorteio_fixo_da_sala.random() < 0.08 else 0.004
            x += espessura + vao
    return pecas


def pecas_dos_batentes():
    """Batentes que envolvem as pontas da parede e avançam no vão: uma face no mesmo plano da parede piscaria na tela."""
    largura, avanco_no_vao = 0.12, 0.02
    distancia_do_centro = MEIA_LARGURA_DA_PORTA - avanco_no_vao + largura / 2
    return [
        Peca("caixa", (lado * distancia_do_centro, 0, 1.23), (largura, 0.28, 2.46), cor("Batente"))
        for lado in (-1, 1)
    ]


def criar_sala(numero, centro):
    destino = colecao(f"Sala_{numero}")
    criar_objeto(f"Piso_Sala_{numero}", (centro, 5.3, 0), [Peca("caixa", (0, 0, -0.05), (8.0, 7.0, 0.1), cor("Piso_Sala"))], destino)
    criar_objeto(f"Batente_{numero}", (centro, 1.7, 0), pecas_dos_batentes(), destino)
    texto_no_chao(f"Placa_Sala_{numero}", f"SALA {numero}", (centro, 0.85, 0.004), destino)

    tampo = Peca("caixa", (0, 0, 0.73), (1.6, 0.8, 0.05), cor("Madeira"))
    pernas_da_mesa = [
        Peca("caixa", (lado_x * 0.74, lado_y * 0.34, 0.355), (0.06, 0.06, 0.71), cor("Madeira_Escura"))
        for lado_x in (-1, 1)
        for lado_y in (-1, 1)
    ]
    criar_objeto(f"Mesa_{numero}", (centro, 6.0, 0), [tampo, *pernas_da_mesa], destino)

    assento = Peca("caixa", (0, 0, 0.45), (0.46, 0.46, 0.05), cor("Cadeira"))
    encosto = Peca("caixa", (0, 0.21, 0.73), (0.46, 0.04, 0.5), cor("Cadeira"))
    pernas_da_cadeira = [
        Peca("caixa", (lado_x * 0.2, lado_y * 0.2, 0.215), (0.04, 0.04, 0.43), cor("Cadeira"))
        for lado_x in (-1, 1)
        for lado_y in (-1, 1)
    ]
    criar_objeto(f"Cadeira_{numero}", (centro, 6.75, 0), [assento, encosto, *pernas_da_cadeira], destino)

    livro = Peca("caixa", (0, 0, 0.025), (0.26, 0.34, 0.05), cor("Capa_Livro"))
    criar_objeto(f"Livro_Mesa_{numero}", (centro, 6.15, 0.755), [livro], destino)
    criar_objeto(f"Armario_{numero}", (centro + 2.95, 8.6, 0), pecas_do_armario(numero), destino)

    moldura = Peca("caixa", (0, 0, 1.45), (3.0, 0.04, 1.3), cor("Madeira"))
    lousa = Peca("caixa", (0, -0.02, 1.45), (2.88, 0.02, 1.18), cor("Lousa"))
    criar_objeto(f"Quadro_{numero}", (centro - 0.9, 8.78, 0), [moldura, lousa], destino)


def main():
    destino = arquivo_depois_do_traco()
    cena_vazia()
    criar_corredor()
    for numero, centro in enumerate(CENTROS_DAS_SALAS, start=1):
        criar_sala(numero, centro)
    salvar(destino)


if __name__ == "__main__":
    main()
