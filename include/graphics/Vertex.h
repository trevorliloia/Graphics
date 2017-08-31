#pragma once

#include"..\glm\glm.hpp"
using namespace glm;

struct Vertex
{
	vec4 pos;
	vec4 color;
	vec2 uv;
	vec4 norm;

	vec4 tangent;
	vec4 bitangent;
};