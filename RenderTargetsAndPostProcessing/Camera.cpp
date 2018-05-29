#include "Camera.h"

const float DEG2RAD = 3.14159f / 180.0f;

void Camera::update()
{
	aie::Input* input = aie::Input::getInstance();

	float thetaR = m_theta * DEG2RAD;
	float phiR = m_phi * DEG2RAD;

	//calculate the forwards and right axes and up axis for the camera
	glm::vec3 forward(cos(phiR)*cos(thetaR), sin(phiR), cos(phiR)*sin(thetaR));
	glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
	glm::vec3 up(0, 1, 0);
	float deltaTime = 0.1f;

	// use WASD, ZX keys to move camera around
	if (input->isKeyDown(aie::INPUT_KEY_X))
		m_position += up * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_Z))
		m_position += -up * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_A))
		m_position += -right * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_position += right * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_W))
		m_position += forward * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_S))
		m_position += -forward * deltaTime;

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

vec3 Camera::getPosition()
{
	return m_position;
}
