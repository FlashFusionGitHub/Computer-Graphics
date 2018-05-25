#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "Application.h"
#include "Camera.h"
#include "Gizmos.h"
#include "Input.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

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

	glm::vec3 m_positions[2];
	glm::quat m_rotations[2];

	struct KeyFrame {
		glm::vec3 position;
		glm::quat rotation;
	};

	KeyFrame m_hipFrames[2];
	KeyFrame m_kneeFrames[2];
	KeyFrame m_ankleFrames[2];
	glm::mat4 m_hipBone;
	glm::mat4 m_kneeBone;
	glm::mat4 m_ankleBone;
};