#include "shader.h"

#include <cstdlib>
#include <cstdio>

#ifdef TROL_USE_OLD_OPENGL
	const std::string Shader::shaderPath="shaders_120/";
#else
	const std::string Shader::shaderPath="shaders_330/";
#endif

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

bool Shader::loadFromShaderDir(const char* vPath, const char* fPath, const char* gPath)
{
	return loadFromFile((Shader::shaderPath + vPath).c_str(),
			(Shader::shaderPath + fPath).c_str(),
			gPath ? (Shader::shaderPath + gPath).c_str() : 0);
}


bool Shader::loadFromFile(const char* vPath, const char* fPath, const char* gPath)
{
	GLchar* vertexSource = 0, *fragmentSource = 0, *geometrySource = 0;
	GLint vSize = 0, fSize = 0, gSize = 0;
	vSize = readShaderSource(vPath, &vertexSource);
	fSize = readShaderSource(fPath, &fragmentSource);
	gSize = readShaderSource(gPath, &geometrySource);

	GLuint v,f,g;

	if(!vSize || !fSize) return false;
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
			printf("Vertex shader %s not compiled.\n", vPath);
			printShaderInfoLog(v);
			return false;
		}
		printf("Vertex shader %s compiled succesfully.\n", vPath);
	}

	if(fSize)
	{
		glCompileShader(f);
		glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			printf("Fragment shader %s not compiled.\n", fPath);
			printShaderInfoLog(f);
			return false;
		}
		printf("Fragment shader %s compiled succesfully.\n", fPath);
	}

	if(gSize)
	{
		glCompileShader(g);
		glGetShaderiv(g, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			printf("Geometry shader %s not compiled.\n", gPath);
			printShaderInfoLog(g);
			return false;
		}
		printf("Geometry shader %s compiled succesfully.\n", gPath);
	}

	id = glCreateProgram();
	if(vSize) glAttachShader(id, v);
	if(fSize) glAttachShader(id, f);
	if(gSize) glAttachShader(id, g);

	glLinkProgram(id);
	glUseProgram(id);

	if(vSize) printShaderInfoLog(v);
	if(fSize) printShaderInfoLog(f);
	if(gSize) printShaderInfoLog(g);

	free(vertexSource); free(fragmentSource); free(geometrySource);

	return true;
}

uint8_t Shader::storeUniformLoc(const char* name)
{
	uniformLocs[numUniforms] = glGetUniformLocation(id, name);	
	stringLocations[name] = uniformLocs[numUniforms];
	return numUniforms++;
}
