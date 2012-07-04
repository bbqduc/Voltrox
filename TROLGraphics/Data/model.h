#pragma once

#ifdef TROL_USE_OLD_OPENGL
#include <GL/glew.h>
#else
#include <GL3/gl3w.h>
#endif

#include <string>
#include <stdint.h>
#include <cstdlib>
#include <cstring>
#include <map>
#include <btBulletCollisionCommon.h>

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
	GLuint* indices;

	btTriangleIndexVertexArray btVertexData;
	btConvexTriangleMeshShape collisionShape; 

	btVector3 getInertia(btScalar mass) { btVector3 ret(0.0f,0.0f,0.0f); collisionShape.calculateLocalInertia(mass, ret); return ret; }
	void printVertexData();

private:

	void setAttribNumbers(AttribType a);
	void setAttribNumbers(const uint8_t*);
	void setAttribNumbers(uint8_t a, uint8_t b=0, uint8_t c=0, uint8_t d=0);

	Model();

	void destroyBuffers();

	void createCollisionShape()
	{
		btVertexData = btTriangleIndexVertexArray(numFaces, (int*)indices, sizeof(GLuint)*3, numVertices, vertexData, vertexBytes);
		collisionShape = btConvexTriangleMeshShape(&btVertexData, true);
	}

};

