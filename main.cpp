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

#include "shader.h"
#include "voxelmodel.h"
#include "glutils.h"

#include <PolyVoxCore/MaterialDensityPair.h>
#include <PolyVoxCore/CubicSurfaceExtractorWithNormals.h>
#include <PolyVoxCore/SurfaceMesh.h>
#include <PolyVoxCore/SimpleVolume.h>

void createSphereInVolume(PolyVox::SimpleVolume<PolyVox::MaterialDensityPair44>& volData, float fRadius)
{
	using namespace PolyVox;
	//This vector hold the position of the center of the volume
	Vector3DFloat v3dVolCenter(volData.getWidth() / 2, volData.getHeight() / 2, volData.getDepth() / 2);

	//This three-level for loop iterates over every voxel in the volume
	for (int z = 0; z < volData.getWidth(); z++)
	{
		for (int y = 0; y < volData.getHeight(); y++)
		{
			for (int x = 0; x < volData.getDepth(); x++)
			{
				//Store our current position as a vector...
				Vector3DFloat v3dCurrentPos(x,y,z);	
				//And compute how far the current position is from the center of the volume
				float fDistToCenter = (v3dCurrentPos - v3dVolCenter).length();

				//If the current voxel is less than 'radius' units from the center then we make it solid.
				if(fDistToCenter <= fRadius)
				{
					//Our new density value
					uint8_t uDensity = MaterialDensityPair44::getMaxDensity();

					//Get the old voxel
					MaterialDensityPair44 voxel = volData.getVoxelAt(x,y,z);

					//Modify the density
					voxel.setDensity(uDensity);

					//Wrte the voxel value into the volume	
					volData.setVoxelAt(x, y, z, voxel);
				}
			}
		}
	}
}

int main()
{
	if(init())
		exit(-1);

	Shader tunnel;
	if(!tunnel.loadFromShaderDir("plain.vert", "tunnel.frag", 0))
		exit(-1);
	Shader plain;
	if(!plain.loadFromShaderDir("plain.vert", "plain.frag", 0))
		exit(-1);
	uint8_t tunnelTimeI = tunnel.storeUniformLoc("time");
	uint8_t tunnelDistanceI = tunnel.storeUniformLoc("tunneldistance");

	float tunnelDist = 0.0001f;

	using PolyVox::Vector3DInt32;
	PolyVox::SimpleVolume<PolyVox::MaterialDensityPair44> volData(PolyVox::Region(Vector3DInt32(0,0,0), Vector3DInt32(63, 63, 63)));
	createSphereInVolume(volData, 30);
	VoxelModel<PolyVox::MaterialDensityPair44> polyModel(volData);

	glUseProgram(plain.id);
//	glUniform1f(tunnel.uniformLocs[tunnelDistanceI], tunnelDist);
//	glUniform1f(tunnel.uniformLocs[tunnelTimeI], tunnelDist);
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
