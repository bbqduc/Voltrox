#include "rendersystem.h"
#include <TROLCommon/root.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void RenderSystem::render()
{
        camera = 10;
		btTransform& c = *static_cast<btTransform*>(Root::storageSystem.getComponent(camera, CT_POSITION));
		const Shader& s = Root::shaderManager.getShader(ShaderManager::MVP_TEXTURED);
        const glm::mat4& perspective = Root::openGLWindow.getPerspective();

		// GL init stuff
		glUseProgram(s.id);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(s.uniformLocs[1], 0);

		// Camera setup
//		glm::mat4 cam(glm::lookAt(c.pos, c.pos + c.view, c.up)); // TODO : ditch glm::lookat
//		glm::mat4 cam(glm::lookAt(glm::vec3(0.0f,0.0f,200.0f), glm::vec3(0.0f,0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f))); // TODO : ditch glm::lookat
		glm::mat4 m;
		btTransform trans;

        btQuaternion q(btVector3(0.0f,1.0f,0.0f), 3.14f);
        btTransform t2(q);
        btVector3 vi(0.0f,3.0f, -8.0f);
        btTransform t(btQuaternion::getIdentity(),vi);
        t = c * t * t2;

        glm::mat4 cam;
        t.inverse().getOpenGLMatrix(&cam[0][0]);
		cam = perspective * cam;

		const SortedArray<ComponentStore::Index_t>& renderables = Root::storageSystem.getComponents(CT_RENDERABLE);
		
		// Draw entities
		// One additional optimization would be to draw same->models sequentially to skip some binds
		for(int i = 0; i < renderables.size(); ++i)
		{
			const btTransform& p = *static_cast<btTransform*>(Root::storageSystem.getComponent(renderables[i].entity, CT_POSITION));
			const Model* r = *static_cast<Model**>(renderables[i].component);

			p.getOpenGLMatrix(&m[0][0]);
			
			glm::mat4 MVP = cam * m;
			glUniformMatrix4fv(s.uniformLocs[0], 1, GL_FALSE, glm::value_ptr(MVP));

			glBindTexture(GL_TEXTURE_2D, r->texture);
			glBindVertexArray(r->vao);
			glBindBuffer(GL_ARRAY_BUFFER, r->vertexBuffer);
#ifdef TROL_USE_OLD_OPENGL // Old opengl doesn't include GL_ELEMENT_ARRAY_BUFFER in a VAO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->indexBuffer);
#endif
			glDrawElements(GL_TRIANGLES, r->numFaces*3, GL_UNSIGNED_INT, 0);
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);

		checkGLErrors("MeshRenderer::render()");
}

/*void RenderSystem::explodeRender()
{
	const Shader& s = Root::shaderManager.getShader(ShaderManager::MESH_EXPLODER);
	btTransform* c = Root::positionSystem.getComponent(camera);
    const glm::mat4& perspective = Root::openGLWindow.getPerspective();

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
		glUniform1f(s.uniformLocs[4], 1.0f - e.timeElapsed / e.TTL);

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
}*/
