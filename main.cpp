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

#include "model.h"
#include "shader.h"
#include "glutils.h"
#include "gltext.h"


int main()
{
	if(init())
		exit(-1);
	
	Shader plain;
	if(!plain.loadFromShaderDir("plainMVP.vert", "plainTextured.frag", 0))
		exit(-1);
	uint8_t MVPI = plain.storeUniformLoc("MVP");
	uint8_t samplerI = plain.storeUniformLoc("sampler");

	TextManager textManager;
	if(!textManager.initGraphics())
		exit(-1);
	textManager.loadFace("FreeSans.ttf");

	checkGLErrors("Preloop");
	bool running = true;

	Model<VertexNormalTexcrd> model;
//	model.loadFromFile("ship.trollo");
	model.makeTexturedCube();
//	model.fullScreenQuadModel();
	if(!model.loadTextureBMP("ship.bmp"))
	{
		std::cerr << "Texture load failed!\n";
		return -1;
	}

	float time = -100.0f;
	double prevTime = glfwGetTime();
	while(running)
	{
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(plain.id);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(plain.uniformLocs[samplerI], 0);
		glBindTexture(GL_TEXTURE_2D, model.texture);

		double t = glfwGetTime();
		time += t-prevTime;
		prevTime=t;
		
		glm::mat4 perspective = glm::perspective(45.0f, 1024.0f/768.0f, 1.0f, 1000.0f);
		glm::mat4 rot = glm::rotate(glm::mat4(), time*10, glm::vec3(1.0f, 1.0f,1.0f));
		glm::mat4 MVP = glm::translate(glm::mat4(), glm::vec3(0,0,-10));
		MVP = MVP * rot;

		glm::mat4 result = perspective * MVP;

		glUniformMatrix4fv(plain.uniformLocs[MVPI], 1, GL_FALSE, glm::value_ptr(result));
		glBindVertexArray(model.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, model.vertexBuffer);
		glDrawElements(GL_TRIANGLES, model.numFaces*3, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
		checkGLErrors("loop");

		textManager.renderText("HAIL TROLLO!", -1, 0, 2.0/1024.0, 2.0/768.0);

		glfwSwapBuffers();
		glfwSleep(0.01);
		running = running && (!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED));
	}
	glUseProgram(0);
	glfwTerminate();
	return 0;

}
