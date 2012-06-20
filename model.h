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
#include <png.h>
#include <pnginfo.h>

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
	bool loadTexturePNG(const std::string& texturepath);
	bool loadTextureBMP(std::string texturepath);

	void fullScreenQuadModel();
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
		glVertexAttribPointer(2, numThirdChannel, GL_FLOAT, GL_FALSE, sizeof(T), (GLvoid*)24); // COLOR / TEXCOORDS
	}

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numFaces*sizeof(glm::uvec3), indices, GL_STATIC_DRAW);


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

template<>
void Model<VertexNormalTexcrd>::fullScreenQuadModel()
{
	VertexNormalTexcrd v[4];
	v[0].vertex = glm::vec3(-1.0f, -1.0f, -1.0f);
	v[1].vertex = glm::vec3(-1.0f, 1.0f, -1.0f);
	v[2].vertex = glm::vec3(1.0f, 1.0f, -1.0f);
	v[3].vertex = glm::vec3(1.0f, -1.0f, -1.0f);

	v[0].normal = glm::vec3(-1.0f, -1.0f, -1.0f);
	v[1].normal = glm::vec3(-1.0f, 1.0f, -1.0f);
	v[2].normal = glm::vec3(1.0f, 1.0f, -1.0f);
	v[3].normal = glm::vec3(1.0f, -1.0f, -1.0f);

	v[0].texcrd = glm::vec2(0,0);
	v[1].texcrd = glm::vec2(0,1);
	v[2].texcrd = glm::vec2(1,1);
	v[3].texcrd = glm::vec2(1,0);

	glm::uvec3 polygons2[2];
	polygons2[0] = glm::uvec3(0,1,2);
	polygons2[1] = glm::uvec3(2,3,0);

	loadVertexData(v, &polygons2[0], 4, 2);
}

template <typename T>
bool Model<T>::loadTexturePNG(const std::string& texturePath)
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
template <typename T>
bool Model<T>::loadTextureBMP(std::string texturePath)
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

#endif
