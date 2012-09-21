#include "root.h"
#define MAX_ENTITIES 1024

InputSystem Root::inputSystem;
OpenGLWindow Root::openGLWindow;
ModelManager Root::modelManager;
TextureManager Root::textureManager;
ShaderManager Root::shaderManager;

PhysicsSystem Root::physicsSystem;
PositionSystem Root::positionSystem;
RenderSystem Root::renderSystem;
StorageSystem Root::storageSystem(MAX_ENTITIES);
std::vector<ISystem*> Root::systems;

// Initializes everything in the correct order
TROLLOERROR Root::init(int resX, int resY)
{
	if(openGLWindow.init(resX, resY))
	{
		std::cerr << "Failed to init OpenGL window!\n";
		return TROLLO_INIT_FAILURE;
	}

	TROLLOERROR ret;
	if(ret = initManagers())
		return ret;

	return initSystems();
}

TROLLOERROR Root::initManagers()
{
	if(textureManager.init())
	{
		std::cerr << "Failed to init TextureManager\n";
		return TROLLO_INIT_FAILURE;
	}
	if(modelManager.init(textureManager.getTexture("default")))
	{
		std::cerr << "Failed to init ModelManager\n";
		return TROLLO_INIT_FAILURE;
	}
	if(shaderManager.init())
	{
		std::cerr << "Failed to init ShaderManager\n";
		return TROLLO_INIT_FAILURE;
	}
	/*	if(textRenderer.init())
		{
		std::cerr << "Failed to init TextRenderer\n";
		return TROLLO_INIT_FAILURE;
		}*/
	return inputSystem.init();
}

TROLLOERROR Root::initSystems()
{
    systems.push_back(&positionSystem);
    storageSystem.addSystem(sizeof(btTransform*));
    systems.push_back(&physicsSystem);
    storageSystem.addSystem(sizeof(btRigidBody));
    systems.push_back(&renderSystem);
    storageSystem.addSystem(sizeof(Model*));
    return TROLLO_OK;
}

rsp_t Root::broadcastMessage(Message message, ct_t recipients)
{
	for(auto i = systems.begin(); i != systems.end(); ++i)
		if((*i)->id & recipients)
			(*i)->handleMessage(message);
    return MSG_DONE;
}


void Root::destroy()
{
	//	textRenderer.destroy();
	shaderManager.destroy();
	modelManager.destroy();
	textureManager.destroy();

	inputSystem.destroy();
//	openGLWindow.destroy();
//	physicsSystem.destroy();
}
