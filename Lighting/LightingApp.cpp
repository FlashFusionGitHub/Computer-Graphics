#include "LightingApp.h"
#include "Gizmos.h"
#include "Input.h"

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <../dependencies/imgui/imgui.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

LightingApp::LightingApp() {

}

LightingApp::~LightingApp() {

}

bool LightingApp::startup() {

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	m_light.diffuse = { 1, 1, 1 };
	m_light.specular = { 1, 1, 1 };
	m_ambientLight = { 1.0f, 1.0f, 1.0f };

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/PBR.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/PBR.frag");

	if (m_phongShader.link() == false) {
		printf("Shader Error: %s\n", m_phongShader.getLastError());
		return false;
	}

	if (m_soulSpearMesh.load("./soulspear/soulspear.obj", true, true) == false) {
		printf("Soulspear mesh error!\n");
		return false;
	}

	if (m_skullSpearMesh.load("./skull/skull.obj", true, true) == false) {
		printf("Soulspear mesh error!\n");
		return false;
	}

	m_soulSpearTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		2, 0, 2, 1 };

	m_soulSpearTransform2 = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		2, 0, -2, 1 };

	m_soulSpearTransform3 = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-2, 0, 2, 1 };

	m_soulSpearTransform4 = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-2, 0, -2, 1 };

	return true;
}

void LightingApp::shutdown() {

	Gizmos::destroy();
}

void LightingApp::update(float deltaTime) {

	//query time
	float time = getTime();

	// rotate light
	m_light.direction = glm::normalize(glm::vec3(glm::cos(time), 0, glm::sin(time)));

	// wipe the gizmos clean for this frame
	Gizmos::clear();

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

void LightingApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = camera.getProjectionMatrix(getWindowWidth(), getWindowHeight());
	m_viewMatrix = camera.getViewMatrix();

	//bind shader
	m_phongShader.bind();

	//bind roughness
	m_phongShader.bindUniform("roughness", m_roughness);

	//bind reflection coefficient
	m_phongShader.bindUniform("reflectionCoefficient", m_reflection);

	//bind ambient light
	m_phongShader.bindUniform("Ia", m_ambientLight);

	//bind light
	m_phongShader.bindUniform("Id", m_light.diffuse);
	m_phongShader.bindUniform("Is", m_light.specular);
	m_phongShader.bindUniform("lightDirection", m_light.direction);

	m_soulSpear.load(m_phongShader, m_ambientLight, m_projectionMatrix, m_viewMatrix, m_soulSpearTransform, m_soulSpearMesh);
	m_skull.load(m_phongShader, m_ambientLight, m_projectionMatrix, m_viewMatrix, m_soulSpearTransform2, m_skullSpearMesh);

	//draw3DObject(m_phongShader, m_light, m_ambientLight, m_projectionMatrix, m_viewMatrix, m_soulSpearTransform, m_soulSpearMesh);
	//draw3DObject(m_phongShader, m_light, m_ambientLight, m_projectionMatrix, m_viewMatrix, m_soulSpearTransform2, m_skullSpearMesh);
	//draw3DObject(m_phongShader, m_light, m_ambientLight, m_projectionMatrix, m_viewMatrix, m_soulSpearTransform3, m_soulSpearMesh);
	//draw3DObject(m_phongShader, m_light, m_ambientLight, m_projectionMatrix, m_viewMatrix, m_soulSpearTransform4, m_soulSpearMesh);

	ImGui::Begin("Lighting");
	ImGui::SliderFloat("Reflection", &m_reflection, 0.0f, 100.0f);
	ImGui::SliderFloat("Roughness", &m_roughness, 0, 1.0f);
	ImGui::End();


	//draw 3D gizmos
	Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	//draw 2D gizmos using orthogonal projection matrix
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}

void LightingApp::draw3DObject(aie::ShaderProgram& phongShader, Light& light, vec3& ambientLight, mat4& projectionMatrix, mat4& viewMatrix, mat4& objectTransform, aie::OBJMesh& objectMesh)
{
	//bind shader
	phongShader.bind();

	//bind roughness
	phongShader.bindUniform("roughness", m_roughness);

	//bind reflection coefficient
	phongShader.bindUniform("reflectionCoefficient", m_reflection);

	//bind ambient light
	phongShader.bindUniform("Ia", ambientLight);

	//bind light
	phongShader.bindUniform("Id", light.diffuse);
	phongShader.bindUniform("Is", light.specular);
	phongShader.bindUniform("lightDirection", light.direction);

	//bind camera
	phongShader.bindUniform("cameraPosition", glm::vec3(glm::inverse(viewMatrix)[3]));

	//bind transform
	auto pvm = projectionMatrix * viewMatrix * objectTransform;
	phongShader.bindUniform("ProjectionViewModel", pvm);

	//bind transforms for lighting
	phongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(objectTransform)));

	//draw soulSpear
	objectMesh.draw();
}
