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

#include "TROLConsole/console.h"

struct Stub_Engine 
{
	static glm::vec3 camPos, camUp, camView;
	static glm::quat camOri;
	const static float mouseSens = 0.5f;

	static int oldMouseX, oldMouseY;
	static void handleMouseInput()
	{
		int x, y;
		glfwGetMousePos(&x,&y);
		float dx = (x - oldMouseX)*mouseSens;
		float dy = (y - oldMouseY)*mouseSens;

		glm::vec3 axis = glm::normalize(glm::cross(camUp, camView));
		camView = glm::rotate(glm::rotate(camView, dx, glm::vec3(0.0f, 1.0f, 0.0f)), dy, axis);
		oldMouseX = x;
		oldMouseY = y;
	}

	static void moveCamera(int key, int action)
	{
//		if(action == GLFW_KEY_PRESSED)
		{
/*			if(key == GLFW_KEY_W)
			if(key == GLFW_KEY_A)
			if(key == GLFW_KEY_S)
			if(key == GLFW_KEY_D)*/
		}
	}

	static bool consoleActive = false;
	static Console* activeConsole;
	static void GLFWCALL handleKeyEvent(int key, int action) { 
		if(consoleActive)
			activeConsole->handleKeyEvent(key, action); 
		else
			moveCamera(key, action);
	}
};

Console* Stub_Engine::activeConsole = 0;
glm::vec3 Stub_Engine::camUp = glm::vec3(0,1,0);
glm::vec3 Stub_Engine::camView = glm::vec3(0,0,-1);

int main()
{
	std::vector<Entity> entities;
	Renderer renderer(entities);
	Console console;
	Stub_Engine::activeConsole = &console;
	glfwSetKeyCallback(&Stub_Engine::handleKeyEvent);

	renderer.addModelTROLLO("ship", "resources/ship.trollo", "default");

	entities.push_back(Entity(&renderer.getModel("ship"), glm::vec3(0,0,-100)));
	entities.push_back(Entity(&renderer.getModel("cube_tex"), glm::vec3(-2,2,-20)));

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

		glm::mat4 cam = glm::lookAt(Stub_Engine::camPos, Stub_Engine::camPos+Stub_Engine::camView, Stub_Engine::camUp);
		renderer.renderEntities(cam);
		renderer.renderConsole(console);

		checkGLErrors("loop");

		glfwSwapBuffers();
		Stub_Engine::handleMouseInput();
		glfwSleep(0.01);
		running = running && (!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED));

		for(auto i = entities.begin(); i != entities.end(); ++i)
		{
			glm::quat r(glm::vec3(0.1f,0.1f,0.1f));
			i->orientation = i->orientation * r;
		}
	}
	glUseProgram(0);
	glfwTerminate();
	return 0;

}
