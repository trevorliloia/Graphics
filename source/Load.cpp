
#include"graphics\Load.h"
#include"graphics\RenderObjects.h"

#define STB_IMAGE_IMPLEMENTATION
#include"STB\stb_image.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include"OBJ\tiny_obj_loader.h"

#include<iostream>
#include<istream>
#include <fstream>
#include <sstream>
#include"graphics\Vertex.h"

Texture loadTexture(const char * path)
{
	Texture retval = { 0 };

	int w, h, c;

	unsigned char *pixels;

	stbi_set_flip_vertically_on_load(true);

	pixels = stbi_load(path, &w, &h, &c, STBI_default);

	retval = makeTex(w, h, c, pixels);

	stbi_image_free(pixels);

	return retval;
}



std::string fileToString(const char *path)
{
	std::stringstream str;
	std::ifstream stream(path);

	if (stream.is_open())
	{
		while (stream.peek() != EOF)
		{
			str << (char)stream.get();
		}
		stream.close();
		return str.str();
	}
}

Shader loadShader(const char *vpath, const char *fpath)
{
	Shader retval = { 0 };

	std::string vsource = fileToString(vpath);
	std::string fsource = fileToString(fpath);


	retval = makeShader(vsource.c_str(), fsource.c_str());
	return retval;
}

Geometry loadGeometry(const char * path)
{
	Geometry retval = {0,0,0,0};
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	size_t vsize = attrib.vertices.size()/3;
	Vertex *verts = new Vertex[vsize];

	for (size_t i = 0; i < vsize; ++i)
	{
		const float *p = &attrib.vertices[i * 3];
		verts[i].pos = {p[0], p[1], p[2], 1};
	}

	size_t isize = shapes[0].mesh.indices.size();
	size_t *indices = new unsigned[isize];
	for (size_t i = 0; i < isize; ++i)
	{
		indices[i] = shapes[0].mesh.indices[i].vertex_index;
	}


	retval = makeGeometry(verts, vsize, indices, isize);

	delete[] verts;
	delete[] indices;

	return retval;
}
