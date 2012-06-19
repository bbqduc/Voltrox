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


int main()
{
	if(init())
		exit(-1);
	
	Shader plain;
	if(!plain.loadFromShaderDir("plainMVP.vert", "plainTextured.frag", 0))
		exit(-1);
	uint8_t MVPI = plain.storeUniformLoc("MVP");
	uint8_t samplerI = plain.storeUniformLoc("sampler");

	checkGLErrors("InitShaders");


/*	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);*/

	glUseProgram(plain.id);
	checkGLErrors("Preloop");
	bool running = true;

	Model<VertexNormalTexcrd> model;
	model.loadFromFile("ship.trollo");
	model.loadTexture("ship.png");
//	model.fullScreenQuadModel();

	for(int i = 0; i < model.numVertices; ++i)
	{
		for(int j = 0; j < 3; ++j)
			std::cout << model.vertexData[i].vertex[j] << ' ';
		std::cout << '\n';
	}
	for(int i = 0; i < model.numFaces; ++i)
	{
		for(int j = 0; j < 3; ++j)
			std::cout << model.indices[i][j] << ' ';
		std::cout << '\n';
	}
	for(int i = 0; i < model.numVertices; ++i)
	{
		for(int j = 0; j < 2; ++j)
			std::cout << model.vertexData[i].texcrd[j] << ' ';
		std::cout << '\n';
	}
	glUniform1i(plain.uniformLocs[samplerI], 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model.texture);

	float time = -100.0f;
	while(running)
	{
		time += 0.5f;
		glm::mat4 perspective = glm::perspective(45.0f, 1024.0f/768.0f, 1.0f, 1000.0f);
		glm::mat4 MVP = glm::translate(glm::mat4(), glm::vec3(0,0,time));

		glm::mat4 result = perspective * MVP;

		glUniformMatrix4fv(plain.uniformLocs[MVPI], 1, GL_FALSE, glm::value_ptr(result));
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(model.VAO);
		glDrawElements(GL_TRIANGLES, model.numFaces*3, GL_UNSIGNED_INT, 0);
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
