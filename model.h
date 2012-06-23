#pragma once

#ifdef TROL_USE_OLD_OPENGL
#include <GL/glew.h>
#else
#include <GL3/gl3w.h>
#endif

#include <string>
#include <stdint.h>
#include <glm/glm.hpp>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <png.h>
#include <pnginfo.h>

class Model
{
public:
	enum AttribType {VertexNormal, VertexNormalColor, VertexNormalTexcrd};
	GLuint VAO, vertexBuffer, indexBuffer, texture;

	uint8_t attribNumbers[4]; // This is to avoid templatizing or virtualizing this class
	uint8_t vertexBytes;
	void setAttribNumbers(AttribType a);
	void setAttribNumbers(uint8_t*);
	void setAttribNumbers(uint8_t a, uint8_t b=0, uint8_t c=0, uint8_t d=0);
	
	public:	int numVertices, numFaces;
	GLfloat* vertexData;
	glm::uvec3* indices;

	bool loadFromFile(const char* path);
	void loadVertexData(const void *vertexData, const glm::uvec3* indices, int numVertices, int numFaces);
	bool loadTexturePNG(const std::string& texturepath);
	bool loadTextureBMP(std::string texturepath);

	void makeTexturedCube();
	void makeTexturedQuad();
	void makeTriangle();

	Model();
	~Model();

private:
	Model& operator=(const Model& rhs);
	Model(const Model&);

	void initBuffers();
	void destroyBuffers();
};