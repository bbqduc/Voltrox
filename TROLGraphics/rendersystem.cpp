#include "rendersystem.h"

void RenderSystem::render()
{
		Position* c = getComponent(camera, CT_POSITION);
		const Shader& s = shaderManager.getShader(ShaderManager::MVP_TEXTURED);

		// GL init stuff
		glUseProgram(s.id);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(s.uniformLocs[1], 0);

		// Camera setup
		glm::mat4 cam(glm::lookAt(c.pos, c.pos + c.view, c.up)); // TODO : ditch glm::lookat
		glm::mat4 m;
		btTransform trans;

		cam = perspective * cam;

		const SortedArray<Index_t>& renderables = getComponents();
		
		// Draw entities
		// One additional optimization would be to draw same->models sequentially to skip some binds
		for(int i = 0; i < renderables.size(); ++i)
		{
			const Position* p = GLOBALTHING::getComponent(renderables[i].entity, CT_POSITION);
			const Renderable* r = renderables[i].component;

			p->transform->getOpenGLMatrix(&m[0][0]);
			
			glm::mat4 MVP = cam * m;
			glUniformMatrix4fv(s.uniformLocs[0], 1, GL_FALSE, glm::value_ptr(MVP));

			glBindTexture(GL_TEXTURE_2D, r->model->texture);
			glBindVertexArray(r->model->vao);
			glBindBuffer(GL_ARRAY_BUFFER, r->model->vertexBuffer);
#ifdef TROL_USE_OLD_OPENGL // Old opengl doesn't include GL_ELEMENT_ARRAY_BUFFER in a VAO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->model->indexBuffer);
#endif
			glDrawElements(GL_TRIANGLES, r->model->numFaces*3, GL_UNSIGNED_INT, 0);
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);

		checkGLErrors("MeshRenderer::render()");
}