"""Exporta a cena do .blend aberto para o .glb indicado depois de '--' (uso: blender -b arquivo.blend -P exportar_glb.py -- saida.glb)."""
import bpy

from os.path import abspath
from sys import argv

bpy.ops.export_scene.gltf(
    filepath=abspath(argv[argv.index("--") + 1]),
    export_format="GLB",
    export_yup=True,
    export_apply=True,
    export_texcoords=False,
    export_cameras=False,
    export_lights=False,
    export_animations=False,
)
