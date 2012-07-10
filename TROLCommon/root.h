#pragma once

#include "TROLGraphics/textrenderer.h"
#include "TROLGraphics/Managers/modelmanager.h"
#include "TROLGraphics/Managers/texturemanager.h"
#include "TROLGraphics/Managers/shadermanager.h"
#include "TROLLogic/inputhandler.h"
#include "TROLLogic/entitystorage.h"
#include "TROLGraphics/glutils.h"
#include "TROLUtil/error.h"
#include "TROLLogic/physicssystem.h"
#include "message.h"
#include <vector>

// Contains all singleton managers/things
// Responsible for initializing/destroying everything in the correct order
struct Root
{
	static InputHandler inputHandler;

	static OpenGLWindow openGLWindow;
	static ModelManager modelManager;
	static TextureManager textureManager;
	static ShaderManager shaderManager;

	static TROLLOERROR init(int resX, int resY);
	static void destroy();

	private:
	Root() {}
	static TROLLOERROR initManagers();
	static TROLLOERROR initSystems();

	static std::vector<System*> systems;

	Root(const Root&);
	Root& operator=(const Root&);
};
