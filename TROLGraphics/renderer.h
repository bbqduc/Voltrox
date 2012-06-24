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
	enum SHADERS { MVP_TEXTURED };

	TextureManager textureManager;
	ModelManager modelManager;
	ShaderManager shaderManager;

	Renderer(const std::vector<Entity>& entities_, int resX_ = 1024, int resY_ = 768);
	int addShader(const char* vPath, const char* fPath, const char* gPath);
	void renderEntities();
	void renderText(const char* text, float x, float y, float scaleX, float scaleY);
	void addModelFromFile(const char* id, const char* path, const char* textureID=0);
	void addModelFromData(const char* id, const GLfloat* data, uint8_t* attribNums, const char* textureID=0);

private:
	std::vector<Shader> shaders;
	std::map<std::string, Model> models;
	const std::vector<Entity>& entities;

	glm::mat4 perspectiveProjection;
	TextRenderer textRenderer;
	int resX, resY;

	void initGL(int resX, int resY);
	void initBasicShaders();
//	boost::thread renderThread;
};
