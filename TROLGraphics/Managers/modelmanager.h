#pragma once

#ifdef TROL_USE_OLD_OPENGL
	#include <GL/glew.h>
#else
	#include <GL3/gl3w.h>
#endif

#include <GL/glfw.h>
#include <GL/gl.h>

#include <vector>
#include <map>
#include <string>
#include <stdint.h>

#include "../Data/model.h"
#include "../glutils.h"
#include "../../TROLUtil/error.h"

class Renderer;

class ModelManager
{
public:
	TROLLOERROR addFromTROLLO(const char* id, const char* path, GLuint texture = GL_INVALID_VALUE);
	void addFromPointer(const char* id, GLfloat* vertexData, GLuint* polygons, int numVertices, int numFaces, const uint8_t* attribNums, GLuint texture = GL_INVALID_VALUE);
	Model& getModel(const std::string& s) { return models[s]; }
	void setModelTexture(const char* mid, GLuint tid) { models[mid].texture = tid; }
	
private:
	friend class Root;
	ModelManager() {}
	TROLLOERROR init(GLuint);
	void destroy()	{ for(auto i = models.begin(); i != models.end(); ++i) i->second.destroyBuffers(); models.clear(); }

	void initBuffers(Model&);
	std::map<std::string, Model> models;
	void addTexturedQuad(GLuint);
	void addTriangle();
};
