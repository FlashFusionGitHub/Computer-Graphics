#include "Input.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera
{
public:
	Camera() : m_theta(0), m_phi(-20), m_position(-10, 40, 0) {}

	void update();

	mat4 getProjectionMatrix(float width, float height);
	mat4 getViewMatrix();

private:
	float m_theta, m_phi;
	vec3 m_position;

	int m_lastMouseX, m_lastMouseY;
};

