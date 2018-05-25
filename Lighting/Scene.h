#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

#include "Camera.h"
#include "Shader.h"
#include "gl_core_4_4.h"

class Instance;

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Shader;

class Scene
{
public:
	Scene();
	~Scene();

	void draw();
	void useShader(Shader* shader);

private:
	std::vector<Instance*> m_instances;

	Camera* m_camera;

	vec3 m_lightDirection;

	vec3 m_pointLights[4];
	vec3 m_pointLightColours[4];
	float m_pointLightPowers[4];
};

