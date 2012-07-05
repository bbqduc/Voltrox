#pragma once
#include <vector>
#include "irender.h"
#include "../TROLUtil/error.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct OpenGLInfo
{
	int resX, resY;
	glm::mat4 perspective;
};

class RenderManager
{
public:
	void renderAll();
	template <typename T>
	T& getNewRenderManager();
	const glm::mat4& getPerspective() { return openglInfo.perspective; }
	int getResX() { return openglInfo.resX; }
	int getResY() { return openglInfo.resY; }

private:
	friend class Root;
	TROLLOERROR init(int resX, int resY);
	void destroy();

	TROLLOERROR initGL();

	std::vector<IRenderer*> renderers;
	OpenGLInfo openglInfo;
};

template <typename T>
T& RenderManager::getNewRenderManager()
{
	T* t = new T();
	renderers.push_back(t);
	return *t;
}