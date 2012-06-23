#include "model.h"
#include "glutils.h"

/**
 * Same image on each face
 * */
void Model::makeTexturedCube()
{
	setAttribNumbers(3,0,2); // No normals for now

	GLfloat vbuffer[8][5] = {
									{-1.0f, -1.0f, -1.0f, 0.0f, 1.0f},
									{-1.0f, 1.0f, -1.0f, 1.0f, 1.0f},
									{1.0f, 1.0f, -1.0f, 1.0f, 0.0f},
									{1.0f, -1.0f, -1.0f, 0.0f, 0.0f},

									{-1.0f, -1.0f, 1.0f, 0.0f, 0.0f},
									{-1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
									{1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
									{1.0f, -1.0f, 1.0f, 0.0f, 1.0f},
									};


	// By default, CCW polygons are front-facing!
	glm::uvec3 polygons2[12]; // 2 Triangles for each face
	// Back
	polygons2[0] = glm::uvec3(0,1,2);
	polygons2[1] = glm::uvec3(2,3,0);
	// Right
	polygons2[2] = glm::uvec3(7,3,6);
	polygons2[3] = glm::uvec3(3,2,6);
	// Front
	polygons2[4] = glm::uvec3(4,6,5);
	polygons2[5] = glm::uvec3(4,7,6);
	// Left
	polygons2[6] = glm::uvec3(0,5,1);
	polygons2[7] = glm::uvec3(0,4,5);
	// Top
	polygons2[8] = glm::uvec3(5,6,1);
	polygons2[9] = glm::uvec3(6,2,1);
	// Bottom
	polygons2[10] = glm::uvec3(7,4,0);
	polygons2[11] = glm::uvec3(0,3,7);

	loadVertexData(&vbuffer[0][0], &polygons2[0], 8, 12);
}

void Model::makeTriangle()
{
	setAttribNumbers(3,0,0); // No normals for now

	GLfloat vbuffer[3][3] = {
									{-1.0f, -1.0f, 0.0f},
									{0.0f, 1.0f, 0.0f},
									{1.0f, -1.0f, 0.0f}
									};


	// By default, CCW polygons are front-facing!
	glm::uvec3 polygons2; // 2 Triangles for each face
	// Back
	polygons2 = glm::uvec3(0,2,1);

	loadVertexData(&vbuffer[0][0], &polygons2, 3, 1);
}

void Model::makeTexturedQuad()
{
	// By default, CCW polygons are front-facing!
	setAttribNumbers(3,0,2); // No normals for now

	GLfloat vbuffer[4][5] = {
									{-1.0f, -1.0f, 0.0f, 0.0f, 0.0f},
									{-1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
									{1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
									{1.0f, -1.0f, 0.0f, 1.0f, 0.0f}
									};
	glm::uvec3 polygons2[2];
	polygons2[0] = glm::uvec3(0,2,1);
	polygons2[1] = glm::uvec3(0,3,2);

	loadVertexData(&vbuffer[0][0], &polygons2[0], 4, 2);
}

bool Model::loadFromFile(const char* path)
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

	vertexData = (GLfloat*)new uint8_t[numVertices*vertexBytes];
	indices = new glm::uvec3[numFaces];

	infile.read((char*)vertexData, sizeof(VertexNormalTexcrd)*numVertices);
	infile.read((char*)indices, sizeof(glm::uvec3)*numFaces);

	std::cout << "Read model with " << numVertices << " vertices and " << numFaces << " faces.\n";
	initBuffers();

	return true;
}

void Model::setAttribNumbers(uint8_t* a) // a needs to be an uint8_t array of at least 4 elements
{
	memcpy(attribNumbers, a, 4);
	vertexBytes = 0;
	for(int i = 0; i < 4; ++i)
		vertexBytes += attribNumbers[i];
	vertexBytes *= sizeof(GLfloat);
}

void Model::setAttribNumbers(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	attribNumbers[0] = a;
	attribNumbers[1] = b;
	attribNumbers[2] = c;
	attribNumbers[3] = d;
	vertexBytes = (a+b+c+d)*sizeof(GLfloat);
}

void Model::setAttribNumbers(AttribType a)
{
	switch(a)
	{
		case VertexNormal:
			setAttribNumbers(3,3);
			break;
		case VertexNormalColor:
			setAttribNumbers(3,3,3);
			break;
		case VertexNormalTexcrd:
			setAttribNumbers(3,3,2);
			break;
	}
}

void Model::loadVertexData(const void *vertexData, const glm::uvec3* indices, int numVertices, int numFaces)
{
	if(this->vertexData)
		destroyBuffers();
	this->numVertices = numVertices;
	this->numFaces = numFaces;
	this->vertexData = (GLfloat*)new uint8_t[numVertices*vertexBytes];
	this->indices = new glm::uvec3[numFaces];

	memcpy(this->vertexData, vertexData, numVertices*vertexBytes);
	memcpy(this->indices, indices, numFaces*sizeof(glm::uvec3));

	initBuffers();
}

void Model::initBuffers()
{
	// initialize VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// initialize VBO for model vertices and polygon vertex indices
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVertices*vertexBytes, vertexData, GL_STATIC_DRAW);

	int accumOffset = 0;
	for(int i = 0; i < 4; ++i)
		if(attribNumbers[i])
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, attribNumbers[i], GL_FLOAT, GL_FALSE, vertexBytes, (GLvoid*)accumOffset);
			accumOffset += attribNumbers[i]*sizeof(GLfloat);
		}

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numFaces*sizeof(glm::uvec3), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Model::Model()
	:numVertices(0),
	numFaces(0),
	vertexData(0),
	indices(0),
	VAO(GL_INVALID_VALUE),
	vertexBuffer(GL_INVALID_VALUE),
	indexBuffer(GL_INVALID_VALUE),
	texture(GL_INVALID_VALUE)
{
	for(int i = 0; i < 4; ++i) attribNumbers[i] = 0;
}

void Model::destroyBuffers()
{
	for(int i = 0; i < 4; ++i) attribNumbers[i] = 0;
	delete[] vertexData; vertexData = 0;
	delete[] indices; indices = 0;
	if(VAO != GL_INVALID_VALUE)
		glDeleteVertexArrays(1, &VAO);
	if(vertexBuffer != GL_INVALID_VALUE)
		glDeleteBuffers(1, &vertexBuffer);
	if(indexBuffer != GL_INVALID_VALUE)
		glDeleteBuffers(1, &indexBuffer);
}

Model::~Model() // THIS NEEDS TO BE CHANGED IF COPYING MODELS IS A NECESSARY FEATURE
{
	destroyBuffers();
}


