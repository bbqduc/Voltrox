#include "meshexplode.h"
#include "../root.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void MeshExplodeRenderer::render()
{
	const Shader& s = Root::getSingleton().shaderManager.getShader(ShaderManager::MESH_EXPLODER);
	const Camera& c = Root::getSingleton().engine->getCamera();
	const glm::mat4& perspective = Root::getSingleton().renderManager.getPerspective();

	glDisable(GL_CULL_FACE);
	glUseProgram(s.id);
	glActiveTexture(GL_TEXTURE0);

	// Texture sampler
	glUniform1i(s.uniformLocs[1], 0);

	glm::mat4 cam(glm::lookAt(c.pos, c.pos + c.view, c.up));
	glm::mat4 m;

	btTransform trans;
	for(int i = 0; i < explosions.size(); ++i)
	{
		const ExplosionInfo& e = *explosions[i];

		// Explosion position
		glUniform3fv(s.uniformLocs[2], 1, &e.localPosition[0]);
		// Time elapsed
		glUniform1f(s.uniformLocs[3], e.timeElapsed);

		e.entity.motionState.getWorldTransform(trans);
		trans.getOpenGLMatrix(&m[0][0]);

		glm::mat4 MVP = perspective * cam * m;
		glUniformMatrix4fv(s.uniformLocs[0], 1, GL_FALSE, glm::value_ptr(MVP));

		glBindTexture(GL_TEXTURE_2D, e.entity.model.texture);
		glBindVertexArray(e.entity.model.vao);
		glBindBuffer(GL_ARRAY_BUFFER, e.entity.model.vertexBuffer);
#ifdef TROL_USE_OLD_OPENGL // Older Opengl versions do not store GL_ELEMENT_ARRAY_BUFFER state in VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e.model.indexBuffer);
#endif
		glDrawElements(GL_TRIANGLES, e.entity.model.numFaces*3, GL_UNSIGNED_INT, 0);
	}
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_CULL_FACE);
}