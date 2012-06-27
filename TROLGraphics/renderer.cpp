#include "renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef TROL_USE_OLD_OPENGL
#include <GL/glew.h>
#else
#include <GL3/gl3w.h>
#endif
#include <GL/glfw.h>
#include <GL/gl.h>
#include <exception>
#include "glutils.h"

Renderer::Renderer(const std::vector<Entity>& entities_, int resX_, int resY_)
	:entities(entities_),
//	renderThread(this->render),
	perspectiveProjection(glm::perspective(45.0f, (float)resX_/resY_, 1.0f, 1000.0f)),
	resX(resX_),
	resY(resY_)
{
	initGL(resX, resY);
	initBasicShaders();
	textureManager.addFromBMP("default", "resources/ship.bmp");
	textureManager.addFromPNG("skybox", "resources/space.png");
	textRenderer.initGraphics(shaderManager.getShader("text"));
	textRenderer.loadFace("resources/FreeSans.ttf");
	modelManager.init(textureManager.getTexture("default"));
}

void Renderer::initGL(int resX, int resY)
{
	if( !glfwInit()) 	
		throw TrolloException("GLFW init failed!\n");

	#ifndef TROL_USE_OLD_OPENGL // Request core profile if possible
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#endif

	if(!glfwOpenWindow(resX,resY,8,8,8,8,24,0, GLFW_WINDOW))
	{
		glfwTerminate();
		throw TrolloException("Couldn't open a window!\n");
	}
#ifdef TROL_USE_OLD_OPENGL
	if(glewInit() != GLEW_OK)
	{
		glfwTerminate();
		throw TrolloException("GLEW init failed!\n");
	}
#else
	if(gl3wInit()) 
	{
		glfwTerminate();
		throw TrolloException("GL3W init failed!\n");
	}
	if(!gl3wIsSupported(3,3))
	{
		glfwTerminate();
		throw TrolloException("OPENGL 3.3 not supported! (Recompile with -DTROL_USE_OLD_OPENGL)\n");
	}
#endif

	checkGLErrors("init");

	std::cout << "OpenGL version " << glGetString(GL_VERSION) << " GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);	  

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	checkGLErrors("post_init");
}

void Renderer::renderEntities()
{
	const Shader& s = shaderManager.getShader(ShaderManager::MVP_TEXTURED);
	glUseProgram(s.id);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(s.uniformLocs[1], 0);
	float time = glfwGetTime();
	for(auto i = entities.begin(); i != entities.end(); ++i)
	{
		glm::mat4 rot = glm::mat4_cast(i->orientation);
		glm::mat4 MVP = glm::translate(perspectiveProjection, i->position) * rot;
		glUniformMatrix4fv(s.uniformLocs[0], 1, GL_FALSE, glm::value_ptr(MVP));
		glBindTexture(GL_TEXTURE_2D, i->model->texture);
		glBindVertexArray(i->model->vao);
		glBindBuffer(GL_ARRAY_BUFFER, i->model->vertexBuffer);
#ifdef TROL_USE_OLD_OPENGL // TROLOLOO COMPATIBILITY IS FUN
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i->model->indexBuffer);
#endif
		glDrawElements(GL_TRIANGLES, i->model->numFaces*3, GL_UNSIGNED_INT, 0);
	}
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	const Shader& pt = shaderManager.getShader(2);
	const Model& skyBox = modelManager.getModel("cube_tex");
	glUseProgram(pt.id);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(pt.uniformLocs[0], 0);
	glBindTexture(GL_TEXTURE_2D, textureManager.getTexture("skybox"));
	glBindVertexArray(skyBox.vao);
	glBindBuffer(GL_ARRAY_BUFFER, skyBox.vertexBuffer);
#ifdef TROL_USE_OLD_OPENGL // TROLOLOO COMPATIBILITY IS FUN
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyBox.indexBuffer);
#endif
	glDrawElements(GL_TRIANGLES, skyBox.numFaces*3, GL_UNSIGNED_INT, 0);
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	checkGLErrors("Renderer::renderEntities()");
}

void Renderer::initBasicShaders()
{
	Shader& s = shaderManager.loadFromShaderDir("mvp_tex", "plainMVP.vert", "plainTextured.frag", 0);
	s.storeUniformLoc("MVP");
	s.storeUniformLoc("sampler");

	Shader& t = shaderManager.loadFromShaderDir("text", "text.vert", "text.frag", 0);
	t.storeUniformLoc("sampler");

	Shader& pt = shaderManager.loadFromShaderDir("plain_tex", "plain.vert", "plainTextured.frag", 0);
	pt.storeUniformLoc("sampler");
}

// Returns the shader index in the shaders vector
Shader& Renderer::addShader(const char* id, const char* vPath, const char* fPath, const char* gPath)
{
	return shaderManager.loadFromShaderDir(id, vPath, fPath, gPath);
}

void Renderer::renderText(const char* text, float x, float y, float scaleX, float scaleY)
{
	textRenderer.renderText(text, x, y, scaleX/resX, scaleY/resY);
}

void Renderer::renderConsole(Console& c)
{
	renderText(c.getCurrentText(), 0.5, 0.5, 1.0, 1.0);
}
