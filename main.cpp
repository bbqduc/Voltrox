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

#define MAX_ENTITIES 512
#include "root.h"

#include <ctime>
#include <cstdlib>

int main()
{
	srand(time(0));

	TROLLOERROR e;
	if(e = Root::initSingleton(1024, 768))
	{
		std::cerr << TROLLOErrorString(e) << '\n';
		Root::destroySingleton();
		return -1;
	}
	Root& root = Root::getSingleton();

	root.modelManager.addFromTROLLO("ship", "resources/ship.trollo", root.textureManager.getTexture("default"));
	btVector3 pos(0,50,-100);

	Entity* et = root.entityStorage.addEntity(root.modelManager.getModel("ship"), pos);
	root.engine->addEntity(*et);

	btQuaternion q;
	for(int i = 0; i < 350; ++i)
	{
		q.setX((rand()%50) - 100);
		q.setY((rand()%50) - 100);
		q.setZ((rand()%50) - 100);
		q.setW((rand()%50) - 100);

		pos.setX(-50.0f + (rand()%100));
		pos.setZ(-100.0f + (rand()%100) - 50);
		pos.setY(60.0f + (rand()%100) - 50);
		et = root.entityStorage.addEntity(root.modelManager.getModel("ship"), pos, q);
		root.engine->addEntity(*et);
	}

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

		root.engine->tick();
//		root.renderer.renderEntities(root.engine->getEntities());
		root.renderManager.renderAll();
		root.textRenderer.renderText(title, 0.0f, -0.85f);

		checkGLErrors("loop");

		glfwSwapBuffers();
//		glfwSleep(0.01);
		running = running && (!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED));

	}
	glUseProgram(0);

	Root::destroySingleton();

	return 0;

}
