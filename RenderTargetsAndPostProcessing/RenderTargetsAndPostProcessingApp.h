#pragma once

#include "Application.h"
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "Camera.h"
#include "RenderTarget.h"

#include <glm/mat4x4.hpp>

class Light {
public:
	glm::vec3 direction;
	glm::vec3 diffuse;
	glm::vec3 specular;
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
	Light m_light;

	aie::ShaderProgram m_phongShader;
	aie::ShaderProgram m_postShader;

	aie::OBJMesh m_dragonMesh;
	glm::mat4 m_dragonTransform;

	aie::RenderTarget m_renderTarget;

	bool m_drawn = false;
	bool m_sobel = false;
	bool m_blur = false;
	bool m_sharpen = false;
	bool m_distort = false;

	int filter;

	int oldFilter;

	Mesh m_fullscreenQuad;
};