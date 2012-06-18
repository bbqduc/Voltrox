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

#include <PolyVoxCore/MaterialDensityPair.h>
#include <PolyVoxCore/CubicSurfaceExtractorWithNormals.h>
#include <PolyVoxCore/SurfaceMesh.h>
#include <PolyVoxCore/SimpleVolume.h>
#include <PolyVoxCore/LargeVolume.h>
#include <PolyVoxCore/RawVolume.h>
#include <PolyVoxCore/LowPassFilter.h>

void createSphereInVolume(PolyVox::LargeVolume<PolyVox::MaterialDensityPair44>& volData, float fRadius, uint8_t uValue)
{
	using namespace PolyVox;
	//This vector hold the position of the center of the volume
	Vector3DInt32 v3dVolCenter = (volData.getEnclosingRegion().getUpperCorner() - volData.getEnclosingRegion().getLowerCorner()) / 2;

	//This three-level for loop iterates over every voxel in the volume
	for (int z = 0; z < volData.getWidth(); z++)
	{
		for (int y = 0; y < volData.getHeight(); y++)
		{
			for (int x = 0; x < volData.getDepth(); x++)
			{
				//Store our current position as a vector...
				Vector3DInt32 v3dCurrentPos(x,y,z);	
				//And compute how far the current position is from the center of the volume
				double fDistToCenter = (v3dCurrentPos - v3dVolCenter).length();

				//If the current voxel is less than 'radius' units from the center
				//then we make it solid, otherwise we make it empty space.
				if(fDistToCenter <= fRadius)
				{
					volData.setVoxelAt(x,y,z, MaterialDensityPair44(uValue, uValue > 0 ? MaterialDensityPair44::getMaxDensity() : MaterialDensityPair44::getMinDensity()));
				}
			}
		}
	}
}

void createCubeInVolume(PolyVox::LargeVolume<PolyVox::MaterialDensityPair44>& volData, PolyVox::Vector3DInt32 lowerCorner, PolyVox::Vector3DInt32 upperCorner, uint8_t uValue)
{
	using namespace PolyVox;
	//This three-level for loop iterates over every voxel between the specified corners
	for (int z = lowerCorner.getZ(); z <= upperCorner.getZ(); z++)
	{
		for (int y = lowerCorner.getY(); y <= upperCorner.getY(); y++)
		{
			for (int x = lowerCorner.getX() ; x <= upperCorner.getX(); x++)
			{
				volData.setVoxelAt(x,y,z, MaterialDensityPair44(uValue, uValue > 0 ? MaterialDensityPair44::getMaxDensity() : MaterialDensityPair44::getMinDensity()));
			}
		}
	}
}

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
	if(!plain.loadFromShaderDir("plainMVP.vert", "plain.frag", 0))
		exit(-1);
	uint8_t MVPI = plain.storeUniformLoc("MVP");

	glm::mat4 perspective = glm::perspective(45.0f, 1024.0f/768.0f, 1.0f, 1000.0f);
	glm::mat4 MVP = glm::translate(glm::mat4(), glm::vec3(-sidelength/2,-sidelength/2,-sidelength/2-volData.getDiagonalLength()));

	glm::mat4 result = perspective * MVP;

	createSphereInVolume(volData, 60, 5);
	createSphereInVolume(volData, 50, 4);
	createSphereInVolume(volData, 40, 3);
	createSphereInVolume(volData, 30, 2);
	createSphereInVolume(volData, 20, 1);

	createCubeInVolume(volData, Vector3DInt32(minPos, minPos, minPos), Vector3DInt32(midPos-1, midPos-1, midPos-1), 0);
	createCubeInVolume(volData, Vector3DInt32(midPos+1, midPos+1, minPos), Vector3DInt32(maxPos, maxPos, midPos-1), 0);
//	createCubeInVolume(volData, Vector3DInt32(minPos, minPos, minPos), Vector3DInt32(midPos-1, midPos-1, midPos-1), 0);
//	createCubeInVolume(volData, Vector3DInt32(minPos, minPos, minPos), Vector3DInt32(midPos-1, midPos-1, midPos-1), 0);

	PolyVox::RawVolume<PolyVox::MaterialDensityPair44> tempVol(PolyVox::Region(0,0,0,128,128,128));
	PolyVox::LowPassFilter<PolyVox::LargeVolume, PolyVox::RawVolume, PolyVox::MaterialDensityPair44> pass1(&volData, PolyVox::Region(Vector3DInt32(62,62,62), Vector3DInt32(126,126,126)), &tempVol, PolyVox::Region(Vector3DInt32(62,62,62), Vector3DInt32(126,126,126)), 3);
	pass1.executeSAT();
	PolyVox::LowPassFilter<PolyVox::RawVolume, PolyVox::LargeVolume, PolyVox::MaterialDensityPair44> pass2(&tempVol, PolyVox::Region(Vector3DInt32(62,62,62), Vector3DInt32(126,126,126)), &volData, PolyVox::Region(Vector3DInt32(62,62,62), Vector3DInt32(126,126,126)), 3);
	pass2.executeSAT();
	
	VoxelModel<PolyVox::LargeVolume, PolyVox::MaterialDensityPair44> polyModel(volData);
	glUseProgram(plain.id);
//	glUniform1f(tunnel.uniformLocs[tunnelDistanceI], tunnelDist);
	glUniformMatrix4fv(plain.uniformLocs[MVPI], 1, GL_FALSE, glm::value_ptr(result));
	checkGLErrors("Preloop");
	bool running = true;
	while(running)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(polyModel.VAO);
		glDrawElements(GL_TRIANGLES, polyModel.mesh.getIndices().size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		checkGLErrors("loop");
		glfwSwapBuffers();
		glfwSleep(0.01);
		running = running && (!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED));
	}
	glUseProgram(0);
	glfwTerminate();
	return 0;

}
