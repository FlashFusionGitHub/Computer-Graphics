#pragma once

#include "tiny_obj_loader.h"
#include "OBJMesh.h"
#include "Shader.h"
#include "RenderTarget.h"

#include <glm/ext.hpp>
#include <vector>

class Model
{
public:

	bool Load(aie::OBJMesh& object, const char* objectFileName, const char* name, glm::vec3& scale, glm::vec3& position);
	void Draw(aie::ShaderProgram& shader, glm::mat4& projectionView, glm::mat4& viewMatrix, glm::vec3& ambientLight, glm::mat3* lights);

protected:

	aie::OBJMesh m_object;

	glm::mat4 m_objectTransform{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1, };

	const char* m_name;

private:

	float m_rotation[3] = { 0, 0, 0 };
	float m_position[3] = { 0, 0, 0 };
	float m_scale[3] = { 0, 0, 0 };

	glm::mat3 m_lights[2];

	glm::mat4 m_rotationXMatrix;
	glm::mat4 m_rotationYMatrix;
	glm::mat4 m_rotationZMatrix;
	glm::mat4 m_scaleMatrix;
	glm::mat4 m_positionMatrix;

	float m_reflection = 20.0f;
	float m_roughness = 0.0f;
};