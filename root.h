#pragma once

#include "TROLGraphics/renderer.h"
#include "TROLGraphics/textrenderer.h"
#include "TROLGraphics/Managers/modelmanager.h"
#include "TROLGraphics/Managers/texturemanager.h"
#include "TROLGraphics/Managers/shadermanager.h"
#include "TROLLogic/engine.h"
#include "TROLLogic/inputhandler.h"
#include "TROLGraphics/glutils.h"


// Contains all singleton managers/things
// Responsible for initializing/destroying everything in the correct order
struct Root
{
	Engine* engine; // Has to be pointer because it contains bullet objects without a default ctor
	InputHandler inputHandler;

	Renderer renderer;
	ModelManager modelManager;
	TextureManager textureManager;
	ShaderManager shaderManager;
	TextRenderer textRenderer;

	static TROLLOERROR initSingleton(int resX, int resY) { assert(!initialized); initialized=true; return singleton.init(resX, resY); };
	static void destroySingleton() { singleton.destroy(); }
	static Root& getSingleton() { return singleton; }

	private:
	Root() {}
	static bool initialized;
	static Root singleton;
	TROLLOERROR init(int resX, int resY);
	void destroy();

	Root(const Root&);
	Root& operator=(const Root&);
};
