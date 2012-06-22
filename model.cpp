#include "model.h"

/**
 * Same image on each face
 * */
template<>
void Model<VertexNormalTexcrd>::makeTexturedCube()
{
	// By default, CCW polygons are front-facing!
	VertexNormalTexcrd v[8];
	v[0].vertex = glm::vec3(-1.0f, -1.0f, -1.0f);
	v[1].vertex = glm::vec3(-1.0f, 1.0f, -1.0f);
	v[2].vertex = glm::vec3(1.0f, 1.0f, -1.0f);
	v[3].vertex = glm::vec3(1.0f, -1.0f, -1.0f);

	v[4].vertex = glm::vec3(-1.0f, -1.0f, 1.0f);
	v[5].vertex = glm::vec3(-1.0f, 1.0f, 1.0f);
	v[6].vertex = glm::vec3(1.0f, 1.0f, 1.0f);
	v[7].vertex = glm::vec3(1.0f, -1.0f, 1.0f);

	v[0].texcrd = glm::vec2(0.0f, 1.0f);
	v[1].texcrd = glm::vec2(1.0f, 1.0f);
	v[2].texcrd = glm::vec2(1.0f, 0.0f);
	v[3].texcrd = glm::vec2(0.0f, 0.0f);

	v[4].texcrd = glm::vec2(0.0f, 0.0f);
	v[5].texcrd = glm::vec2(1.0f, 0.0f);
	v[6].texcrd = glm::vec2(1.0f, 1.0f);
	v[7].texcrd = glm::vec2(0.0f, 1.0f);

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
	loadVertexData(v, &polygons2[0], 8, 12);
}

template<>
void Model<VertexNormalTexcrd>::makeTexturedQuad()
{
	// By default, CCW polygons are front-facing!
	VertexNormalTexcrd v[4];
	v[0].vertex = glm::vec3(-1.0f, -1.0f, 0.0f);
	v[1].vertex = glm::vec3(-1.0f, 1.0f, 0.0f);
	v[2].vertex = glm::vec3(1.0f, 1.0f, 0.0f);
	v[3].vertex = glm::vec3(1.0f, -1.0f, 0.0f);

	v[0].normal = v[1].normal = v[2].normal = v[3].normal = glm::vec3(0.0f, 0.0f, 1.0f); 

	v[0].texcrd = glm::vec2(0,0);
	v[1].texcrd = glm::vec2(0,1);
	v[2].texcrd = glm::vec2(1,1);
	v[3].texcrd = glm::vec2(1,0);

	glm::uvec3 polygons2[2];
	polygons2[0] = glm::uvec3(0,2,1);
	polygons2[1] = glm::uvec3(0,3,2);

	loadVertexData(v, &polygons2[0], 4, 2);
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