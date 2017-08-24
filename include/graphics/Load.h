#pragma once

#include"RenderObjects.h"
#include<iostream>
using namespace std;

Texture loadTexture(const char *path);

//void fileToString(const char *path);

Shader loadShader(const char *vpath, const char *fpath);

Geometry loadGeometry(const char *path);