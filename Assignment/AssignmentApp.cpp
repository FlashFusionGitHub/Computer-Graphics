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

	m_light1.lightAttributes[1] = glm::vec3(lightOneDiffuse[0], lightOneDiffuse[1], lightOneDiffuse[2]);
	m_light1.lightAttributes[2] = glm::vec3(lightOneSpecular[0], lightOneSpecular[1], lightOneSpecular[2]);

	m_light2.lightAttributes[1] = glm::vec3(lightTwoDiffuse[0], lightTwoDiffuse[1], lightTwoDiffuse[2]);
	m_light2.lightAttributes[2] = glm::vec3(lightTwoSpecular[0], lightTwoSpecular[1], lightTwoSpecular[2]);

	m_ambientLight = glm::vec3(ambientLight[0], ambientLight[1], ambientLight[2]);

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
	m_chest.Load(m_chestMesh, "./heart/Heart.obj", "Chest", glm::vec3(50, 50, 50), glm::vec3(-0.2f, 0, 0));
	m_skull.Load(m_skullMesh, "./skull/skull.obj", "Skull", glm::vec3(1, 1, 1), glm::vec3(0, 3.2f, 10));

	return true;
}

void AssignmentApp::shutdown() {

	Gizmos::destroy();
}

void AssignmentApp::update(float deltaTime) {

	//query time
	float time = getTime();

	// rotate light
	m_light1.lightAttributes[0] = glm::vec3(lightOneDirection[0], lightOneDirection[1], lightOneDirection[3]);
	// rotate light
	m_light2.lightAttributes[0] = glm::vec3(lightTwoDirection[0], lightTwoDirection[1], lightTwoDirection[3]);

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

	ImGui::Begin("Lights");

	if (ImGui::InputFloat3("Light 1 Direction", lightOneDirection)) {
		m_light1.lightAttributes[0][0] = lightOneDirection[0];
		m_light1.lightAttributes[0][1] = lightOneDirection[1];
		m_light1.lightAttributes[0][2] = lightOneDirection[2];
	}

	if (ImGui::ColorEdit3("Light 1 Diffuse", lightOneDiffuse)) {
		m_light1.lightAttributes[1][0] = lightOneDiffuse[0];
		m_light1.lightAttributes[1][1] = lightOneDiffuse[1];
		m_light1.lightAttributes[1][2] = lightOneDiffuse[2];
	}

	if (ImGui::InputFloat3("Light 1 Specular", lightOneSpecular)) {
		m_light1.lightAttributes[2][0] = lightOneSpecular[0];
		m_light1.lightAttributes[2][1] = lightOneSpecular[1];
		m_light1.lightAttributes[2][2] = lightOneSpecular[2];
	}

	if (ImGui::InputFloat3("Light 2 Direction", lightTwoDirection)) {
		m_light2.lightAttributes[0][0] = lightOneDirection[0];
		m_light2.lightAttributes[0][1] = lightOneDirection[1];
		m_light2.lightAttributes[0][2] = lightOneDirection[2];
	}

	if (ImGui::ColorEdit3("Light 2 Diffuse", lightTwoDiffuse)) {
		m_light2.lightAttributes[1][0] = lightTwoDiffuse[0];
		m_light2.lightAttributes[1][1] = lightTwoDiffuse[1];
		m_light2.lightAttributes[1][2] = lightTwoDiffuse[2];
	}

	if (ImGui::InputFloat3("Light 2 Specular", lightTwoSpecular)) {
		m_light2.lightAttributes[2][0] = lightTwoSpecular[0];
		m_light2.lightAttributes[2][1] = lightTwoSpecular[1];
		m_light2.lightAttributes[2][2] = lightTwoSpecular[2];
	}

	if (ImGui::ColorEdit3("Ambient Light", ambientLight)) {
		m_ambientLight.x = ambientLight[0];
		m_ambientLight.y = ambientLight[1];
		m_ambientLight.z = ambientLight[2];
	}

	ImGui::End();

	// draw Objects
	m_soulSpear.Draw(m_normalMap, m_projectionMatrix, m_viewMatrix, m_ambientLight, m_lights);
	m_axe.Draw(m_normalMap, m_projectionMatrix, m_viewMatrix, m_ambientLight, m_lights);
	m_barrel.Draw(m_normalMap, m_projectionMatrix, m_viewMatrix, m_ambientLight, m_lights);
	m_chest.Draw(m_normalMap, m_projectionMatrix, m_viewMatrix, m_ambientLight, m_lights);
	m_skull.Draw(m_normalMap, m_projectionMatrix, m_viewMatrix, m_ambientLight, m_lights);

	// draw 3D gizmos
	Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	// draw 2D gizmos using an orthogonal projection matrix
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}
