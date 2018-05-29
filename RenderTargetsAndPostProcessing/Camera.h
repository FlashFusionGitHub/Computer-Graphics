#include "Input.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera
{
public:
	Camera() : m_theta(0), m_phi(-20), m_position(-30, 15, 0) {}

	void update();

	mat4 getProjectionMatrix(float width, float height);
	mat4 getViewMatrix();

	vec3 getPosition();

private:
	float m_theta, m_phi;
	vec3 m_position;

	int m_lastMouseX, m_lastMouseY;
};
