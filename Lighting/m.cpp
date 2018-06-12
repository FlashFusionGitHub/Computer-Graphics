#include "m.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

m::m()
{
}


m::~m()
{
}

void m::load(aie::ShaderProgram& phongShader, glm::vec3& ambientLight, glm::mat4& projectionMatrix, glm::mat4& viewMatrix,
	glm::mat4& objectTransform, aie::OBJMesh& objectMesh)
{
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
