#pragma once

#include <map>
#include <string>

#include "../TROLLogic/Data/entity.h"
#include "Data/model.h"
#include "shader.h"
#include "textrenderer.h"

#include "Managers/texturemanager.h"
#include "Managers/modelmanager.h"
#include "Managers/shadermanager.h"

#include "../TROLConsole/console.h"
#include "camera.h"

#include <glm/glm.hpp>

class Renderer
{

public:

	static bool explodeAll;

	void renderEntities(const std::vector<Entity*>& entities);
	void renderConsole(Console&);

	Camera& getCamera() { return camera; }
	int getResY() { return resY; }
	int getResX() { return resX; }

private:
	friend class Root;
	Renderer() {}
	TROLLOERROR init(int resX, int resY);
	void destroy() { glfwTerminate(); }

	Camera camera;
	glm::mat4 perspective;

	int resX, resY;
	ShaderHandle MVP_TEXTURED;

	TROLLOERROR initGL();
};
