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

template <template <typename> class VolumeType, typename VoxelType>
class VoxelModel
{
public: 
	GLuint vertexBuffer, indexBuffer, VAO;
	void destroyBuffers();
	void setMesh(VolumeType<VoxelType>& volume);
	VoxelModel(VolumeType<VoxelType>& volume);
	PolyVox::SurfaceMesh<PolyVox::PositionMaterialNormal> mesh;
};

template <template <typename> class VolumeType, typename VoxelType>
VoxelModel<VolumeType, VoxelType>::VoxelModel(VolumeType<VoxelType>& volume)
	:vertexBuffer(GL_INVALID_VALUE),
	indexBuffer(GL_INVALID_VALUE),
	VAO(GL_INVALID_VALUE)
{
	setMesh(volume);
}

template <template <typename> class VolumeType, typename VoxelType>
void VoxelModel<VolumeType,VoxelType>::destroyBuffers()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	indexBuffer = vertexBuffer = GL_INVALID_VALUE;
}

template <template <typename> class VolumeType, typename VoxelType>
void VoxelModel<VolumeType, VoxelType>::setMesh(VolumeType<VoxelType>& volume)
{
	if(indexBuffer != GL_INVALID_VALUE || vertexBuffer != GL_INVALID_VALUE)
		destroyBuffers();
	if(VAO == GL_INVALID_VALUE)
		glGenVertexArrays(1, &VAO);

	PolyVox::CubicSurfaceExtractorWithNormals<VolumeType, VoxelType> surfaceExtractor(&volume, volume.getEnclosingRegion(), &mesh);
	surfaceExtractor.execute();
	std::cout << "Extracted mesh with " << mesh.getNoOfIndices() << "  " << mesh.getNoOfVertices() << '\n';			
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.getNoOfVertices()*sizeof(GLfloat)*6, 0, GL_STATIC_DRAW);

	using PolyVox::Vector3DFloat;
	GLfloat* ptr = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	for(auto i = mesh.getVertices().begin(); i != mesh.getVertices().end(); ++i)
	{
		const Vector3DFloat t = i->getPosition() + static_cast<Vector3DFloat>(mesh.m_Region.getLowerCorner());
		*ptr++ = t.getX();
		*ptr++ = t.getY();
		*ptr++ = t.getZ();
		
		*ptr++ = i->getNormal().getX();
		*ptr++ = i->getNormal().getY();
		*ptr++ = i->getNormal().getZ();
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(GLfloat)*6, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(GLfloat)*6, (GLvoid*)12);
	
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndices().size()*sizeof(GLuint), &mesh.getIndices()[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);
}
