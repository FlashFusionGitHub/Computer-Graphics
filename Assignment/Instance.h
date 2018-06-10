#pragma once

#include <glm\glm.hpp>
#include "Texture.h"
#include "Model.h"

#include <glm\ext.hpp>

class Scene;

class Instance
{
public:
	Instance(Model* model, unsigned int shaderID, aie::Texture* diffuse, aie::Texture* normal, aie::Texture* specular);
	~Instance();

	void SetShader(unsigned int shaderID);

	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 eulerAngles);
	void SetScale(glm::vec3 scale);

	glm::mat4 GetTransform();
	glm::vec3 GetPosition();

	void UpdateTransform();
	void Draw(Scene* scene, float time);

	Model* m_model;

private:
	glm::vec3 m_position;
	glm::vec3 m_eulerAngles;
	glm::vec3 m_scale;

	glm::mat4 m_transform;

	aie::Texture* m_diffuse;
	aie::Texture* m_normal;
	aie::Texture* m_specular;

	unsigned int m_shaderID;
};