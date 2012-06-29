#include "modelmanager.h"
#include "../glutils.h"

void ModelManager::init(GLuint defaultTexture)
{
	addFromTROLLO("cube_tex", "resources/cube.trollo", defaultTexture);
//	addTexturedCube(defaultTexture);
	addTexturedQuad(defaultTexture);
	addTriangle();
}

void ModelManager::addTriangle()
{
	GLfloat vbuffer[3][3] = {
									{0.0f, 1.0f, 0.0f},
									{-1.0f, -1.0f, 0.0f},
									{1.0f, -1.0f, 0.0f}
									};


	// By default, CCW polygons are front-facing!
	glm::uvec3 polygons2; // 2 Triangles for each face
	// Back
	polygons2 = glm::uvec3(0,1,2);

	uint8_t attribNums[4] = {3,0,0,0};
	addFromPointer("triangle", &vbuffer[0][0], &polygons2[0], 3, 1, attribNums);	
}

void ModelManager::addTexturedQuad(GLuint defaultTexture)
{
	// By default, CCW polygons are front-facing!
	GLfloat vbuffer[4][5] = {
									{-1.0f, -1.0f, 0.0f, 0.0f, 0.0f},
									{-1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
									{1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
									{1.0f, -1.0f, 0.0f, 1.0f, 0.0f}
									};
	glm::uvec3 polygons2[2];
	polygons2[0] = glm::uvec3(0,2,1);
	polygons2[1] = glm::uvec3(0,3,2);

	uint8_t attribNums[4] = {3,0,2,0};
	addFromPointer("quad_tex", &vbuffer[0][0], &polygons2[0][0], 4, 2, attribNums, defaultTexture);	
}

void ModelManager::addTexturedCube(GLuint defaultTexture)
{
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

	uint8_t attribNums[4] = {3,0,2,0};
	addFromPointer("cube_tex", &vbuffer[0][0], &polygons2[0][0], 8, 12, attribNums, defaultTexture);	
}

void ModelManager::addFromPointer(const char* id, GLfloat* vertexData, GLuint* polygons, int numVertices, int numFaces, const uint8_t* attribNums, GLuint texture)
{
	Model& m = models[id];
	m.setAttribNumbers(attribNums);
	if(m.vertexData)
		m.destroyBuffers();
	m.numVertices = numVertices;
	m.numFaces = numFaces;
	m.vertexData = (GLfloat*)new uint8_t[m.numVertices*m.vertexBytes];
	m.indices = new glm::uvec3[m.numFaces];

	memcpy(m.vertexData, vertexData, m.numVertices*m.vertexBytes);
	memcpy(m.indices, polygons, m.numFaces*sizeof(glm::uvec3));
	m.texture = texture;
	
	initBuffers(m);
}

void ModelManager::initBuffers(Model& m)
{
	// initialize VAO
	glGenVertexArrays(1, &m.vao);
	glBindVertexArray(m.vao);

	// initialize VBO for model vertices and polygon vertex indices
	glGenBuffers(1, &m.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m.vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m.numVertices*m.vertexBytes, m.vertexData, GL_STATIC_DRAW);

	int accumOffset = 0;
	for(int i = 0; i < 4; ++i)
		if(m.attribNumbers[i])
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, m.attribNumbers[i], GL_FLOAT, GL_FALSE, m.vertexBytes, (GLvoid*)accumOffset);
			accumOffset += m.attribNumbers[i]*sizeof(GLfloat);
		}

	glGenBuffers(1, &m.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.numFaces*sizeof(glm::uvec3), m.indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ModelManager::addFromTROLLO(const char* id, const char* path, GLuint texture)
{
	std::ifstream infile(path, std::ios_base::binary | std::ios_base::in);
	if(!infile)
		throw TrolloException("Could not open TROLLO model file.\n");
	int magic; infile.read((char*)&magic, sizeof(int));
	int mode; infile.read((char*)&mode, sizeof(int));
	if(magic != 1337 || mode != 1)
		throw TrolloException("Model file does not have a TROLLO header.\n");

	Model& m = models[id];
	
	m.vertexBytes = 0;
	infile.read((char*)&m.numVertices, sizeof(int));
	infile.read((char*)&m.numFaces, sizeof(int));
	for(int i = 0; i < 4; ++i)
	{
		int t;
		infile.read((char*)&t, sizeof(int));
		m.attribNumbers[i] = t;
		m.vertexBytes += m.attribNumbers[i];
	}
	m.vertexBytes *= sizeof(GLfloat);

	m.vertexData = (GLfloat*)new uint8_t[m.numVertices*m.vertexBytes];
	m.indices = new glm::uvec3[m.numFaces];

	infile.read((char*)m.vertexData, m.vertexBytes*m.numVertices);
	infile.read((char*)m.indices, sizeof(glm::uvec3)*m.numFaces);
	m.texture = texture;

	std::cout << "Read model '" << id << "' with " << m.numVertices << " vertices and " << m.numFaces << " faces.\n";

//	m.printVertexData();

	initBuffers(m);
}
