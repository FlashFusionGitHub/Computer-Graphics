#pragma once

#include "Application.h"
#include "Camera.h"
#include <glm/mat4x4.hpp>

class AssignmentApp : public aie::Application {
public:

	AssignmentApp();
	virtual ~AssignmentApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	//Camera in scene
	Camera m_camera;
};