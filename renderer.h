#pragma once

#include <vector>
#include <map>
#include <string>

#include "entity.h"
#include "model.h"
#include "shader.h"
#include "gltext.h"

class Renderer
{
public:
	enum SHADERS { MVP_TEXTURED };

	const std::vector<Entity>& entities;
	Renderer(const std::vector<Entity>& entities_, int resX_ = 1024, int resY_ = 768);
	int addShader(const char* vPath, const char* fPath, const char* gPath);
	void renderEntities();
	void renderText(const char* text, float x, float y, float scaleX, float scaleY);
	void loadModelFromFile(const char* path, const char* id);
private:
	std::vector<Shader> shaders;

	glm::mat4 perspectiveProjection;
	TextRenderer textRenderer;
	int resX, resY;

	void initGL(int resX, int resY);
	void initBasicShaders();
//	boost::thread renderThread;
};