#include "RenderTargetsAndPostProcessingApp.h"
#include "Gizmos.h"
#include "Input.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <../dependencies/imgui/imgui.h>
#include <iostream>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

RenderTargetsAndPostProcessingApp::RenderTargetsAndPostProcessingApp() {

}

RenderTargetsAndPostProcessingApp::~RenderTargetsAndPostProcessingApp() {

}

bool RenderTargetsAndPostProcessingApp::startup() {
	
	setBackgroundColour(1.00f, 1.00f, 1.00f);

	m_light.diffuse = { 1, 1, 1 };
	m_light.specular = { 1, 1, 1 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// load a phong shader
	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");

	if (m_phongShader.link() == false) {
		printf("Phong Shader Error: %s\n",
			m_phongShader.getLastError());
		return false;
	}

	// load an OBJ and assign a scaled transform
	if (m_dragonMesh.load("./stanford/dragon.obj") == false) {
		printf("Dragon Mesh Error!\n");
		return false;
	}

	m_dragonTransform = {
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		0,0,0,1
	};

	if (m_renderTarget.initialise(1, getWindowWidth(),
		getWindowHeight()) == false) {
		printf("Render Target Error!\n");
		return false;
	}

	// create a fullscreen quad
	m_fullscreenQuad.initialiseFullscreenQuad();

	// load a post-processing shader
	m_postShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/post.vert");

	m_postShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/textured.frag");

	if (m_postShader.link() == false) {
		printf("Post Shader Error: %s\n",
			m_postShader.getLastError());
		return false;
	}

	return true;
}

void RenderTargetsAndPostProcessingApp::shutdown() {

	Gizmos::destroy();
}

void RenderTargetsAndPostProcessingApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	m_camera.update();

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

	if (oldFilter != filter) {
		switch (filter) {
		case 1:
			m_postShader.loadShader(aie::eShaderStage::FRAGMENT,
				"./shaders/blur.frag");
			break;
		case 2:
			m_postShader.loadShader(aie::eShaderStage::FRAGMENT,
				"./shaders/sharpen.frag");
			break;
		case 3:
			m_postShader.loadShader(aie::eShaderStage::FRAGMENT,
				"./shaders/distort.frag");
			break;
		case 4:
			m_postShader.loadShader(aie::eShaderStage::FRAGMENT,
				"./shaders/sobel.frag");
			break;
		case 5:
			m_postShader.loadShader(aie::eShaderStage::FRAGMENT,
				"./shaders/drawn.frag");
			break;
		case 6:
			m_postShader.loadShader(aie::eShaderStage::FRAGMENT,
				"./shaders/greyscale.frag");
			break;
		case 7:
			m_postShader.loadShader(aie::eShaderStage::FRAGMENT,
				"./shaders/sepia.frag");
			break;
		default:
			m_postShader.loadShader(aie::eShaderStage::FRAGMENT,
				"./shaders/textured.frag");
		}

		m_postShader.link();

		oldFilter = filter;
	}

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void RenderTargetsAndPostProcessingApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = m_camera.getProjectionMatrix(getWindowWidth(), getWindowHeight());
	m_viewMatrix = m_camera.getViewMatrix();

	// bind our render target
	m_renderTarget.bind();
	// wipe the screen to the background colour
	clearScreen();
	// draw scene with a light
	m_phongShader.bind();
	m_phongShader.bindUniform("Ia", m_ambientLight);
	m_phongShader.bindUniform("Id", m_light.diffuse);
	m_phongShader.bindUniform("Is", m_light.specular);
	m_phongShader.bindUniform("LightDirection", m_light.direction);
	m_phongShader.bindUniform("cameraPosition",
		vec3(glm::inverse(m_viewMatrix)[3]));
	// bind transform
	auto pvm = m_projectionMatrix * m_viewMatrix * m_dragonTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);
	// bind transforms for lighting
	m_phongShader.bindUniform("ModelMatrix", m_dragonTransform);
	m_phongShader.bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_dragonTransform)));
	// draw mesh
	m_dragonMesh.draw();

	ImGui::Begin("Filters");
	ImGui::SliderInt("Filter", &filter, 0, 7);
	ImGui::End();

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
	// unbind target to return to backbuffer
	m_renderTarget.unbind();
	// clear the backbuffer
	clearScreen();
	// bind post shader and textures
	m_postShader.bind();
	m_postShader.bindUniform("colourTarget", 0);
	m_renderTarget.getTarget(0).bind(0);
	// draw fullscreen quad
	m_fullscreenQuad.draw();

}