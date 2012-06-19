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
#include <fstream>
#include <iostream>

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
	public:	int numVertices, numFaces;
	T* vertexData;
	glm::uvec3* indices;

	GLuint VAO, vertexBuffer, indexBuffer, texture;

	bool loadFromFile(const char* path);
	void loadVertexData(const T *vertexData, const glm::uvec3* indices, int numVertices, int numFaces);
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
void Model<T>::loadVertexData(const T *vertexData, const glm::uvec3* indices, int numVertices, int numFaces)
{
	if(this->vertexData)
		destroyBuffers();
	this->numVertices = numVertices;
	this->numFaces = numFaces;
	this->vertexData = new T[numVertices];
	this->indices = new glm::uvec3[numFaces];

	memcpy(this->vertexData, vertexData, numVertices*sizeof(T));
	memcpy(this->indices, indices, numFaces*sizeof(glm::uvec3));

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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(T), (GLvoid*)sizeof(glm::vec3)); // NORMALS
	int numThirdChannel = (sizeof(T) - 2*sizeof(glm::vec3)) / sizeof(GLfloat); // COMPILE-TIME CONSTANT
	if(numThirdChannel)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, numThirdChannel, GL_FLOAT, GL_FALSE, sizeof(T), (GLvoid*)(2*sizeof(glm::vec3))); // COLOR / TEXCOORDS
	}

	glBindVertexArray(0);
}

template <typename T>
Model<T>::Model()
	:numVertices(0),
	numFaces(0),
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
	if(VAO != GL_INVALID_VALUE)
		glDeleteVertexArrays(1, &VAO);
	if(vertexBuffer != GL_INVALID_VALUE)
		glDeleteBuffers(1, &vertexBuffer);
	if(indexBuffer != GL_INVALID_VALUE)
		glDeleteBuffers(1, &indexBuffer);
}

template <typename T>
Model<T>::~Model() // THIS NEEDS TO BE CHANGED IF COPYING MODELS IS A NECESSARY FEATURE
{
	destroyBuffers();
}

template <>
bool Model<VertexNormalTexcrd>::loadFromFile(const char* path)
{
	std::ifstream infile(path, std::ios_base::binary | std::ios_base::in);
	if(!infile)
		return false;
	int magic; infile.read((char*)&magic, sizeof(int));
	int mode; infile.read((char*)&mode, sizeof(int));
	if(magic != 1337 || mode != 1)
		return false;

	infile.read((char*)&numVertices, sizeof(int));
	infile.read((char*)&numFaces, sizeof(int));

	vertexData = new VertexNormalTexcrd[numVertices];
	indices = new glm::uvec3[numFaces];

	infile.read((char*)vertexData, sizeof(VertexNormalTexcrd)*numVertices);
	infile.read((char*)indices, sizeof(glm::uvec3)*numFaces);

	std::cout << "Read model with " << numVertices << " vertices and " << numFaces << " faces.\n";
	initBuffers();

	return true;
}


#endif
