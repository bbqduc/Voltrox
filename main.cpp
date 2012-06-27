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
	static bool consoleActive;
	static Console* activeConsole;
	static glm::vec3 camPos, camUp, camView, camMove;
	static float angleY, angleX;
	static glm::quat camOri;
	const static float mouseSens;

//	static int oldMouseX, oldMouseY;
	static void handleMouseInput()
	{
		int x, y;
		glfwGetMousePos(&x,&y);
		/*float dx = (x - oldMouseX)*mouseSens;
		float dy = (y - oldMouseY)*mouseSens;*/
		glfwSetMousePos(1024/2,768/2);
		angleY += mouseSens * (1024/2 - x);
		angleX += mouseSens * (768/2 - y);
		camView = glm::vec3(cos(angleX) * sin(angleY),
								sin(angleX),
								cos(angleX) * cos(angleY));
		glm::vec3 right = glm::vec3(sin(angleY - 3.14f/2.0f),
											0,
											cos(angleY - 3.14f/2.0f));
		camUp = glm::cross( right, camView );

/*		oldMouseX = 0;//x;*/
//		oldMouseY = 0;//y;
	}

	static void moveCamera(int key, int action)
	{
		if(action == GLFW_PRESS)
		{
			if(key == 'W')
				camMove = camView;
			if(key == 'S')
				camMove = -1.0f * camView;
/*			if(key == GLFW_KEY_S)
			if(key == GLFW_KEY_D)*/
		}
		if(action == GLFW_RELEASE)
		{
			if(key == 'W')
				camMove = glm::vec3();
			if(key == 'S')
				camMove = glm::vec3();
/*			if(key == GLFW_KEY_S)
			if(key == GLFW_KEY_D)*/
		}
	}

	static void GLFWCALL handleKeyEvent(int key, int action) { 
		if(consoleActive)
			activeConsole->handleKeyEvent(key, action); 
		else
			moveCamera(key, action);
	}
};

bool Stub_Engine::consoleActive = false;
Console* Stub_Engine::activeConsole = 0;
const float Stub_Engine::mouseSens = 0.0005f;
float Stub_Engine::angleY = 3.14f;
float Stub_Engine::angleX = 0.0f;

glm::vec3 Stub_Engine::camUp = glm::vec3(0,1,0);
glm::vec3 Stub_Engine::camView = glm::vec3(0,0,-1);
glm::vec3 Stub_Engine::camPos = glm::vec3();
glm::vec3 Stub_Engine::camMove = glm::vec3();

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

	char title[128];
	while(running)
	{
		++frame;
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double t = glfwGetTime();
		if(1.0f + prevTime <= t)
		{
			float spf = (t - prevTime)*1000 / frame;
			sprintf(title, "ms per frame : %f", spf);
			glfwSetWindowTitle(title);
			prevTime = t;
			frame = 0;
		}
		renderer.renderText(title, 0.0f, -0.85f);

		glm::mat4 cam = glm::lookAt(Stub_Engine::camPos, Stub_Engine::camPos+Stub_Engine::camView, Stub_Engine::camUp);
		renderer.renderEntities(cam, Stub_Engine::camView);
		renderer.renderConsole(console);

		checkGLErrors("loop");

		glfwSwapBuffers();
		Stub_Engine::handleMouseInput();
		Stub_Engine::camPos += Stub_Engine::camMove;
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
