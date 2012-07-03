#include "renderer.h"
#include "../root.h"

#ifdef TROL_USE_OLD_OPENGL
#include <GL/glew.h>
#else
#include <GL3/gl3w.h>
#endif
#include <GL/glfw.h>
#include <GL/gl.h>
#include "glutils.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool Renderer::explodeAll=false;

void Renderer::init(int resX_, int resY_)
{
	resX = resX_;
	resY = resY_;
	perspective = glm::perspective(45.0f, (float)resX/resY, 1.0f, 1000.0f);
	initGL();
}

TROLLOERROR Renderer::initGL()
{
	if( !glfwInit()) 	
		return TROLLO_INIT_FAILURE;

#ifndef TROL_USE_OLD_OPENGL // Request core profile if possible
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	if(!glfwOpenWindow(resX,resY,8,8,8,8,24,0, GLFW_WINDOW))
	{
		glfwTerminate();
		return TROLLO_INIT_FAILURE;
	}
#ifdef TROL_USE_OLD_OPENGL
	if(glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return TROLLO_INIT_FAILURE;
	}
#else
	if(gl3wInit()) 
	{
		glfwTerminate();
		return TROLLO_INIT_FAILURE;
	}
	if(!gl3wIsSupported(3,3))
	{
		glfwTerminate();
		return TROLLO_INIT_FAILURE;
	}
#endif

	checkGLErrors("init");

	std::cout << "OpenGL version " << glGetString(GL_VERSION) << "\nGLSL : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
	std::cout << "Vendor : " << glGetString(GL_VENDOR) << "\nRenderer : " << glGetString(GL_RENDERER) << "\n\n";

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);	  

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetMousePos(resX / 2, resY / 2);

	checkGLErrors("post_init");
}

void Renderer::renderEntities(const btAlignedObjectArray<Entity>& entities)
{

	if(!explodeAll)
	{
		const Shader& s = Root::getSingleton().shaderManager.getShader(ShaderManager::MVP_TEXTURED);
		glUseProgram(s.id);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(s.uniformLocs[1], 0);
		float time = glfwGetTime();

		glm::mat4 cam(glm::lookAt(camera.pos, camera.pos + camera.view, camera.up));
		glm::mat4 m;

		btTransform trans;
		for(int i = 0; i < entities.size(); ++i)
		{
			const Entity& e = entities[i];

			e.motionState->getWorldTransform(trans);
			trans.getOpenGLMatrix(&m[0][0]);

			glm::mat4 MVP = perspective * cam * m;
			glUniformMatrix4fv(s.uniformLocs[0], 1, GL_FALSE, glm::value_ptr(MVP));

			glBindTexture(GL_TEXTURE_2D, e.model->texture);
			glBindVertexArray(e.model->vao);
			glBindBuffer(GL_ARRAY_BUFFER, e.model->vertexBuffer);
#ifdef TROL_USE_OLD_OPENGL // TROLOLOO COMPATIBILITY IS FUN
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e.model->indexBuffer);
#endif
			glDrawElements(GL_TRIANGLES, e.model->numFaces*3, GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}
	else
	{
		glDisable(GL_CULL_FACE);
		static float timee = 0.0f;
		timee += 0.1f;
		if(timee > 30.0f)
		{
			timee = 0.0f;
			explodeAll = false;
		}
		const Shader& s = Root::getSingleton().shaderManager.getShader(ShaderManager::MESH_EXPLODER);
		glUseProgram(s.id);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(s.uniformLocs[1], 0);
		glUniform3f(s.uniformLocs[2], 0.0f, 0.0f, -6.0f);
		glUniform1f(s.uniformLocs[3], timee);


		glm::mat4 cam(glm::lookAt(camera.pos, camera.pos + camera.view, camera.up));
		glm::mat4 m;

		btTransform trans;
		for(int i = 0; i < entities.size(); ++i)
		{
			const Entity& e = entities[i];

			e.motionState->getWorldTransform(trans);
			trans.getOpenGLMatrix(&m[0][0]);

			glm::mat4 MVP = perspective * cam * m;
			glUniformMatrix4fv(s.uniformLocs[0], 1, GL_FALSE, glm::value_ptr(MVP));

			glBindTexture(GL_TEXTURE_2D, e.model->texture);
			glBindVertexArray(e.model->vao);
			glBindBuffer(GL_ARRAY_BUFFER, e.model->vertexBuffer);
#ifdef TROL_USE_OLD_OPENGL // TROLOLOO COMPATIBILITY IS FUN
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e.model->indexBuffer);
#endif
			glDrawElements(GL_TRIANGLES, e.model->numFaces*3, GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnable(GL_CULL_FACE);
	}
		const Shader& s = Root::getSingleton().shaderManager.getShader(ShaderManager::MVP_TEXTURED);
		glUseProgram(s.id);
		glUniform1i(s.uniformLocs[1], 0);

	//glCullFace(GL_FRONT);
	glDisable(GL_CULL_FACE);
	glm::mat4 c = glm::lookAt(glm::vec3(0.0f),camera.view, camera.up);
	glm::mat4 f = perspective * c * glm::scale(glm::mat4(), glm::vec3(500.0f));
	const Model& skyBox = Root::getSingleton().modelManager.getModel("cube_tex");

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(s.uniformLocs[1], 0);
	glUniformMatrix4fv(s.uniformLocs[0], 1, GL_FALSE, glm::value_ptr(f));
	glBindTexture(GL_TEXTURE_2D, Root::getSingleton().textureManager.getTexture("skybox"));
	glBindVertexArray(skyBox.vao);
	glBindBuffer(GL_ARRAY_BUFFER, skyBox.vertexBuffer);
#ifdef TROL_USE_OLD_OPENGL // TROLOLOO COMPATIBILITY IS FUN
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyBox.indexBuffer);
#endif
	glDrawElements(GL_TRIANGLES, skyBox.numFaces*3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	checkGLErrors("Renderer::renderEntities()");
}


void Renderer::renderConsole(Console& c)
{
	//	renderText(c.getCurrentText(), 0.5, 0.5, 1.0, 1.0);
}
