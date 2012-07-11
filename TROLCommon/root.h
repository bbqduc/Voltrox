#pragma once

#include "TROLGraphics/textrenderer.h"
#include "TROLGraphics/Managers/modelmanager.h"
#include "TROLGraphics/Managers/texturemanager.h"
#include "TROLGraphics/Managers/shadermanager.h"
#include "TROLLogic/inputhandler.h"
#include "TROLGraphics/glutils.h"
#include "TROLUtil/error.h"
#include "TROLLogic/physicssystem.h"
#include "TROLCommon/entitysystem.h"
#include "TROLCommon/positionsystem.h"
#include "TROLGraphics/rendersystem.h"
#include "TROLGraphics/openglwindow.h"
#include "TROLCommon/message.h"
#include <vector>

// Contains all singleton managers/things
// Responsible for initializing/destroying everything in the correct order
struct Root
{
	static InputHandler inputHandler;
    static EntitySystem entitySystem;

	static OpenGLWindow openGLWindow;
	static ModelManager modelManager;
	static TextureManager textureManager;
	static ShaderManager shaderManager;

	static TROLLOERROR init(int resX, int resY);
	static void destroy();

    static PhysicsSystem physicsSystem;
    static PositionSystem positionSystem;
    static RenderSystem renderSystem;

    static rsp_t broadcastMessage(Message, ct_t);

	private:
	Root() {}
	static TROLLOERROR initManagers();
	static TROLLOERROR initSystems();

	Root(const Root&);
	Root& operator=(const Root&);
};
