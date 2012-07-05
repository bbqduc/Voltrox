#include "meshrender.h"
#include "../TROLLogic/Data/entity.h"
#include "../root.h"
#include "glutils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void MeshRenderer::render()
{
		const Shader& s = Root::getSingleton().shaderManager.getShader(ShaderManager::MVP_TEXTURED);
		const Camera& c = Root::getSingleton().engine->getCamera();
		const glm::mat4& perspective = Root::getSingleton().renderManager.getPerspective();

		// GL init stuff
		glUseProgram(s.id);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(s.uniformLocs[1], 0);

		// Camera setup
		glm::mat4 cam(glm::lookAt(c.pos, c.pos + c.view, c.up));
		glm::mat4 m;
		btTransform trans;

		// Draw entities
		// One additional optimization would be to draw same models sequentially to skip some binds
		for(int i = 0; i < entities.size(); ++i)
		{
			const Entity& e = *entities[i];

			e.motionState.getWorldTransform(trans);
			trans.getOpenGLMatrix(&m[0][0]);
			glm::mat4 MVP = perspective * cam * m;
			glUniformMatrix4fv(s.uniformLocs[0], 1, GL_FALSE, glm::value_ptr(MVP));

			glBindTexture(GL_TEXTURE_2D, e.model.texture);
			glBindVertexArray(e.model.vao);
			glBindBuffer(GL_ARRAY_BUFFER, e.model.vertexBuffer);
#ifdef TROL_USE_OLD_OPENGL // Old opengl doesn't include GL_ELEMENT_ARRAY_BUFFER in a VAO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e.model.indexBuffer);
#endif
			glDrawElements(GL_TRIANGLES, e.model.numFaces*3, GL_UNSIGNED_INT, 0);
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);

		checkGLErrors("MeshRenderer::render()");
}