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

#include "TROLLogic/Data/entity.h"
#include "TROLGraphics/renderer.h"
#include "TROLGraphics/glutils.h"

int main()
{
	std::vector<Entity> entities;
	Renderer renderer(entities);

	renderer.textureManager.addFromPNG("ship", "resources/ship.png");

	renderer.modelManager.addFromTROLLO();
	Model model;
	if(!model.loadTexturePNG("ship.png"))
	{
		std::cerr << "Texture load failed!\n";
		return -1;
	}
//	model.loadFromFile("ship.trollo");
	model.makeTexturedCube();
//	model.makeTriangle();
//	model.makeTexturedQuad();

	for(float i = -1; i < 1; i+=0.1f)
		entities.push_back(Entity(&model, glm::vec3(i,-i,-10)));

	checkGLErrors("Preloop");
	bool running = true;

	float time = -100.0f;
	double prevTime = glfwGetTime();
	float frame = 0;
	while(running)
	{
		++frame;
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double t = glfwGetTime();
		time += t-prevTime;
		prevTime=t;
		char a[64];
		float c = frame / t;
		sprintf(a, "FPS %f", c);

		renderer.renderEntities();
		renderer.renderText(a, -0.5, 0.8, 1.0, 1.0);

		checkGLErrors("loop");

		glfwSwapBuffers();
		glfwSleep(0.01);
		running = running && (!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED));
	}
	glUseProgram(0);
	glfwTerminate();
	return 0;

}
