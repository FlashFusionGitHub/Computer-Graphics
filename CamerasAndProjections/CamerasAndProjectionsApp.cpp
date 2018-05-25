#include "CamerasAndProjectionsApp.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

CamerasAndProjectionsApp::CamerasAndProjectionsApp() {

}

CamerasAndProjectionsApp::~CamerasAndProjectionsApp() {

}

bool CamerasAndProjectionsApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	m_positions[0] = glm::vec3(10, 5, 10);
	m_positions[1] = glm::vec3(-10, 0, -10);
	m_rotations[0] = glm::quat(glm::vec3(0, -1, 0));
	m_rotations[1] = glm::quat(glm::vec3(0, 1, 0));

	return true;
}

void CamerasAndProjectionsApp::shutdown() {

	Gizmos::destroy();
}

void CamerasAndProjectionsApp::update(float deltaTime) {

	// use time to animate a alue between [0, 1]
	float s = glm::cos(getTime()) * 0.5f + 0.5f;

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	m_hipFrames[0].position = glm::vec3(0, 5, 0);
	m_hipFrames[0].rotation = glm::quat(glm::vec3(1, 0, 0));
	m_hipFrames[1].position = glm::vec3(0, 5, 0);
	m_hipFrames[1].rotation = glm::quat(glm::vec3(-1, 0, 0));

	m_kneeFrames[0].position = glm::vec3(0, -2.5f, 0);
	m_kneeFrames[0].rotation = glm::quat(glm::vec3(1, 0, 0));
	m_kneeFrames[1].position = glm::vec3(0, -2.5f, 0);
	m_kneeFrames[1].rotation = glm::quat(glm::vec3(0, 0, 0));

	m_ankleFrames[0].position = glm::vec3(0, -2.5f, 0);
	m_ankleFrames[0].rotation = glm::quat(glm::vec3(-1, 0, 0));
	m_ankleFrames[1].position = glm::vec3(0, -2.5f, 0);
	m_ankleFrames[1].rotation = glm::quat(glm::vec3(0, 0, 0));

	// linearly interpolate hip position
	glm::vec3 p = (1.0f - s) * m_hipFrames[0].position +
		s * m_hipFrames[1].position;

	// spherically interpolate hip rotation
	glm::quat r = glm::slerp(m_hipFrames[0].rotation,
		m_hipFrames[1].rotation, s);

	// update the hip bone
	m_hipBone = glm::translate(p) * glm::toMat4(r);	// linearly interpolate knee position
	glm::vec3 p2 = (1.0f - s) * m_kneeFrames[0].position +
		s * m_kneeFrames[1].position;

	// spherically interpolate knee rotation
	glm::quat r2 = glm::slerp(m_kneeFrames[0].rotation,
		m_kneeFrames[1].rotation, s);

	// update the knee bone
	m_kneeBone = m_hipBone * glm::translate(p2) * glm::toMat4(r2);	// linearly interpolate knee position
	glm::vec3 p3 = (1.0f - s) * m_ankleFrames[0].position +
		s * m_ankleFrames[1].position;

	// spherically interpolate knee rotation
	glm::quat r3 = glm::slerp(m_ankleFrames[0].rotation,
		m_ankleFrames[1].rotation, s);

	// update the knee bone
	m_ankleBone = m_kneeBone * glm::translate(p3) * glm::toMat4(r3);
	glm::vec3 hipPos = glm::vec3(m_hipBone[3].x,
		m_hipBone[3].y,
		m_hipBone[3].z);

	glm::vec3 kneePos = glm::vec3(m_kneeBone[3].x,
		m_kneeBone[3].y,
		m_kneeBone[3].z);

	glm::vec3 anklePos = glm::vec3(m_ankleBone[3].x,
		m_ankleBone[3].y,
		m_ankleBone[3].z);

	glm::vec4 half(0.5f);
	glm::vec4 pink(1, 0, 1, 1);

	Gizmos::addAABBFilled(hipPos, half, pink, &m_hipBone);
	Gizmos::addAABBFilled(kneePos, half, pink, &m_kneeBone);
	Gizmos::addAABBFilled(anklePos, half, pink, &m_ankleBone);

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	camera.update();

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void CamerasAndProjectionsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = camera.getProjectionMatrix(getWindowWidth(), getWindowHeight());
	m_viewMatrix = camera.getViewMatrix();

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}