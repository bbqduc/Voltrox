#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstdlib>

#ifndef MAX_ENTITIES
#define MAX_ENTITIES 1024
#endif
#include <TROLCommon/root.h>


int main()
{
	srand(time(0));

	TROLLOERROR e;
	if(e = Root::init(1024, 768))
	{
		std::cerr << TROLLOErrorString(e) << '\n';
		Root::destroy();
		return -1;
	}
    Root::modelManager.addFromTROLLO("ship", "resources/ship.trollo", Root::textureManager.getTexture("default"));
	Model& shipModel = Root::modelManager.getModel("ship");
	btVector3 pos(0,50,-100);

	Message msg;
	btQuaternion q;
    PhysCreateMsgData msgData;

	msg.mType = ADD;
	msg.data = &msgData;

	float mass = 1.0f;
	msgData.ci = btRigidBody::btRigidBodyConstructionInfo(mass, 0, &const_cast<btConvexTriangleMeshShape&>(shipModel.collisionShape), shipModel.getInertia(mass));
	for(int i = 0; i < 350; ++i)
	{
		msg.entity = Root::storageSystem.createEntity();
		q.setX((rand()%50) - 100);
		q.setY((rand()%50) - 100);
		q.setZ((rand()%50) - 100);
		q.setW((rand()%50) - 100);

		pos.setX(-50.0f + (rand()%100));
		pos.setZ(-100.0f + (rand()%100) - 50);
		pos.setY(60.0f + (rand()%100) - 50);
		msgData.t = btTransform(q, pos);
		Root::broadcastMessage(msg, CTFlags::PHYSICS);
        *static_cast<Model**>(Root::storageSystem.addComponent(msg.entity, CT_RENDERABLE)) = &shipModel;
	}

	checkGLErrors("Preloop");
	bool running = true;

	double prevTime = glfwGetTime();
	float frame = 0;

	while(running)
	{
//		++frame;
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Root::physicsSystem.tick();
        Root::renderSystem.render();

		checkGLErrors("loop");

		glfwSwapBuffers();
		running = running && (!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED));

		double t = glfwGetTime();
		if(1.0f + prevTime <= t)
		{
			char title[128];
			float spf = (t - prevTime)*1000 / frame;
			sprintf(title, "ms per frame : %f", spf);
			glfwSetWindowTitle(title);
			prevTime = t;
			frame = 0;
		}

//		root.engine->tick();
//		root.renderManager.renderAll();
//		root.textRenderer.renderText(title, 0.0f, -0.85f);

	}
	glUseProgram(0);

	Root::destroy();

	return 0;
}
