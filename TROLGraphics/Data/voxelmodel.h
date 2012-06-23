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
#include <PolyVoxCore/SurfaceExtractor.h>
#include <PolyVoxCore/SimpleVolume.h>
#include <PolyVoxCore/MeshDecimator.h>
#include <glm/gtc/matrix_transform.hpp>

template <template <typename> class VolumeType, typename VoxelType>
class VoxelModel
{
	public: 
		PolyVox::SurfaceMesh<PolyVox::PositionMaterialNormal> mesh;
		GLuint vertexBuffer, indexBuffer, VAO;


		VoxelModel()
			:vertexBuffer(GL_INVALID_VALUE),
			indexBuffer(GL_INVALID_VALUE),
			VAO(GL_INVALID_VALUE)
	{
	}

		void destroyBuffers()
		{
			glDeleteBuffers(1, &vertexBuffer);
			glDeleteBuffers(1, &indexBuffer);
			indexBuffer = vertexBuffer = GL_INVALID_VALUE;
		}

		void initBuffers()
		{
			if(indexBuffer != GL_INVALID_VALUE || vertexBuffer != GL_INVALID_VALUE)
				destroyBuffers();
			if(VAO == GL_INVALID_VALUE)
				glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, mesh.getNoOfVertices()*sizeof(GLfloat)*9, 0, GL_STATIC_DRAW);

			using PolyVox::Vector3DFloat;
			GLfloat* ptr = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			for(auto i = mesh.getVertices().begin(); i != mesh.getVertices().end(); ++i)
			{
				const Vector3DFloat t = i->getPosition() + static_cast<Vector3DFloat>(mesh.m_Region.getLowerCorner());
				*ptr++ = t.getX();
				*ptr++ = t.getY();
				*ptr++ = t.getZ();

				*ptr++ = i->getNormal().getX();
				*ptr++ = i->getNormal().getY();
				*ptr++ = i->getNormal().getZ();

				glm::vec3 c = convertMaterialIDToColour(i->getMaterial()*.5);
				*ptr++ = c.x;
				*ptr++ = c.y;
				*ptr++ = c.z;

			}
			glUnmapBuffer(GL_ARRAY_BUFFER);

			glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(GLfloat)*9, 0);
			glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(GLfloat)*9, (GLvoid*)12);
			glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(GLfloat)*9, (GLvoid*)24);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glGenBuffers(1, &indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndices().size()*sizeof(GLuint), &mesh.getIndices()[0], GL_STATIC_DRAW);

			glBindVertexArray(0);
		}

		void decimateMesh(float edgeCollapseThreshold=0.95f)
		{
			PolyVox::SurfaceMesh<PolyVox::PositionMaterialNormal> temp(mesh);
			PolyVox::MeshDecimator<PolyVox::PositionMaterialNormal> decim(&temp, &mesh, edgeCollapseThreshold);
			decim.execute();
			std::cout << "Decimated mesh has " << mesh.getNoOfIndices() << "  " << mesh.getNoOfVertices() << '\n';			
		}

		void cubicExtractMesh(VolumeType<VoxelType>& volume, const PolyVox::Region& region)
		{
			PolyVox::CubicSurfaceExtractorWithNormals<VolumeType, VoxelType> surfaceExtractor(&volume, region, &mesh);
			surfaceExtractor.execute();
			std::cout << "Extracted mesh with " << mesh.getNoOfIndices() << "  " << mesh.getNoOfVertices() << '\n';			
		}
		void smoothExtractMesh(VolumeType<VoxelType>& volume, const  PolyVox::Region& region)
		{
			PolyVox::SurfaceExtractor<VolumeType, VoxelType> surfaceExtractor(&volume, region, &mesh);
			surfaceExtractor.execute();
			std::cout << "Extracted mesh with " << mesh.getNoOfIndices() << "  " << mesh.getNoOfVertices() << '\n';			
		}

private:	glm::vec3 convertMaterialIDToColour(uint8_t materialID)
{
	glm::vec3 ret;

	switch(materialID)
	{
		case 1:
			ret.x = 1.0f;
			ret.y = 0.0f;
			ret.z = 0.0f;
			break;
		case 2:
			ret.x = 0.0f;
			ret.y = 1.0f;
			ret.z = 0.0f;
			break;
		case 3:
			ret.x = 0.0f;
			ret.y = 0.0f;
			ret.z = 1.0f;
			break;
		case 4:
			ret.x = 1.0f;
			ret.y = 1.0f;
			ret.z = 0.0f;
			break;
		case 5:
			ret.x = 1.0f;
			ret.y = 0.0f;
			ret.z = 1.0f;
			break;
		default:
			ret.x = 1.0f;
			ret.y = 1.0f;
			ret.z = 1.0f;
	}

	return ret;
}

};
