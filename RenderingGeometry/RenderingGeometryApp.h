#pragma once

#include "Application.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

#include <glm/mat4x4.hpp>
#include <Texture.h>

class RenderingGeometryApp : public aie::Application {
public:

	RenderingGeometryApp();
	virtual ~RenderingGeometryApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	Camera camera;

	aie::Texture m_gridTexture;
	aie::ShaderProgram m_shader;
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;
};