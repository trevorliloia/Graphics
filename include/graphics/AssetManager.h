#pragma once
#include "GameObjects.h"
#include "RenderObjects.h"
#include "graphics\draw.h"
#include "graphics\Load.h"
#include <cstring>

struct AssetManager
{
	Camera cams[8];
	SpecGloss objects[32];
	StandardLight stdLights[8];
	DirectionalLight dirLights[64];

};