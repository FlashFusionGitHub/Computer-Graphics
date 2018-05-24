#pragma once

#include "Application.h"
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "Camera.h"

#include <glm/mat4x4.hpp>

class LightingApp : public aie::Application {
public:

	LightingApp();
	virtual ~LightingApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	//flying camera
	Camera camera;

	//aie::OBJMesh m_dragonMesh;
	//glm::mat4 m_dragonTransform;

	aie::OBJMesh m_soulSpearMesh;
	glm::mat4 m_soulSpearTransform;

	aie::ShaderProgram m_phongShader;

	struct Light {
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	Light m_light;
	glm::vec3 m_ambientLight;
};