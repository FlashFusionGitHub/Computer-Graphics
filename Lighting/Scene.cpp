#include "Scene.h"
#include "Instance.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::draw()
{
	for (int i = 0; i < m_instances.size(); i++) {
		m_instances[i]->draw(this);
	}
}

void Scene::useShader(Shader * shader)
{
	unsigned int id = shader->getID();
	int loc;

	glUseProgram(id);

	loc = glGetUniformLocation(id, "cameraPosition");

	glUniform3f(loc, m_camera->getPosition().x, m_camera->getPosition().y, m_camera->getPosition().z);

	loc = glGetUniformLocation(id, "lightDir");

	glUniform3f(loc, m_lightDirection.x, m_lightDirection.y, m_lightDirection.z);
}
