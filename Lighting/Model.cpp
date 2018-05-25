#include "Model.h"
#include "Shader.h"

#include <gl_core_4_4.h>
#include <fbxskeleton.h>

Model::Model()
{
}


Model::~Model()
{
}

void Model::draw(mat4 transform, mat4 cameraMatrix, aie::Shader* shader)
{
	glm::mat4 mvp = cameraMatrix * transform;

	shader->setMatrix("MVP", mvp);
	shader->setMatrix("M", transform);

	if (isAnimated())
	{
		// grab the skeleton and animation we want to use
		FBXSkeleton* skeleton = fbxFile->getSkeletonByIndex(0);
		skeleton->updateBones();
		int bones_location = glGetUniformLocation(shader->getID(), "bones");
		glUniformMatrix4fv(bones_location, skeleton->m_boneCount, GL_FALSE,
			(float*)skeleton->m_bones);
	}

	for (unsigned int i = 0; i < m_gl_info.size(); ++i) {
		glBindVertexArray(m_gl_info[i].m_VAO);
		glDrawElements(GL_TRIANGLES, m_gl_info[i].m_index_count,
			GL_UNSIGNED_INT, 0);
	}
}
