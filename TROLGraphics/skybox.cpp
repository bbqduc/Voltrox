#include "skybox.h"
#include "../root.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void SkyboxRender::render()
{
	const Shader& s = Root::getSingleton().shaderManager.getShader(ShaderManager::MVP_TEXTURED);
	const Camera& cam = Root::getSingleton().engine->getCamera();
	const Model& skyBox = Root::getSingleton().modelManager.getModel("cube_tex");

	glUseProgram(s.id);
	// Texture sampler

	//glCullFace(GL_FRONT);
	glDisable(GL_CULL_FACE);
	glm::mat4 c = glm::lookAt(glm::vec3(0.0f),cam.view, cam.up);
	const glm::mat4& perspective = Root::getSingleton().renderManager.getPerspective();
	glm::mat4 f = perspective * c * glm::scale(glm::mat4(), glm::vec3(500.0f));

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(s.uniformLocs[1], 0);
	glUniformMatrix4fv(s.uniformLocs[0], 1, GL_FALSE, glm::value_ptr(f));
	glBindTexture(GL_TEXTURE_2D, Root::getSingleton().textureManager.getTexture("skybox"));
	glBindVertexArray(skyBox.vao);
	glBindBuffer(GL_ARRAY_BUFFER, skyBox.vertexBuffer);
#ifdef TROL_USE_OLD_OPENGL // Old opengl doesn't include GL_ELEMENT_ARRAY_BUFFER in a VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyBox.indexBuffer);
#endif
	glDrawElements(GL_TRIANGLES, skyBox.numFaces*3, GL_UNSIGNED_INT, 0);

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_CULL_FACE);

}