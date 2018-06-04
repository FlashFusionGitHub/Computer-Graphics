#include "ParticleEffectsApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

ParticleEffectsApp::ParticleEffectsApp() {

}

ParticleEffectsApp::~ParticleEffectsApp() {

}

bool ParticleEffectsApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	m_particleShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/texturedparticle.vert");
	m_particleShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/texturedparticle.frag");

	if (m_particleShader.link() == false) {
		printf("Particle Shader Error: %s\n", m_particleShader.getLastError());
		return false;
	}

	if (m_particleTexture.load("./textures/bubble.png") == false) {
		printf("Failed to load texture!\n");
		return false;
	}

	m_emitter = new ParticleEmitter();

	m_emitter->initalise(250, 80,
		2.5f, 5.0f,
		1, 9,
		0.1f, 6.0f,
		glm::vec4(1, 0, 0, 1), glm::vec4(1, 1, 0, 1), false, true);

	m_particleTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	return true;
}

void ParticleEffectsApp::shutdown() {

	Gizmos::destroy();
}

void ParticleEffectsApp::update(float deltaTime) {

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

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	m_emitter->update(deltaTime, m_camera.getTransform());

	m_camera.update();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void ParticleEffectsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = m_camera.getProjectionMatrix(getWindowWidth(), getWindowHeight());
	m_viewMatrix = m_camera.getViewMatrix();

	// bind particle shader
	m_particleShader.bind();
	// bind particle transform
	auto pvm = m_projectionMatrix * m_viewMatrix * m_particleTransform;
	m_particleShader.bindUniform("ProjectionViewModel", pvm);

	m_particleTexture.bind(0);
	m_particleShader.bindUniform("diffuseTexture", 0);

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	// draw transparency last
	m_emitter->draw();
}