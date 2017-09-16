#pragma once
#include "GameObjects.h"
#include "RenderObjects.h"
#include "graphics\draw.h"
#include "graphics\Load.h"
#include <cstring>
#include <map>

struct AssetManager
{
	map<std::string, Camera> cams;
	map<std::string, SpecGloss> objects;
	map<std::string, StandardLight> stdLights;
	map<std::string, DirectionalLight> dirLights;

	
	Camera findCam(std::string name);
	SpecGloss findObj(std::string name);
	StandardLight findSL(std::string name);
	DirectionalLight findDL(std::string name);
};