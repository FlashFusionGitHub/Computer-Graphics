#pragma once

#include "Application.h"
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "Camera.h"

#include <Texture.h>
#include <glm/mat4x4.hpp>

class MaterialsAndTexturesApp : public aie::Application {
public:

	MaterialsAndTexturesApp();
	virtual ~MaterialsAndTexturesApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	Camera camera;

	//aie::Texture m_gridTexture;

	aie::ShaderProgram m_shader;

	//Mesh m_quadMesh;
	//glm::mat4 m_quadTransform;

	aie::OBJMesh m_soulSpearMesh;
	glm::mat4 m_soulSpearTransform;
};