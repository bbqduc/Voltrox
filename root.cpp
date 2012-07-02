#include "root.h"

bool Root::initialized = false;
Root Root::singleton;

// Initializes everything in the correct order
TROLLOERROR Root::init(int resX, int resY)
{
	engine = new Engine();
	inputHandler.init();

	renderer.init(resX, resY);
	textureManager.init();
	modelManager.init(textureManager.getTexture("default"));
	shaderManager.init();
	textRenderer.init();

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
