#pragma once

#include "Application.h"
#include "Camera.h"
#include "Shader.h"
#include "tiny_obj_loader.h"
#include "OBJMesh.h"
#include "Model.h"

#include <glm/mat4x4.hpp>
#include <vector>

class AssignmentApp : public aie::Application {
public:

	AssignmentApp();
	virtual ~AssignmentApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	// camera transforms
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	// Camera in scene
	Camera m_camera;

	aie::ShaderProgram m_normalMap;

	Model m_soulSpear;
	Model m_axe;
	Model m_barrel;
	Model m_skull;
	Model m_chest;

	glm::vec3 m_ambientLight;

	glm::mat3 m_lights[2];

	struct MultiLights {
		union {
			glm::mat3 light;
			glm::vec3 lightAttributes[3];

			//[0] direction
			//[1] diffuse
			//[2] specular
		};
	};

	MultiLights m_light1;
	MultiLights m_light2;
};