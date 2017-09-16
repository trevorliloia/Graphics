#include "..\include\graphics\AssetManager.h"
#include <cstring>
#include <map>

Camera AssetManager::findCam(std::string name)
{
	return cams[name];
}

SpecGloss AssetManager::findObj(std::string name)
{
	return objects[name];
}

StandardLight AssetManager::findSL(std::string name)
{
	return stdLights[name];
}

DirectionalLight AssetManager::findDL(std::string name)
{
	return dirLights[name];
}
