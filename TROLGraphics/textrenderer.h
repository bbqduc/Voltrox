#pragma once

#ifdef TROL_USE_OLD_OPENGL
	#include <GL/glew.h>
#else
	#include <GL3/gl3w.h>
#endif

#include <GL/glfw.h>
#include <GL/gl.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "shader.h"
#include <glm/glm.hpp>

class TextRenderer
{
	public:
	TextRenderer();
	bool initGraphics();

	bool loadFace(const char* path, int height = 48);
	void renderText(const char* text, float x, float y, float sx, float sy);

	private:

	void initAtlas();

	GLuint tex, vbo, vao;
	int width,height; // width and height of texture
	Shader textShader;

	FT_Library ft;
	FT_Face face; // Just one for now
	int numFaces;

	struct {
		float ax; // advance.x
		float ay; // advance.y

		float bw; // bitmap width
		float bh; // bitmap height

		float bl; // bitmap left
		float bt; // bitmap top

		float tx; // x offset of glyph in texture coordinates
		float ty; // y offset of glyhp in texture coordinates
	} c[128]; // character information

};