#ifndef MODEL_H
#define MODEL_H

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

struct VertexNormal
{
	glm::vec3 vertex;
	glm::vec3 normal;
};

struct VertexNormalColor : public VertexNormal
{
	glm::vec3 color;
};

struct VertexNormalTexcrd : public VertexNormal
{
	glm::vec2 texcrd;
};


template <typename T>
class Model
{
	public:	int numVertices, numIndices;
	T* vertexData;
	glm::uvec3* indices;

	GLuint VAO, vertexBuffer, indexBuffer, texture;

	void loadVertexData(const T *vertexData, int numVertices, int numIndices);
	void destroyBuffers();
//	void initTexture(const std::string& texturepath); NYI

	Model();
	~Model();
	private:
	void initBuffers();
	Model(const Model&);
	Model& operator=(const Model& rhs);
};

template <typename T>
void Model<T>::loadVertexData(const T *vertexData, const glm::uvec3* indices, int numVertices, int numIndices)
{
	if(this->vertexData)
		destroyBuffers();
	this->numVertices = numVertices;
	this->numIndices = numIndices;
	this->vertexData = new T[numVertices];
	this->indices = new glm::uvec3[numIndices];

	memcpy(this->vertexData, vertexData, numVertices*sizeof(T));
	memcpy(this->indices, indices, numIndices*sizeof(glm::uvec3));

	initBuffers();
}

template <typename T>
void Model<T>::initBuffers()
{
	// initialize VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// initialize VBO for model vertices and polygon vertex indices
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(T), vertexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(T), 0);	// VERTICES
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(T), sizeof(glm::vec3)); // NORMALS
	int numThirdChannel = (sizeof(T) - 2*sizeof(glm::vec3)) / sizeof(GLfloat); // COMPILE-TIME CONSTANT
	if(numThirdChannel)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, numThirdChannel, GL_FLOAT, GL_FALSE, sizeof(T), 2*sizeof(glm::vec3)); // COLOR / TEXCOORDS
	}

	glBindVertexArray(0);
}

template <typename T>
Model<T>::Model()
	:numVertices(0),
	numIndices(0),
	vertexData(0),
	indices(0),
	VAO(GL_INVALID_VALUE),
	vertexBuffer(GL_INVALID_VALUE),
	indexBuffer(GL_INVALID_VALUE),
	texture(GL_INVALID_VALUE)
{
}

template <typename T>
void Model<T>::destroyBuffers()
{
	delete[] vertexData; vertexData = 0;
	delete[] indices; indices = 0;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

template <typename T>
Model::~Model() // THIS NEEDS TO BE CHANGED IF COPYING MODELS IS A NECESSARY FEATURE
{
	destroyBuffers();
}

#endif