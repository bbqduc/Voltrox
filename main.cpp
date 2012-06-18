#include <string>
#ifdef TROL_USE_OLD_OPENGL
#include <GL/glew.h>
#else
#include <GL3/gl3w.h>
#endif

#include <GL/glfw.h>
#include <GL/gl.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "voxelmodel.h"
#include "glutils.h"
#include "shapes.h"

#include <PolyVoxCore/MaterialDensityPair.h>
#include <PolyVoxCore/CubicSurfaceExtractorWithNormals.h>
#include <PolyVoxCore/SurfaceMesh.h>
#include <PolyVoxCore/SimpleVolume.h>
#include <PolyVoxCore/LargeVolume.h>
#include <PolyVoxCore/RawVolume.h>
#include <PolyVoxCore/LowPassFilter.h>


int main()
{
	if(init())
		exit(-1);
	
	int32_t sidelength = 128;
	int32_t minPos = 0;
	int32_t midPos = sidelength / 2;
	int32_t maxPos = sidelength - 1;

	using PolyVox::Vector3DInt32;	
	PolyVox::LargeVolume<PolyVox::MaterialDensityPair44> volData(PolyVox::Region(Vector3DInt32(0,0,0), Vector3DInt32(maxPos, maxPos, maxPos)));

	Shader plain;
	if(!plain.loadFromShaderDir("plainMVP.vert", "colorarg.frag", 0))
		exit(-1);
	uint8_t MVPI = plain.storeUniformLoc("MVP");

	checkGLErrors("InitShaders");

	glm::mat4 perspective = glm::perspective(45.0f, 1024.0f/768.0f, 1.0f, 1000.0f);
	glm::mat4 MVP = glm::translate(glm::mat4(), glm::vec3(-sidelength/2,-sidelength/2,-sidelength/2-volData.getDiagonalLength()));

	glm::mat4 result = perspective * MVP;

	createShapes(volData);
;
	PolyVox::RawVolume<PolyVox::MaterialDensityPair44> tempVol(PolyVox::Region(0,0,0,128,128,128));
	PolyVox::LowPassFilter<PolyVox::LargeVolume, PolyVox::RawVolume, PolyVox::MaterialDensityPair44> pass1(&volData, PolyVox::Region(Vector3DInt32(62,62,62), Vector3DInt32(126,126,126)), &tempVol, PolyVox::Region(Vector3DInt32(62,62,62), Vector3DInt32(126,126,126)), 3);
	pass1.executeSAT();
	PolyVox::LowPassFilter<PolyVox::RawVolume, PolyVox::LargeVolume, PolyVox::MaterialDensityPair44> pass2(&tempVol, PolyVox::Region(Vector3DInt32(62,62,62), Vector3DInt32(126,126,126)), &volData, PolyVox::Region(Vector3DInt32(62,62,62), Vector3DInt32(126,126,126)), 3);
	pass2.executeSAT();
	

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	const int32_t regionSideLength = 128;
	const int32_t regionWidth = volData.getWidth() / regionSideLength;
	const int32_t regionHeight = volData.getHeight() / regionSideLength;
	const int32_t regionDepth = volData.getDepth() / regionSideLength;
	int32_t currentModel = 0;
	int32_t numModels = regionWidth*regionHeight*regionDepth;

	VoxelModel<PolyVox::LargeVolume, PolyVox::MaterialDensityPair44>* regionModels = new VoxelModel<PolyVox::LargeVolume, PolyVox::MaterialDensityPair44>[numModels];

	for(int32_t i = 0; i < regionDepth; ++i)
		for(int32_t j = 0; j < regionHeight; ++j)
			for(int32_t k = 0; k < regionWidth; ++k)
			{
				int32_t startX = k*regionSideLength, startY = j*regionSideLength, startZ = i*regionSideLength;
				int32_t endX = startX+regionSideLength, endY = startY+regionSideLength, endZ = startZ+regionSideLength;
					
				Vector3DInt32 regLowerCorner(startX, startY, startZ);
				Vector3DInt32 regUpperCorner(endX, endY, endZ);

				regionModels[currentModel].smoothExtractMesh(volData, PolyVox::Region(regLowerCorner, regUpperCorner));
				regionModels[currentModel].decimateMesh();

				if(regionModels[currentModel].mesh.getNoOfIndices())
					regionModels[currentModel++].initBuffers();
				else
					--numModels;
			}


/*	VoxelModel<PolyVox::LargeVolume, PolyVox::MaterialDensityPair44> polyModel;
	polyModel.smoothExtractMesh(volData);
	polyModel.decimateMesh();
	polyModel.initBuffers();*/
	glUseProgram(plain.id);
//	glUniform1f(tunnel.uniformLocs[tunnelDistanceI], tunnelDist);
	glUniformMatrix4fv(plain.uniformLocs[MVPI], 1, GL_FALSE, glm::value_ptr(result));
	checkGLErrors("Preloop");
	bool running = true;

	int32_t uLodLevel=0;
//	int startIndex = polyModel.mesh.m_vecLodRecords[uLodLevel].beginIndex;
//	int endIndex = polyModel.mesh.m_vecLodRecords[uLodLevel].endIndex;

	while(running)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for(int32_t i = 0; i < numModels; ++i)
		{
			glBindVertexArray(regionModels[i].VAO);
			glDrawElements(GL_TRIANGLES, regionModels[i].mesh.getIndices().size(), GL_UNSIGNED_INT, 0);
//		glDrawRangeElements(GL_TRIANGLES, startIndex, endIndex-1, endIndex-startIndex, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			checkGLErrors("loop");
		}
		glfwSwapBuffers();
		glfwSleep(0.01);
		running = running && (!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED));
	}
	glUseProgram(0);
	glfwTerminate();
	return 0;

}
