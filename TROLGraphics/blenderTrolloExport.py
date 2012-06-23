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


from array import array
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

  activeUV = mesh.tessface_uv_textures.active.data

  lvdic = {}
  lfl = []
  lvcnt = 0
  vertexdata = array('f')

  for i, f in enumerate(mesh.tessfaces):
    tmpfaces = []
    for j,v in enumerate(f.vertices):
      vec = mesh.vertices[v].co.to_tuple()
      nor = mesh.vertices[v].normal.to_tuple()
      co = tuple(activeUV[i].uv[j])
      key = vec, nor, co
      vinx = lvdic.get(key)

      if (vinx is None):
        lvdic[key] = lvcnt
        tmpfaces.append(lvcnt)
        lvcnt+=1
        for t in range(0,3):
                vertexdata.append(vec[t]);
        for t in range(0,3):
                vertexdata.append(nor[t]);
        for t in range(0,2):
                vertexdata.append(co[t]);
      else:
        inx = lvdic[key]
        tmpfaces.append(inx)

    lfl.append(tmpfaces)

  out.write(pack('I', lvcnt))
  out.write(pack('I', len(mesh.polygons)))

  vertexdata.tofile(out)
  
  for i in lfl:
          for j in i:
                  out.write(pack('I', j))
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
