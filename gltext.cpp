#include "gltext.h"
#include "glutils.h"
#include <iostream>

#define MAXWIDTH 1024

TextRenderer::TextRenderer()
	:numFaces(0)
{
	if(FT_Init_FreeType(&ft))
		std::cerr << "Could not init freetype library!\n";
}

void TextRenderer::initAtlas()
{
	FT_GlyphSlot g = face->glyph;
	int roww = 0;
	int rowh = 0;
	width = 0;
	height = 0;
	memset(c, 0, sizeof(c));

	/* Find minimum size for character texture */
	for(int i = 32; i < 128; ++i)
	{
		if(FT_Load_Char(face, i, FT_LOAD_RENDER)) 
		{
			std::cerr << "Loading character " << (char)i << " failed!\n";
			continue;
		}
		if(roww + g->bitmap.width + 1 >= MAXWIDTH)
		{
			width = width > roww ? width : roww;
			height += rowh;
			roww = 0;
			rowh = 0;
		}
		roww += g->bitmap.width + 1;
		rowh = rowh > g->bitmap.rows ? rowh : g->bitmap.rows;
	}

	width = width > roww ? width : roww;
	height += rowh;

	glBindTexture(GL_TEXTURE_2D, tex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	GLint swizzleMask[] = {GL_ONE, GL_ONE, GL_ONE, GL_RED};
	glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int ox = 0;
	int oy = 0;
	rowh = 0;

	for(int i = 32; i < 128; ++i)
	{
		if(FT_Load_Char(face, i, FT_LOAD_RENDER))
		{
			std::cerr << "Error loading character " << (char) i << '\n';
			continue;
		}

		if(ox + g->bitmap.width + 1 >= MAXWIDTH)
		{
			oy += rowh;
			rowh = 0;
			ox = 0;
		}

		glTexSubImage2D(GL_TEXTURE_2D, 0, ox, oy, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

		c[i].ax = g->advance.x >> 6;
		c[i].ay = g->advance.y >> 6;

		c[i].bw = g->bitmap.width;
		c[i].bh = g->bitmap.rows;

		c[i].bl = g->bitmap_left;
		c[i].bt = g->bitmap_top;

		c[i].tx = ox / (float)width;
		c[i].ty = oy / (float)height;

		rowh = rowh > g->bitmap.rows ? rowh : g->bitmap.rows;
		ox += g->bitmap.width+1;
	}

	std::cerr << "Generated a " << width << " x " << height << " ( " << width*height/MAXWIDTH << " kb) texture atlas!\n";
	checkGLErrors("TextRenderer::initAtlas()");

}

bool TextRenderer::loadFace(const char* path, int height)
{
	bool ret = !FT_New_Face(ft, path, numFaces++, &face);
	if(ret)
	{
		FT_Set_Pixel_Sizes(face, numFaces-1, height);
		initAtlas();
	}

	return ret;
}

bool TextRenderer::initGraphics()
{
	glGenTextures(1, &tex);
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);

	// Compile shader
	if(!textShader.loadFromShaderDir("text.vert", "text.frag", 0))
	{
		std::cerr << "Failed to compile Text-shader!!!\n";
		return false;
	}
	textShader.storeUniformLoc("sampler");

	checkGLErrors("TextureManager::initGraphics");
	return true;
}

void TextRenderer::renderText(const char *text, float x, float y, float sx, float sy)
{
	const unsigned char* p;

	glUseProgram(textShader.id);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(textShader.uniformLocs[0], 1);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glm::vec4* coords = new glm::vec4[6*strlen(text)];

	int i = 0;

	for(p = (unsigned char*)text;*p;++p)
	{
		float x2 = x + c[*p].bl * sx;
		float y2 = -y - c[*p].bt * sy;

		float w = c[*p].bw * sx;
		float h = c[*p].bh * sy;

		x += c[*p].ax * sx;
		y += c[*p].ay * sy;

		if(!w || !h) // Skip glyphs with no pixels
			continue;

		coords[i++] = glm::vec4(x2+w,		-y2,		c[*p].tx + c[*p].bw / width,		c[*p].ty);
		coords[i++] = glm::vec4(x2,		-y2,		c[*p].tx,								c[*p].ty);
		coords[i++] = glm::vec4(x2,		-y2-h,	c[*p].tx,								c[*p].ty + c[*p].bh / height);
		coords[i++] = glm::vec4(x2+w,		-y2,		c[*p].tx + c[*p].bw / width,		c[*p].ty);
		coords[i++] = glm::vec4(x2,		-y2-h,	c[*p].tx,								c[*p].ty + c[*p].bh / height);
		coords[i++] = glm::vec4(x2+w,		-y2-h,	c[*p].tx + c[*p].bw / width,		c[*p].ty + c[*p].bh / height);

	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*6*strlen(text), coords, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, i);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);

	checkGLErrors("TextureManager::renderText");
}
