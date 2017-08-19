#pragma once

struct Vertex;



struct Geometry
{
	unsigned handle, vbo, ibo, size;
};

Geometry makeGeometry(const Vertex *verts, size_t vsize,
	const unsigned *idxs, size_t isize);

void freeGeometry(Geometry &g);

struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vert_src, const char *frag_src);

void freeShader(Shader &s);

struct Framebuffer
{
	unsigned handle, width, height;
};

struct Texture 
{
	unsigned handle;
	float w, h;
	//vec2 vertex;
};

Texture makeTex(unsigned w, unsigned h, unsigned c, const unsigned char *pixels);

void freeTex(Texture &t);