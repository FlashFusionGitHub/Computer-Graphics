#include "MaterialsAndTexturesApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

MaterialsAndTexturesApp::MaterialsAndTexturesApp() {

}

MaterialsAndTexturesApp::~MaterialsAndTexturesApp() {

}

bool MaterialsAndTexturesApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(15), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	if (m_shader.link() == false) {
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	//if (m_gridTexture.load("./textures/numbered_grid.tga") == false) {
	//	printf("Failed to load texture!\n");
	//	return false;
	//}

	if (m_soulSpearMesh.load("./soulspear/soulspear.obj", true, true) == false) {
		printf("Soulspear mesh error!\n");
		return false;
	}

	//m_quadMesh.initialiseQuad();

	//m_quadTransform = {
	//	10, 0, 0, 0,
	//	0, 10, 0, 0,
	//	0, 0, 10, 0,
	//	0, 0, 0, 1 };

	m_soulSpearTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };

	return true;
}

void MaterialsAndTexturesApp::shutdown() {

	Gizmos::destroy();
}

void MaterialsAndTexturesApp::update(float deltaTime) {

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

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	camera.update();

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void MaterialsAndTexturesApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = camera.getProjectionMatrix(getWindowWidth(), getWindowHeight());
	m_viewMatrix = camera.getViewMatrix();

	//bind shader
	m_shader.bind();

	//bind transform
	auto pvm = m_projectionMatrix * m_viewMatrix /* * m_quadTransform */ * m_soulSpearTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);

	// bind texture location
	m_shader.bindUniform("diffuseTexture", 0);

	// bind texture to specified location
	//m_gridTexture.bind(0);

	//draw quad
	//m_quadMesh.draw();

	//draw spear mesh
	m_soulSpearMesh.draw();

	//draw 3D gizmos
	Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	//draw 2D gizmos using orthogonal projection matrix
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}