#include "shadermanager.h"
#include "../glutils.h"
#include <iostream>

#ifdef TROL_USE_OLD_OPENGL
const std::string ShaderManager::shaderDir="shaders_120/";
#else
const std::string ShaderManager::shaderDir="shaders_330/";
#endif

void ShaderManager::init()
{
	numShaders = 0;
	initBasicShaders();
}

void ShaderManager::initBasicShaders()
{
	loadFromShaderDir("mvp_tex", "plainMVP.vert", "plainTextured.frag", 0);
	storeUniformLoc(MVP_TEXTURED, "MVP");
	storeUniformLoc(MVP_TEXTURED, "sampler");

	loadFromShaderDir("text", "text.vert", "text.frag", 0);
	storeUniformLoc(TEXT, "sampler");

	loadFromShaderDir("plain_tex", "plain.vert", "plainTextured.frag", 0);
	storeUniformLoc(PLAIN_TEXTURED, "sampler");
}

void printShaderInfoLog(GLint shader)
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

	if (infoLogLen > 1)
	{
		infoLog = (GLchar*)malloc(sizeof(GLchar)*infoLogLen);

		glGetShaderInfoLog(shader,infoLogLen, &charsWritten, infoLog);
		printf("InfoLog:\n%s\n", infoLog);
		free(infoLog);
	}
	checkGLErrors("printShaderInfoLog");
}


GLint readShaderSource(const char* path, GLchar** target)
{
	if(!path)
		return 0;
	FILE* file = fopen(path, "rb");
	if(!file)
		return 0;
	fseek(file, 0L, SEEK_END);
	GLint size = ftell(file);
	fseek(file, 0L, SEEK_SET);

	*target = (GLchar*)malloc(sizeof(GLchar)*size);
	fread(*target, sizeof(GLchar), size, file);

	fclose(file);

	return size;
}

ShaderHandle ShaderManager::loadFromShaderDir(const char* id, const char* vPath, const char* fPath, const char* gPath)
{
	return loadFromPath(id, (ShaderManager::shaderDir + vPath).c_str(),
		(ShaderManager::shaderDir + fPath).c_str(),
		gPath ? (ShaderManager::shaderDir + gPath).c_str() : 0);
}


ShaderHandle ShaderManager::loadFromPath(const char* id, const char* vPath, const char* fPath, const char* gPath)
{
	GLchar* vertexSource = 0, *fragmentSource = 0, *geometrySource = 0;
	GLint vSize = 0, fSize = 0, gSize = 0;
	vSize = readShaderSource(vPath, &vertexSource);
	fSize = readShaderSource(fPath, &fragmentSource);
	gSize = readShaderSource(gPath, &geometrySource);

	GLuint v,f,g;

	Shader s;

	if(!vSize || !fSize) 
	{
		free(vertexSource); free(fragmentSource); free(geometrySource);
		return TROLLO_INVALID_SHADER;
	}
	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	if(gSize) g = glCreateShader(GL_GEOMETRY_SHADER);

	const GLchar* vcode = vertexSource, // need consts for opengl
		*fcode = fragmentSource,
		*gcode = geometrySource;

	if(vSize) glShaderSource(v, 1, &vcode, &vSize);
	if(fSize) glShaderSource(f, 1, &fcode, &fSize);
	if(gSize) glShaderSource(g, 1, &gcode, &gSize);

	GLint compiled;

	if(vSize)
	{
		glCompileShader(v);
		glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
		free(vertexSource); free(fragmentSource); free(geometrySource);
			printf("Vertex shader %s not compiled.\n", vPath);
			printShaderInfoLog(v);
			return TROLLO_INVALID_SHADER;
		}
		printf("Vertex shader %s compiled succesfully.\n", vPath);
	}

	if(fSize)
	{
		glCompileShader(f);
		glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
		free(vertexSource); free(fragmentSource); free(geometrySource);
			printf("Fragment shader %s not compiled.\n", fPath);
			printShaderInfoLog(f);
			return TROLLO_INVALID_SHADER;
		}
		printf("Fragment shader %s compiled succesfully.\n", fPath);
	}

	if(gSize)
	{
		glCompileShader(g);
		glGetShaderiv(g, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
		free(vertexSource); free(fragmentSource); free(geometrySource);
			printShaderInfoLog(g);
			printf("Geometry shader %s not compiled.\n", gPath);
			return TROLLO_INVALID_SHADER;
		}
		printf("Geometry shader %s compiled succesfully.\n", gPath);
	}

	s.id = glCreateProgram();
	if(vSize) glAttachShader(s.id, v);
	if(fSize) glAttachShader(s.id, f);
	if(gSize) glAttachShader(s.id, g);

#ifdef TROL_USE_OLD_OPENGL
	glBindAttribLocation(s.id, 0, "in_Position");
	glBindAttribLocation(s.id, 1, "in_Normal");
	glBindAttribLocation(s.id, 2, "in_Texcoord");
#endif

	glLinkProgram(s.id);
	glUseProgram(s.id);

	glGetProgramiv(s.id, GL_LINK_STATUS, &compiled);
	free(vertexSource); free(fragmentSource); free(geometrySource);
	if (!compiled)
		return TROLLO_INVALID_SHADER;

	if(vSize) printShaderInfoLog(v);
	if(fSize) printShaderInfoLog(f);
	if(gSize) printShaderInfoLog(g);


	shaders.push_back(s);
	shadersString[id] = numShaders;
	checkGLErrors("ShaderManager::loadFromFile");

	return numShaders++;
}
