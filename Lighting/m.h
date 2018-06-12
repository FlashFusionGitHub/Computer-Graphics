#pragma once

#include "Application.h"

#include "Shader.h"
#include "OBJMesh.h"

#include <glm/mat4x4.hpp>

class Mesh;

class m
{
public:
	m();
	~m();

	void load(aie::ShaderProgram& phongShader, glm::vec3& ambientLight, glm::mat4& projectionMatrix, glm::mat4& viewMatrix,
		glm::mat4& objectTransform, aie::OBJMesh& objectMesh);
};

