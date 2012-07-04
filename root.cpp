#include "root.h"

bool Root::initialized = false;
Root Root::singleton;

// Initializes everything in the correct order
TROLLOERROR Root::init(int resX, int resY)
{
	engine = new Engine();
	inputHandler.init();

	if(renderer.init(resX, resY))
	{
		std::cerr << "Failed to init renderer\n";
		return TROLLO_INIT_FAILURE;
	}
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
	if(textRenderer.init())
	{
		std::cerr << "Failed to init TextRenderer\n";
		return TROLLO_INIT_FAILURE;
	}

	return TROLLO_OK;
}

void Root::destroy()
{
	textRenderer.destroy();
	shaderManager.destroy();
	modelManager.destroy();
	textureManager.destroy();
	renderer.destroy();

	inputHandler.destroy();
	delete engine;
}
