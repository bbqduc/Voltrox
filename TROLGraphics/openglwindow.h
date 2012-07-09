#pragma once
#include <glm/glm.hpp>
#include "TROLUtil/error.h"

// TODO : perspective belongs somewhere else
class OpenGLWindow
{
	public:
		TROLLOERROR init(int resX, int resY);
		int getResX() { return resX; }
		int getResY() { return resY; }
		const glm::mat4& getPerspective() { return perspective; }
	private:
		friend class Root;
		OpenGLManager() {}
		OpenGLManager(const OpenGLManager&);
		OpenGLManager& operator=(const OpenGLManager&);
		TROLLOERROR initGL()

		int resX, resY;
		glm::mat4 perspective;
};
