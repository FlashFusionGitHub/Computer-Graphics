#pragma once
#include <glm/glm.hpp>
#include <vector>

class BoundingSphere 
{
public:
	BoundingSphere();
	~BoundingSphere();

	void fit(const std::vector<glm::vec3>& points);

	glm::vec3 centre;
	float radius;
};

