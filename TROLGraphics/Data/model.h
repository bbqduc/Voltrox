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
#include <map>

class ModelManager;

class Model
{
	friend class ModelManager;
	friend class std::map<std::string, Model>;
public:
	enum AttribType {VertexNormal, VertexNormalColor, VertexNormalTexcrd};
	GLuint vao, vertexBuffer, indexBuffer, texture;

	uint8_t attribNumbers[4]; // This is to avoid templatizing or virtualizing this class
	uint8_t vertexBytes;
	
	int numVertices, numFaces;
	GLfloat* vertexData;
	glm::uvec3* indices;

	void printVertexData();

private:

	void setAttribNumbers(AttribType a);
	void setAttribNumbers(const uint8_t*);
	void setAttribNumbers(uint8_t a, uint8_t b=0, uint8_t c=0, uint8_t d=0);

	Model();

	void initBuffers();
	void destroyBuffers();
};
