#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Shader.h"
#include "Scene.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Shader;

class Instance
{
public:
	Instance();
	~Instance();

	void draw(Scene* scene);

private:
	vec3 m_position;
	vec3 m_euler;
	vec3 m_scale;

	mat4 m_transform;

	Shader* m_shader;
};

