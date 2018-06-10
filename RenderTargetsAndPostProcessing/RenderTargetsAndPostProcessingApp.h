#pragma once

#include "Application.h"
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "Camera.h"
#include "RenderTarget.h"

#include <Texture.h>
#include <glm/mat4x4.hpp>

class Light {
public:
	glm::vec3 direction;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class MultiLights {
public:
	union {
		glm::mat3 light;
		glm::vec3 lightAttributes[3];

		//[0] direction
		//[1] diffuse
		//[2] specular
	};
};

class RenderTargetsAndPostProcessingApp : public aie::Application {
public:

	RenderTargetsAndPostProcessingApp();
	virtual ~RenderTargetsAndPostProcessingApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	Camera m_camera;

	glm::vec3 m_ambientLight;

	glm::mat3 m_lights[2];

	MultiLights m_light1;
	MultiLights m_light2;


	aie::ShaderProgram m_phongShader;

	aie::ShaderProgram m_postShader;

	aie::OBJMesh m_soulSpear;
	glm::mat4 m_soulSpearTransform;
	aie::Texture m_soulSpearTexture;

	aie::RenderTarget m_renderTarget;

	bool m_drawn = false;
	bool m_sobel = false;
	bool m_blur = false;
	bool m_sharpen = false;
	bool m_distort = false;

	float m_rotation[3] = {0, 0, 0};
	float m_position[3] = { 0, 0, 0 };
	float m_scale[3] = {1, 1, 1};

	float m_reflection = 0;
	float m_roughness = 0;

	mat4 m_rotationXMatrix;
	mat4 m_rotationYMatrix;
	mat4 m_rotationZMatrix;
	mat4 m_scaleMatrix;
	mat4 m_positionMatrix;

	//mat4 newMatrix;

	int filter = 0;

	int oldFilter;

	Mesh m_fullscreenQuad;
};