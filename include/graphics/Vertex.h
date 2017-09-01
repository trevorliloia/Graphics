#pragma once

#include"..\glm\glm.hpp"
using namespace glm;

struct Vertex
{
	vec4 position;
	vec4 color;
	vec2 texcoord;
	vec4 normal;

	vec4 tangent;
	vec4 bitangent;
};