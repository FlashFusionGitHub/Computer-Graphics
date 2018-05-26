#pragma once

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Shader;

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Model
{
public:
	Model();
	~Model();

	void draw(mat4 transform, mat4 cameraMatrix, aie::Shader* shader);

	bool isAnimated() {
		return m_animatedState;
	}

private:
	bool m_animatedState;
};

