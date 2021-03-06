#pragma once

#ifdef TROL_USE_OLD_OPENGL
	#include <GL/glew.h>
#else
	#include <GL3/gl3w.h>
#endif

#include <GL/glfw.h>
#include <GL/gl.h>

#include <cassert>
#include <vector>
#include <string>
#include <map>
#include "../shader.h"
#include "../glutils.h"
#include "../../TROLUtil/error.h"

class ShaderManager
{
public:
	static const ShaderHandle TROLLO_INVALID_SHADER = -1;
	static const std::string shaderDir;

	enum BASIC_SHADERS { MVP_TEXTURED, TEXT, PLAIN_TEXTURED, MESH_EXPLODER };

	ShaderHandle loadFromPath(const char* id, const char* vPath, const char* fPath, const char* gPath);
	ShaderHandle loadFromShaderDir(const char* id, const char* vPath, const char* fPath, const char* gPath);
	Shader& getShader(const char* id) { auto a = shadersString.find(id); assert(a != shadersString.end()); return shaders[a->second];}
	Shader& getShader(ShaderHandle i) { assert(isValidHandle(i)); return shaders[i]; }
	uint8_t storeUniformLoc(ShaderHandle h, const char* uniformName) { assert(isValidHandle(h)); return shaders[h].storeUniformLoc(uniformName); }

private:
	friend class Root;
	ShaderManager() {}
	TROLLOERROR init();
	TROLLOERROR initBasicShaders();
	void destroy() { for(ShaderHandle i = 0; i < numShaders; ++i) glDeleteShader(shaders[i].id); numShaders = 0; shadersString.clear(); shaders.clear(); }

	bool isValidHandle(ShaderHandle i) { return i != TROLLO_INVALID_SHADER && i >= 0 && i <= shaders.size(); }
	int numShaders;
	std::map<std::string, ShaderHandle> shadersString; // For access by shader name (contains index to vector)
	std::vector<Shader> shaders; // For access by shader index
};
