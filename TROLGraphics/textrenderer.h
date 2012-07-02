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
#include "glutils.h"

class TextRenderer
{
	public:
	TROLLOERROR init();
	void destroy();

	bool loadFace(const char* path, int height = 48);
	void renderText(const char* text, float x, float y, float sx=1.0f, float sy=1.0f);

	private:
	friend class Root;
	TextRenderer() {}

	void initAtlas(FT_Face&);
	void initGraphics();

	GLuint tex, vbo, vao;
	int width,height; // width and height of texture

	FT_Library ft;
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