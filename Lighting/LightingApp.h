#pragma once

#include "Application.h"
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "Camera.h"

#include <glm/mat4x4.hpp>

class Light {
public:
	glm::vec3 direction;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class LightingApp : public aie::Application {
public:

	LightingApp();
	virtual ~LightingApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void draw3DObject(aie::ShaderProgram& phongShader, Light& light, vec3& ambientLight,
		mat4& projectionMatrix, mat4& viewMatrix, mat4& objectTransform, aie::OBJMesh& objectMesh);

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
	glm::mat4 m_soulSpearTransform2;
	glm::mat4 m_soulSpearTransform3;
	glm::mat4 m_soulSpearTransform4;

	aie::ShaderProgram m_phongShader;

	float m_reflection;
	float m_roughness;

	Light m_light;
	glm::vec3 m_ambientLight;
};