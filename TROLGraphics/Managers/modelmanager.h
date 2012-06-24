#pragma once

#include <vector>
#include <map>
#include <string>
#include <stdint.h>

class Renderer;

class ModelManager
{
public:
	void addFromTROLLO(const char* id, const char* path, const char* textureID=0);
	void addFromPointer(const char* id, GLfloat* vertexData, GLuint* polygons, int numVertices, int numFaces, const uint8_t* attribNums, const char* textureName);
	const Model& getModel(const std::string& s) { return models[s]; }
private:
	std::map<std::string, Model> models;
	friend Renderer::Renderer(const std::vector<Entity>&, int, int);
	void init();
	void addTexturedCube();
	void addTexturedQuad();
	void addTriangle();
};
