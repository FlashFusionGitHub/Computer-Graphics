#pragma once

#include "Application.h"
#include "ParticleEmitter.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include <glm/mat4x4.hpp>

class ParticleEffectsApp : public aie::Application {
public:

	ParticleEffectsApp();
	virtual ~ParticleEffectsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	Camera m_camera;

	aie::ShaderProgram m_particleShader;
	glm::mat4 m_particleTransform;
	ParticleEmitter* m_emitter;
};