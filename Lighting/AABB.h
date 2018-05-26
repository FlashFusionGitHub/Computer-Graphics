#pragma once

#include <glm/glm.hpp>
#include <vector>

class AABB 
{
public:
	AABB();
	~AABB();

	void reset();

	void fit(const std::vector<glm::vec3>& points);

	glm::vec3 min, max;
};
