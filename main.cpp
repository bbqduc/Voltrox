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
#include "TROLLogic/engine.h"

int main()
{
	Engine engine;
	Renderer renderer(engine.getEntities());
	engine.camera = &renderer.getCamera();

	renderer.addModelTROLLO("ship", "resources/ship.trollo", "default");
	engine.addEntity(Entity(&renderer.getModel("ship"), glm::vec3(0,0,-100)));
	engine.addEntity(Entity(&renderer.getModel("cube_tex"), glm::vec3(-2,2,-20)));

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

		engine.tick();
		renderer.renderEntities();

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
