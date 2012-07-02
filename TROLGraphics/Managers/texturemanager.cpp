#include "texturemanager.h"

void TextureManager::init()
{
	addFromBMP("default", "resources/ship.bmp");
	addFromPNG("skybox", "resources/space.png");
}

GLuint TextureManager::addFromBMP(const std::string& id, const std::string& texturePath)
{
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char* data;

	FILE* file = fopen(texturePath.c_str(), "rb");
	if(!file)
		return GL_INVALID_VALUE;
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

	glGenTextures(1, &textures[id]);
	glBindTexture(GL_TEXTURE_2D, textures[id]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete[] data;

	return textures[id];
}

GLuint TextureManager::addFromPNG(const std::string& id, const std::string& texturePath)
{
	FILE *fp = fopen(texturePath.c_str(), "rb");
	if(!fp)
		return GL_INVALID_VALUE;
	png_byte header[8];
	fread(header, 1, 8, fp);
	if(png_sig_cmp(header, 0, 8))
	{
		fclose(fp);
		return GL_INVALID_VALUE;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png_ptr)
		return GL_INVALID_VALUE;

	png_infop info_ptr = png_create_info_struct(png_ptr);
	png_infop end_info = png_create_info_struct(png_ptr);
	if(!info_ptr || !end_info || setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		return GL_INVALID_VALUE;
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
		return GL_INVALID_VALUE;
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
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
            fclose(fp);
				return GL_INVALID_VALUE;
   }

	glGenTextures(1, &textures[id]);
	glBindTexture(GL_TEXTURE_2D, textures[id]);
	glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? GL_RGBA : GL_RGB, width, height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*) image_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	delete[] image_data;
	delete[] row_pointers;
	fclose(fp);

	return true;
}
