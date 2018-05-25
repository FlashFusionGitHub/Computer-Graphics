#include "Instance.h"

Instance::Instance()
{
}


Instance::~Instance()
{
}

void Instance::draw(Scene* scene)
{
	scene->useShader(m_shader);
}
