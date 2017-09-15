#pragma once
#include "GameObjects.h"
#include "RenderObjects.h"
#include "graphics\draw.h"
#include "graphics\Load.h"
#include <cstring>
#include <map>

struct AssetManager
{
	Camera cams[8];
	map<std::string, SpecGloss> objects;
	StandardLight stdLights[8];
	DirectionalLight dirLights[64];
	SpecGloss findObj(std::string name);
};