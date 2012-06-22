#include "model.h"

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

bool Model::loadTexturePNG(const std::string& texturePath)
{
	FILE *fp = fopen(texturePath.c_str(), "rb");
	if(!fp)
		return false;
	png_byte header[8];
	fread(header, 1, 8, fp);
	if(png_sig_cmp(header, 0, 8))
	{
		fclose(fp);
		return false;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png_ptr)
		return false;

	png_infop info_ptr = png_create_info_struct(png_ptr);
	png_infop end_info = png_create_info_struct(png_ptr);
	if(!info_ptr || !end_info || setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		return false;
	}
	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	int bit_depth, color_type;
	png_uint_32 twidth, theight;

	png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type, NULL, NULL, NULL);

	int width = twidth;
	int height = theight;

	png_read_update_info(png_ptr, info_ptr);

	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	png_byte *image_data = new png_byte[rowbytes * height];
	png_bytepp row_pointers = new png_bytep[height];

	if(!image_data || !row_pointers) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		delete[] image_data;
		fclose(fp);
		return false;
	}

	for(int i = 0; i < height; ++i)
		row_pointers[height - 1 - i] = image_data + i * rowbytes;

	png_read_image(png_ptr, row_pointers);

	bool hasAlpha;
	switch (info_ptr->color_type) {
        case PNG_COLOR_TYPE_RGBA:
            hasAlpha = true;
            break;
        case PNG_COLOR_TYPE_RGB:
            hasAlpha = false;
            break;
        default:
            std::cout << "Color type " << info_ptr->color_type << " not supported" << std::endl;
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
            fclose(fp);
            return false;
   }

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? GL_RGBA : GL_RGB, width, height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*) image_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	delete[] image_data;
	delete[] row_pointers;
	fclose(fp);

	return true;
}

bool Model::loadTextureBMP(std::string texturePath)
{
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char* data;

	FILE* file = fopen(texturePath.c_str(), "rb");
	fread(header, 1, 54, file);
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if(imageSize == 0) imageSize = width*height*3;
	if(dataPos == 0) dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data,1,imageSize,file);
	fclose(file);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}
