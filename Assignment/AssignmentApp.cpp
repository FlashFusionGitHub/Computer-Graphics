#include "AssignmentApp.h"
#include "Gizmos.h"
#include "Input.h"

#include <../dependencies/imgui/imgui.h>
#include <gl_core_4_4.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

AssignmentApp::AssignmentApp() {

}

AssignmentApp::~AssignmentApp() {

}

bool AssignmentApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	m_light1.lightAttributes[1] = { 1, 1, 1 };
	m_light1.lightAttributes[2] = { 1, 1, 1 };

	m_light2.lightAttributes[1] = { 1, 1, 1 };
	m_light2.lightAttributes[2] = { 1, 1, 1 };

	m_ambientLight = { 0.25f, 0.25f, 0.25f };

	// load a phong shader
	m_normalMap.loadShader(aie::eShaderStage::VERTEX, "./shaders/normalmap.vert");
	m_normalMap.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/normalmap.frag");

	if (m_normalMap.link() == false) {
		printf("Shader Error: %s\n", m_normalMap.getLastError());
		return false;
	}

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	m_soulSpear.Load(m_soulSpearMesh, "./soulspear/soulspear.obj", "SoulSpear", glm::vec3(2, 2, 2), glm::vec3(0, 0, 0));
	m_axe.Load(m_axeMesh, "./axe/Hatchet.obj", "Hatchet", glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(100, 0, 0));
	m_barrel.Load(m_barrelMesh, "./barrel/tut_storage_lp.obj", "Barrel", glm::vec3(1, 1, 1), glm::vec3(0, -0.3f, -10));
	m_skull.Load(m_skullMesh, "./skull/skull.obj", "Skull", glm::vec3(1, 1, 1), glm::vec3(0, 3.2f, 10));
	m_chest.Load(m_chestMesh, "./chest/treasure_chest.obj", "Chest", glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(-110.0f, 30, 0));

	return true;
}

void AssignmentApp::shutdown() {

	Gizmos::destroy();
}

void AssignmentApp::update(float deltaTime) {

	//query time
	float time = getTime();

	// rotate light
	m_light1.lightAttributes[0] = glm::normalize(glm::vec3(glm::cos(time), 0, glm::sin(time)));
	// rotate light
	m_light2.lightAttributes[0] = glm::normalize(glm::vec3(glm::sin(time), glm::cos(time), 0));

	m_lights[0] = m_light1.light;
	m_lights[1] = m_light2.light;

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	m_camera.update(deltaTime);

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

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void AssignmentApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on camera projection matrix
	m_projectionMatrix = m_camera.getProjectionMatrix(getWindowWidth(), getWindowHeight());
	// update view matrix based on camera view matrix
	m_viewMatrix = m_camera.getViewMatrix();

	// draw Objects
	m_soulSpear.Draw(m_normalMap, m_projectionMatrix, m_viewMatrix, m_ambientLight, m_lights);
	m_axe.Draw(m_normalMap, m_projectionMatrix, m_viewMatrix, m_ambientLight, m_lights);
	m_barrel.Draw(m_normalMap, m_projectionMatrix, m_viewMatrix, m_ambientLight, m_lights);
	m_skull.Draw(m_normalMap, m_projectionMatrix, m_viewMatrix, m_ambientLight, m_lights);
	m_chest.Draw(m_normalMap, m_projectionMatrix, m_viewMatrix, m_ambientLight, m_lights);

	// draw 3D gizmos
	Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	// draw 2D gizmos using an orthogonal projection matrix
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}
