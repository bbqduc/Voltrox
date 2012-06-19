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

def write_obj(filepath, context):
  out = open(filepath, 'w')
  objs = [Object for Object in context.scene.objects
          if Object.type in ('MESH') and Object.parent is None]
  mesh = objs[0].to_mesh(bpy.context.scene, True, "PREVIEW")
  uvcoords = mesh.uv_layers.active.data

  Vertices = []
  for Polygon in mesh.polygons:
      for Vertex in [uvcoords[Vertex] for Vertex in Polygon.loop_indices]:
        Vertices.append(tuple(Vertex.uv))

  for i in range(0, len(mesh.vertices)):
    out.write( '%f %f %f\n' % (mesh.vertices[i].co.x, mesh.vertices[i].co.y, mesh.vertices[i].co.z) )
    out.write( '%f %f %f\n' % (mesh.vertices[i].normal.x, mesh.vertices[i].normal.y, mesh.vertices[i].normal.z) )
    out.write( '%f %f\n' % (Vertices[i][0], Vertices[i][1]))
  for polygon in mesh.polygons:
      out.write( '%d %d %d\n' %(polygon.vertices[0], polygon.vertices[1], polygon.vertices[2]))
  
#  for face in mesh.faces:
 #   out.write('f')
#
 #   for vert in face.v:
  #    out.write( ' %i' % (vert.index +1) )
   # out.write('\n')
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
