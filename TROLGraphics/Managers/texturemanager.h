#pragma once

#include <map>
#include <string>
#include <png.h>
#include <pnginfo.h>

#ifdef TROL_USE_OLD_OPENGL
	#include <GL/glew.h>
#else
	#include <GL3/gl3w.h>
#endif

#include <GL/glfw.h>
#include <GL/gl.h>

#include "../glutils.h"
#include "../../TROLUtil/error.h"

class TextureManager
{
public:
	GLuint getTexture(const std::string& s) { return textures[s]; }
	GLuint addFromPNG(const std::string&, const std::string&);
	GLuint addFromBMP(const std::string&, const std::string&);
private:
	friend class Root;
	TextureManager() {}
	TROLLOERROR init();
	void destroy();

	std::map<std::string, GLuint> textures;
};
