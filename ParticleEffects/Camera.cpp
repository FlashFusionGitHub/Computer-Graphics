#include "Camera.h"

#include <gl_core_4_4.h>

const float DEG2RAD = 3.14159f / 180.0f;

void Camera::update()
{
	aie::Input* input = aie::Input::getInstance();

	float thetaR = m_theta * DEG2RAD;
	float phiR = m_phi * DEG2RAD;

	//calculate the forwards and right axes and up axis for the camera
	m_forward = vec3(cos(phiR)*cos(thetaR), sin(phiR), cos(phiR)*sin(thetaR));
	m_right = vec3(-sin(thetaR), 0, cos(thetaR));
	m_up = vec3(0, 1, 0);
	float deltaTime = 0.1f;

	// use WASD, ZX keys to move camera around
	if (input->isKeyDown(aie::INPUT_KEY_X))
		m_position += m_up * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_Z))
		m_position += -m_up * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_A))
		m_position += -m_right * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_position += m_right * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_W))
		m_position += m_forward * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_S))
		m_position += -m_forward * deltaTime;

	// get the current mouse coordinates
	float mx = input->getMouseX();
	float my = input->getMouseY();

	// if the right button is down, increment theta and phi
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		m_theta += 0.05f * (mx - m_lastMouseX);
		m_phi += 0.05f * (my - m_lastMouseY);
	}

	// store this frames values for next frame
	m_lastMouseX = mx;
	m_lastMouseY = my;
}

mat4 Camera::getProjectionMatrix(float width, float height)
{
	return glm::perspective(glm::pi<float>() * 0.25f, width / height, 0.1f, 1000.0f);
}

mat4 Camera::getViewMatrix()
{
	float thetaR = m_theta * DEG2RAD;
	float phiR = m_phi * DEG2RAD;

	vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));

	return glm::lookAt(m_position, m_position + forward, vec3(0, 1, 0));
}

mat4 Camera::getTransform()
{
	float thetaR = m_theta * DEG2RAD;

	mat4 position = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		m_position[0], m_position[1], m_position[2], 1
	};

	mat4 rotationX = {
		1, 0, 0, 0,
		0, cos(thetaR), -sin(thetaR), 0,
		0, sin(thetaR), cos(thetaR), 0,
		0, 0, 0, 1
	};

	mat4 rotationY = {
		cos(thetaR), 0, sin(thetaR), 0,
		0, 1, 0, 0,
		-sin(thetaR), 0, cos(thetaR), 0,
		0, 0, 0, 1
	};

	mat4 transform = position * rotationX * rotationY;

	return transform;
}

vec3 Camera::getPosition()
{
	return m_position;
}
