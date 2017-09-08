#pragma once
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "RenderObjects.h"


struct Camera
{
	glm::mat4 proj;
	glm::mat4 view;
};

struct SpecGloss
{
	Geometry geo;
	glm::mat4 model;
	Texture diffuse;
	Texture specular;
	Texture normal;
	float gloss;
};

struct StandardLight
{
	glm::vec3 dir;
	glm::vec4 color;
	float intensity;
	glm::vec4 ambient;
	int type;
};

struct DirectionalLight
{
	glm::vec3 target;
	float range;
	glm::vec3 direction;
	
	glm::mat4 getProj() const
	{
		return glm::ortho<float>(-range, range, -range, range, -range, range);
	}
	
	glm::mat4 getView() const
	{
		return glm::lookAt(direction, target, glm::vec3(0, 1, 0));
	}

	glm::vec4 color;
	float intensity;
};

namespace _internal
{
	void t_setUniform(const Shader &s, int &loc_io, int & tex_io, const Camera &val);
	void t_setUniform(const Shader &s, int &loc_io, int & tex_io, const SpecGloss &val);
	void t_setUniform(const Shader &s, int &loc_io, int & tex_io, const DirectionalLight &val);

}