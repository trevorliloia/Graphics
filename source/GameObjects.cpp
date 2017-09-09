#include "..\include\graphics\GameObjects.h"
#include "graphics\draw.h"
#include "graphics\Load.h"
#include <cstring>

void _internal::t_setUniform(const Shader & s, int & loc_io, int & tex_io, const Camera & val)
{
	t_setUniform(s,loc_io, tex_io, val.proj);
	t_setUniform(s, loc_io, tex_io, val.view);
}

void _internal::t_setUniform(const Shader & s, int & loc_io, int & tex_io, const SpecGloss & val)
{
	t_setUniform(s, loc_io, tex_io, val.model);
	t_setUniform(s, loc_io, tex_io, val.diffuse);
	t_setUniform(s, loc_io, tex_io, val.specular);
	t_setUniform(s, loc_io, tex_io, val.normal);
	t_setUniform(s, loc_io, tex_io, val.gloss);
}

void _internal::t_setUniform(const Shader & s, int & loc_io, int & tex_io, const DirectionalLight & val)
{
	t_setUniform(s, loc_io, tex_io, val.getProj());
	t_setUniform(s, loc_io, tex_io, val.getView());
	t_setUniform(s, loc_io, tex_io, val.color);
	t_setUniform(s, loc_io, tex_io, val.intensity);
}

void Scene::initCam()
{
	cam.view = glm::lookAt(glm::vec3(0, 2, 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	cam.proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 10.f);
}

void Scene::initBuffer()
{
	screen = { 0, 1280, 720 };
}


void SpecGloss::initLoad(const char * geoName, const char * diffName, 
			const char * specName, const char * normName, int glossVal)
{
	std::string temp = (std::string("../../resources/models/") + std::string(geoName));
	geo = loadGeometry(temp.c_str());
	temp = (std::string("../../resources/textures/") + std::string(diffName));
	diffuse = loadTexture(temp.c_str());
	temp = (std::string("../../resources/textures/") + std::string(specName));
	specular = loadTexture(temp.c_str());
	temp = (std::string("../../resources/textures/") + std::string(normName));
	normal = loadTexture(temp.c_str());
	gloss = glossVal;
}

void SpecGloss::initLoad(Geometry g, const char * diffName, const char * specName, const char * normName, int glossVal)
{
	geo = g;
	std::string temp = (std::string("../../resources/textures/") + std::string(diffName));
	diffuse = loadTexture(temp.c_str());
	temp = (std::string("../../resources/textures/") + std::string(specName));
	specular = loadTexture(temp.c_str());
	temp = (std::string("../../resources/textures/") + std::string(normName));
	normal = loadTexture(temp.c_str());
	gloss = glossVal;
}

void DirectionalLight::initLight(float r, float i, glm::vec4 clr, glm::vec3 dir)
{
	range = r;
	intensity = i;
	color = clr;
	direction = dir;
}
