#pragma once

#include "Application.h"
#include "Camera.h"

#include <glm/mat4x4.hpp>

class CamerasAndProjectionsApp : public aie::Application {
public:

	CamerasAndProjectionsApp();
	virtual ~CamerasAndProjectionsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	Camera camera;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
};