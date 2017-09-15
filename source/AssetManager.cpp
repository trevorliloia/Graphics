#include "..\include\graphics\AssetManager.h"
#include <cstring>
#include <map>

SpecGloss AssetManager::findObj(std::string name)
{
	return objects[name];
}
