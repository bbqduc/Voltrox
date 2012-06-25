#include "model.h"
#include "../glutils.h"

void Model::setAttribNumbers(const uint8_t* a) // a needs to be an uint8_t array of at least 4 elements
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

Model::Model()
	:numVertices(0),
	numFaces(0),
	vertexData(0),
	indices(0),
	vao(GL_INVALID_VALUE),
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
	if(vao != GL_INVALID_VALUE)
		glDeleteVertexArrays(1, &vao);
	if(vertexBuffer != GL_INVALID_VALUE)
		glDeleteBuffers(1, &vertexBuffer);
	if(indexBuffer != GL_INVALID_VALUE)
		glDeleteBuffers(1, &indexBuffer);
}