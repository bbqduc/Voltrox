#!BPY

"""
Name: 'Trolloexport'
Blender: 260
Group: 'Export'
Tooltip: 'Trollo format exporter!'
"""

bl_info = {
    "name": "Trollo format(.trollo)",
    "author": "Johannes Ylinen",
    "version": (2, 1, 3),
    "blender": (2, 6, 3),
    "location": "File > Export > Trollo (.trollo)",
    "description": "Export Trollo Model Format (.trollo)",
    "warning": "",
    "wiki_url": ""\
      "Scripts/Import-Export/Trollo_Exporter",
    "tracker_url": ""\
        "",
    "category": "Import-Export"}


import os
import bpy
from struct import *

def write_obj(filepath, context):
  out = open(filepath, 'wb')

  out.write(pack('I', 1337)) # TROLLO MAGIC NUMBER
  TEXTURED_CODE = 1
  out.write(pack('I', TEXTURED_CODE))

  objs = [Object for Object in context.scene.objects
          if Object.type in ('MESH') and Object.parent is None]
  mesh = objs[0].to_mesh(bpy.context.scene, True, "PREVIEW")
  uvcoords = mesh.uv_layers.active.data

  out.write(pack('I', len(mesh.vertices)))
  out.write(pack('I', len(mesh.polygons)))

  Vertices = []
  for Polygon in mesh.polygons:
      for Vertex in [uvcoords[Vertex] for Vertex in Polygon.loop_indices]:
        Vertices.append(tuple(Vertex.uv))

  for i in range(0, len(mesh.vertices)):
    out.write(pack('f',mesh.vertices[i].co.x))
    out.write(pack('f',mesh.vertices[i].co.y))
    out.write(pack('f',mesh.vertices[i].co.z))

    out.write(pack('f',mesh.vertices[i].normal.x))
    out.write(pack('f',mesh.vertices[i].normal.y))
    out.write(pack('f',mesh.vertices[i].normal.z))

    out.write(pack('f',Vertices[i][0]))
    out.write(pack('f',Vertices[i][1]))
  for polygon in mesh.polygons:
      out.write(pack('I',polygon.vertices[0]))
      out.write(pack('I',polygon.vertices[1]))
      out.write(pack('I',polygon.vertices[2]))
  
  out.close()


from bpy.props import StringProperty, EnumProperty, BoolProperty


class TrolloExporter(bpy.types.Operator):
    """Export to the Trollo model format (.trollo)"""

    bl_idname = "export.trollo"
    bl_label = "Export Trollo"

    filepath = StringProperty(subtype='FILE_PATH')

    ApplyModifiers = BoolProperty(
        name="Apply Modifiers",
        description="Apply object modifiers before export",
        default=True)

    def execute(self, context):
        #Append .x
        FilePath = bpy.path.ensure_ext(self.filepath, ".trollo")

        write_obj(FilePath, context)
        return {'FINISHED'}

    def invoke(self, context, event):
        if not self.filepath:
            self.filepath = bpy.path.ensure_ext(bpy.data.filepath, ".trollo")
        WindowManager = context.window_manager
        WindowManager.fileselect_add(self)
        return {"RUNNING_MODAL"}


def menu_func(self, context):
    self.layout.operator(TrolloExporter.bl_idname, text="Trollo (.trollo)")


def register():
    bpy.utils.register_module(__name__)

    bpy.types.INFO_MT_file_export.append(menu_func)


def unregister():
    bpy.utils.unregister_module(__name__)

    bpy.types.INFO_MT_file_export.remove(menu_func)


if __name__ == "__main__":
    register()
