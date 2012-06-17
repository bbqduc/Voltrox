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
	GLuint vertexBuffer, indexBuffer, VAO;
	void destroyBuffers();
	void setMesh(PolyVox::SimpleVolume<T>& volume);
	VoxelModel(PolyVox::SimpleVolume<T>& volume);
	PolyVox::SurfaceMesh<PolyVox::PositionMaterialNormal> mesh;
};

template <typename T>
VoxelModel<T>::VoxelModel(PolyVox::SimpleVolume<T>& volume)
	:vertexBuffer(GL_INVALID_VALUE),
	indexBuffer(GL_INVALID_VALUE),
	VAO(GL_INVALID_VALUE)
{
	setMesh(volume);
}

template <typename T>
void VoxelModel<T>::destroyBuffers()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	indexBuffer = vertexBuffer = GL_INVALID_VALUE;
}

template <typename T>
void VoxelModel<T>::setMesh(PolyVox::SimpleVolume<T>& volume)
{
	if(indexBuffer != GL_INVALID_VALUE || vertexBuffer != GL_INVALID_VALUE)
		destroyBuffers();
	if(VAO == GL_INVALID_VALUE)
		glGenVertexArrays(1, &VAO);

	PolyVox::CubicSurfaceExtractorWithNormals<PolyVox::SimpleVolume, T> surfaceExtractor(&volume, volume.getEnclosingRegion(), &mesh);
	surfaceExtractor.execute();
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.getVertices().size()*sizeof(T), &mesh.getVertices()[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(PolyVox::PositionMaterialNormal), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(PolyVox::PositionMaterialNormal), (GLvoid*)12);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndices().size()*sizeof(GLuint), &mesh.getIndices()[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);
}