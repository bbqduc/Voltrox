#include "root.h"

InputHandler Root::inputHandler;
OpenGLWindow Root::openGLWindow;
ModelManager Root::modelManager;
TextureManager Root::textureManager;
ShaderManager Root::shaderManager;

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
	return inputHandler.init();
}

TROLLOERROR Root::initSystems()
{
	systems.push_back(new PositionSystem());
	systems.push_back(new PhysicsSystem());
	systems.push_back(new RenderSystem());
}

void Root::broadcastMessage(Message message, ct_t recipients)
{
	for(auto i = systems.begin(); i != systems.end(); ++i)
		if(i->id & recipients)
			i->handleMessage(message);
}


void Root::destroy()
{
	//	textRenderer.destroy();
	shaderManager.destroy();
	modelManager.destroy();
	textureManager.destroy();

	inputHandler.destroy();
	openGLWindow.destroy();
	physicsSystem.destroy();
}
