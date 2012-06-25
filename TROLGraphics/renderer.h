#pragma once

#include <vector>
#include <map>
#include <string>

#include "../TROLLogic/Data/entity.h"
#include "Data/model.h"
#include "shader.h"
#include "textrenderer.h"

#include "Managers/texturemanager.h"
#include "Managers/modelmanager.h"
#include "Managers/shadermanager.h"

class Renderer
{

public:
	Renderer(const std::vector<Entity>& entities_, int resX_ = 1024, int resY_ = 768);
	void renderEntities();
	void renderText(const char* text, float x, float y, float scaleX, float scaleY);
	void addBMPTexture(const char* id, const char* path) { textureManager.addFromBMP(id, path); }

	const Model& getModel(const char* id) { return modelManager.getModel(id); }
	void setModelTexture(const char* mid, const char* tid) { modelManager.setModelTexture(mid, textureManager.getTexture(tid)); }
	void addModelTROLLO(const char* id, const char* path, const char* textureID=0) { GLuint t = textureID ? textureManager.getTexture(textureID) : GL_INVALID_VALUE; modelManager.addFromTROLLO(id, path, t); }
	void addModelFromData(const char* id, const GLfloat* data, uint8_t* attribNums, const char* textureID=0);

	Shader& addShader(const char* id, const char* vPath, const char* fPath, const char* gPath = 0);
	Shader& getShader(const char* id) { return shaderManager.getShader(id); }

private:
	TextRenderer textRenderer;
	TextureManager textureManager;
	ModelManager modelManager;
	ShaderManager shaderManager;

	const std::vector<Entity>& entities;

	glm::mat4 perspectiveProjection;
	int resX, resY;

	void initGL(int resX, int resY);
	void initBasicShaders();
};
