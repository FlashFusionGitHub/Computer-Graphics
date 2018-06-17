#include "Model.h"

#include <../dependencies/imgui/imgui.h>
#include <gl_core_4_4.h>
#include <iostream>


bool Model::Load(aie::OBJMesh& object, const char* objectFileName, const char* name, glm::vec3& scale, glm::vec3& position)
{

	m_object = object;

	// load an OBJ and assign a scaled transform
	if (m_object.load(objectFileName, true, true) == false) {
		printf("Object Error!\n");
		return false;
	}

	for (int i = 0; i < 3; i++) {
		m_scale[i] = scale[i];
		m_position[i] = position[i];
	}

	m_name = name;

	m_scaleMatrix = m_objectTransform;
	m_positionMatrix = m_objectTransform;
	m_rotationXMatrix = m_objectTransform;
	m_rotationYMatrix = m_objectTransform;
	m_rotationZMatrix = m_objectTransform;

	m_scaleMatrix = {
		m_scale[0], 0, 0, 0,
		0, m_scale[1], 0, 0,
		0, 0, m_scale[2], 0,
		0, 0, 0, 1
	};

	m_positionMatrix = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		m_position[0], m_position[1], m_position[2], 1
	};

	m_objectTransform = m_scaleMatrix * m_positionMatrix
		* m_rotationXMatrix * m_rotationYMatrix * m_rotationZMatrix;

	return true;
}

void Model::Draw(aie::ShaderProgram& shader, glm::mat4& projectionView, glm::mat4& viewMatrix, glm::vec3& ambientLight, glm::mat3* lights)
{
	// draw scene with a light
	shader.bind();

	shader.bindUniform("Ia", ambientLight);

	shader.bindUniform("lights", 2, lights);

	shader.bindUniform("cameraPosition", glm::vec3(glm::inverse(viewMatrix)[3]));

	// bind transform
	auto pvm = projectionView * viewMatrix * m_objectTransform;
	shader.bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	shader.bindUniform("ModelMatrix", m_objectTransform);
	shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_objectTransform)));

	shader.bindUniform("roughness", m_roughness);
	shader.bindUniform("reflectionCoefficient", m_reflection);

	// draw mesh
	m_object.draw();

	ImGui::Begin(m_name);

	// Position Edit
	if (ImGui::InputFloat3("Position", m_position)) {
		m_positionMatrix = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			m_position[0], m_position[1], m_position[2], 1,
		};
	}

	//Rotation Edit
	if (ImGui::SliderAngle("Rotation X", &m_rotation[0])) {
		m_rotationXMatrix = {
			1, 0, 0, 0,
			0, cos(m_rotation[0]), -sin(m_rotation[0]), 0,
			0, sin(m_rotation[0]), cos(m_rotation[0]), 0,
			0, 0, 0, 1,
		};
	}

	if (ImGui::SliderAngle("Rotation Y", &m_rotation[1])) {
		m_rotationYMatrix = {
			cos(m_rotation[1]), 0, sin(m_rotation[1]), 0,
			0, 1, 0, 0,
			-sin(m_rotation[1]), 0, cos(m_rotation[1]), 0,
			0, 0, 0, 1,
		};
	}

	if (ImGui::SliderAngle("Rotation Z", &m_rotation[2])) {
		m_rotationZMatrix = {
			cos(m_rotation[2]), -sin(m_rotation[2]), 0, 0,
			sin(m_rotation[2]), cos(m_rotation[2]), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};
	}

	//Scale Edit
	if (ImGui::InputFloat3("Scale", m_scale)) {
		m_scaleMatrix = {
			m_scale[0], 0, 0, 0,
			0, m_scale[1], 0, 0,
			0, 0, m_scale[2], 0,
			0, 0, 0, 1,
		};
	}

	ImGui::SliderFloat("Reflection", &m_reflection, 0.0f, 100.0f);
	ImGui::SliderFloat("Roughness", &m_roughness, 0, 1.0f);

	if (ImGui::Button("Reset")) {

		m_reflection = 0;
		m_roughness = 0;

		for (int i = 0; i < 3; i++) {
			m_scale[i] = 1.0f;
			m_position[i] = 0.0f;
			m_rotation[i] = 0.0f;
		}

		m_objectTransform = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};

		m_scaleMatrix = m_objectTransform;
		m_positionMatrix = m_objectTransform;
		m_rotationXMatrix = m_objectTransform;
		m_rotationYMatrix = m_objectTransform;
		m_rotationZMatrix = m_objectTransform;
	}

	ImGui::End();

	m_objectTransform = m_scaleMatrix * m_positionMatrix
		* m_rotationXMatrix * m_rotationYMatrix * m_rotationZMatrix;
}
