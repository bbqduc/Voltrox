#pragma once

#ifdef TROL_USE_OLD_OPENGL
#include <GL/glew.h>
#else
#include <GL3/gl3w.h>
#endif

#include <string>
#include <stdint.h>
#include <glm/glm.hpp>

#include <PolyVoxCore/MaterialDensityPair.h>
#include <PolyVoxCore/CubicSurfaceExtractorWithNormals.h>
#include <PolyVoxCore/SurfaceMesh.h>
#include <PolyVoxCore/SimpleVolume.h>

template <typename T>
class VoxelModel
{
public: 
	GLuint vertexBuffer, indexBuffer;
	void destroyBuffers();
	setMesh(const PolyVox::BaseVolume<T>& volume);
	VoxelModel(const PolyVox::BaseVolume<T>& volume);

	GLint drawMode;
	GLuint texture;
	GLuint VBO_vertices_id, VBO_normals_id, VBO_indices_id, VBO_color_id, VBO_texcoord_id, VAO_id;

	void calculate_normals();
	void InitVBOs();
	void Init_Texture(const std::string& texturepath);



};