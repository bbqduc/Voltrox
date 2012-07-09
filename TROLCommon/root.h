#pragma once

#include "TROLGraphics/textrenderer.h"
#include "TROLGraphics/Managers/modelmanager.h"
#include "TROLGraphics/Managers/texturemanager.h"
#include "TROLGraphics/Managers/shadermanager.h"
#include "TROLLogic/engine.h"
#include "TROLLogic/inputhandler.h"
#include "TROLLogic/entitystorage.h"
#include "TROLGraphics/glutils.h"
#include "TROLUtil/error.h"


// Contains all singleton managers/things
// Responsible for initializing/destroying everything in the correct order
struct Root
{
	PhysicsSystem physicsSystem;
	RenderSystem renderSystem;
	PositionSystem positionSystem;

	InputHandler inputHandler;

	OpenGLWindow openGLWindow;
	ModelManager modelManager;
	TextureManager textureManager;
	ShaderManager shaderManager;
//	TextRenderer textRenderer;

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
