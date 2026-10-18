"""Funções comuns aos scripts que criam os arquivos .blend do jogo."""
import sys
from pathlib import Path
from typing import NamedTuple

import bmesh
import bpy
from mathutils import Matrix, Vector


class Peca(NamedTuple):
    """Um bloco de um objeto: forma ('caixa', 'cilindro' ou 'esfera'), centro relativo à origem, tamanho e material."""
    forma: str
    centro: tuple[float, float, float]
    tamanho: tuple[float, float, float]
    material: bpy.types.Material


def arquivo_depois_do_traco() -> Path:
    return Path(sys.argv[sys.argv.index("--") + 1]).resolve()


def cena_vazia() -> None:
    bpy.ops.wm.read_factory_settings(use_empty=True)


def salvar(destino: Path) -> None:
    bpy.ops.wm.save_as_mainfile(filepath=str(destino))


def cor_linear(hexadecimal: str) -> list[float]:
    """Converte '#rrggbb' (sRGB, como no seletor de cores) para o espaço linear usado pelo Blender."""
    canais = [int(hexadecimal[i:i + 2], 16) / 255 for i in (1, 3, 5)]
    return [c / 12.92 if c <= 0.04045 else ((c + 0.055) / 1.055) ** 2.4 for c in canais]


def material(nome: str, hexadecimal: str) -> bpy.types.Material:
    existente = bpy.data.materials.get(nome)
    if existente:
        return existente
    novo = bpy.data.materials.new(nome)
    cor = (*cor_linear(hexadecimal), 1.0)
    principled = novo.node_tree.nodes["Principled BSDF"]
    principled.inputs["Base Color"].default_value = cor
    principled.inputs["Roughness"].default_value = 0.8
    novo.diffuse_color = cor
    return novo


def colecao(nome: str) -> bpy.types.Collection:
    existente = bpy.data.collections.get(nome)
    if existente:
        return existente
    nova = bpy.data.collections.new(nome)
    bpy.context.scene.collection.children.link(nova)
    return nova


def _vertices_da_forma(malha_editavel: bmesh.types.BMesh, forma: str, transformacao: Matrix) -> list:
    match forma:
        case "caixa":
            return bmesh.ops.create_cube(malha_editavel, size=1.0, matrix=transformacao)["verts"]
        case "cilindro":
            return bmesh.ops.create_cone(
                malha_editavel, cap_ends=True, segments=16, radius1=0.5, radius2=0.5, depth=1.0, matrix=transformacao
            )["verts"]
        case "esfera":
            return bmesh.ops.create_icosphere(malha_editavel, subdivisions=2, radius=0.5, matrix=transformacao)["verts"]
    raise ValueError(f"forma desconhecida: {forma}")


def criar_objeto(nome: str, origem: tuple, pecas: list[Peca], destino: bpy.types.Collection) -> bpy.types.Object:
    """Junta as peças numa única malha, com uma cor por peça e a origem do objeto em `origem`."""
    malha = bpy.data.meshes.new(nome)
    malha_editavel = bmesh.new()
    for peca in pecas:
        if peca.material.name not in malha.materials:
            malha.materials.append(peca.material)
        indice_material = list(malha.materials).index(peca.material)
        transformacao = Matrix.Translation(Vector(peca.centro)) @ Matrix.Diagonal((*peca.tamanho, 1.0))
        vertices = _vertices_da_forma(malha_editavel, peca.forma, transformacao)
        for face in {face for vertice in vertices for face in vertice.link_faces}:
            face.material_index = indice_material
    malha_editavel.to_mesh(malha)
    malha_editavel.free()

    objeto = bpy.data.objects.new(nome, malha)
    objeto.location = origem
    destino.objects.link(objeto)
    return objeto
