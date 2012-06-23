#pragma once

#include <map>
#include <string>

class TextureManager
{
public:
	TextureManager() {};
	GLuint getTexture(const std::string& s) { return textures[s]; }
	GLuint addFromPNG(const std::string&, const std::string&);
	GLuint addFromBMP(const std::string&, const std::string&);
private:
	std::map<std::string, GLuint> textures;
};