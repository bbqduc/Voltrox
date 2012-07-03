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

	void renderEntities(const btAlignedObjectArray<Entity>& entities);
	void renderConsole(Console&);
//	void renderText(const char* text, float x, float y, float scaleX = 1.0f, float scaleY = 1.0f);

/*	void setModelTexture(const char* mid, const char* tid) { modelManager.setModelTexture(mid, textureManager.getTexture(tid)); }
	void addModelTROLLO(const char* id, const char* path, const char* textureID=0) { GLuint t = textureID ? textureManager.getTexture(textureID) : GL_INVALID_VALUE; modelManager.addFromTROLLO(id, path, t); }
	void addModelFromData(const char* id, const GLfloat* data, uint8_t* attribNums, const char* textureID=0);*/

	Camera& getCamera() { return camera; }
	int getResY() { return resY; }
	int getResX() { return resX; }

private:
	friend class Root;
	Renderer() {}
	void init(int resX, int resY);
	void destroy() { glfwTerminate(); }

	Camera camera;
	glm::mat4 perspective;

	int resX, resY;
	ShaderHandle MVP_TEXTURED;

	TROLLOERROR initGL();
};
