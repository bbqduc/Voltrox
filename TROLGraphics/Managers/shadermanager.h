#pragma once

#ifdef TROL_USE_OLD_OPENGL
	#include <GL/glew.h>
#else
	#include <GL3/gl3w.h>
#endif

#include <GL/glfw.h>
#include <GL/gl.h>

#include <vector>
#include <string>
#include <map>
#include "../shader.h"
#include "../glutils.h"

class ShaderManager
{
public:
	enum SHADER { MVP_TEXTURED=0 };

	ShaderManager() : numShaders(0) {}

	Shader& loadFromPath(const char* id, const char* vPath, const char* fPath, const char* gPath);
	Shader& loadFromShaderDir(const char* id, const char* vPath, const char* fPath, const char* gPath);
	Shader& getShader(const char* id) { auto a = shadersString.find(id); if(a == shadersString.end()) throw TrolloException("Requested NULL shader!\n"); else return shaders[a->second];}
	Shader& getShader(int i) { return shaders[i]; }

	static const std::string shaderDir;
private:
	int numShaders;
	std::map<std::string, int> shadersString; // For access by shader name (contains index to vector)
	std::vector<Shader> shaders; // For access by shader index
};
