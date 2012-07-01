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

#include "TROLLogic/Data/entity.h"
#include "TROLGraphics/renderer.h"
#include "TROLGraphics/glutils.h"

#include "TROLConsole/console.h"
#include "TROLLogic/engine.h"

#include <ctime>
#include <cstdlib>

int main()
{
	srand(time(0));
	Engine engine;
	Renderer renderer;
	engine.camera = &renderer.getCamera();
	engine.modelManager = &renderer.getModelManager();

	renderer.addModelTROLLO("ship", "resources/ship.trollo", "default");
	btVector3 pos(0,50,-100);
	engine.addEntity(renderer.getModel("ship"), pos);

	btQuaternion q;
	for(int i = 0; i < 100; ++i)
	{
		q.setX((rand()%50) - 100);
		q.setY((rand()%50) - 100);
		q.setZ((rand()%50) - 100);
		q.setW((rand()%50) - 100);

		pos.setX(-50.0f + (rand()%100));
		pos.setZ(-100.0f + (rand()%100) - 50);
		pos.setY(60.0f + (rand()%100) - 50);
		engine.addEntity(renderer.getModel("ship"), pos, q);
	}
//	pos = btVector3(-2,2,-20);
//	engine.addEntity(renderer.getModel("cube_tex"), pos);

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

		engine.tick();
		renderer.renderEntities(engine.getEntities());
		renderer.renderText(title, 0.0f, -0.85f);

		checkGLErrors("loop");

		glfwSwapBuffers();
		engine.tick();
		glfwSleep(0.01);
		running = running && (!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED));

/*		for(auto i = entities.begin(); i != entities.end(); ++i)
		{
			glm::quat r(glm::vec3(0.1f,0.1f,0.1f));
			i->orientation = i->orientation * r;
		}*/
	}
	glUseProgram(0);
	glfwTerminate();
	return 0;

}
