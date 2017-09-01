#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "glm\glm.hpp"

#include"graphics\genShape.h"

#include <cmath>

#include <random>

Geometry makeNGon(size_t N, float r)
{
	unsigned vsize = N + 1;
	unsigned isize = N * 3;
	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	// circle = 360 or 2PI
	// angle of each triangle = 360 / N
	float a = (2 * 3.14159265359) / N;

	verts[N] = { { 0,0,0,1 },{ 1,1,1,1 } };

	for (int i = 0; i < N; ++i)
	{
		float x = cos(i*a)*r; // angle to vector
		float y = sin(i*a)*r;

		verts[i] = { { x,y,0,1 },{ x,y,0,1 } };

		idxs[i * 3 + 0] = N;
		idxs[i * 3 + 1] = i;
		idxs[i * 3 + 2] = (i + 1) % N;
	}

	Geometry ret = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;

	return ret;
}





Geometry makeCheckerboard(int dim, float size)
{
	unsigned vdim = dim + 1;
	unsigned vsize = vdim*vdim;		    // # of vertices
	unsigned isize = 3 * 2 * dim * dim; // # of quads/tris
	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	float step = size / dim;
	float offset = size / 2;
	int l = 0;
	for (int i = 0; i < vsize; ++i)
	{
		float x = (i % vdim)*step - offset;
		float y = (i / vdim)*step - offset;

		verts[i].position = { x,y,0,1 };
		verts[i].color = { rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX,1 };

		if (i % vdim != vdim - 1 && i / vdim != vdim - 1)
		{
			idxs[l++] = i;
			idxs[l++] = i + 1;
			idxs[l++] = i + vdim;

			idxs[l++] = i + 1;
			idxs[l++] = i + vdim;
			idxs[l++] = i + vdim + 1;
		}
	}

	Geometry ret = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;

	return ret;
}


//#include "..\include\graphics\genShape.h"
//#include"graphics\Context.h"
//
//Geometry makeNGon(size_t sides, float r)
//{
//
//	unsigned vsize = sides + 1;
//	unsigned isize = sides * 3;
//
//	Vertex *verts = new Vertex[vsize];
//	unsigned *idxs = new unsigned[isize];
//
//	float a = (2 * 3.14159265359) / sides;
//
//	verts[sides] = { {0,0,0,1},{1,1,1,1} };
//
//	for (int i = 0; i < sides; ++i)
//	{
//		float x = sin(i*a)*r;
//		float y = cos(i*a)*r;
//
//		verts[i] = { {x,y,0,1},{cos(x),sin(y),tan((x + y) / 2),1},{x,y} };
//
//		idxs[i * 3 + 0] = sides;
//		idxs[i * 3 + 1] = i;
//		idxs[i * 3 + 2] = i == sides-1? 0 : i + 1;
//	}
//
//
//	Geometry ret = makeGeometry(verts, vsize, idxs, isize);
//	delete[] verts;
//	delete[] idxs;
//
//	return ret;
//}
//
//Geometry makeCheckerboard(int dim, float size)
//{
//	unsigned vdim = dim + 1;
//	unsigned vsize = vdim*vdim;
//	unsigned isize = 3 * 2 * dim*dim;
//	Vertex *verts = new Vertex[vsize];
//	unsigned *idxs = new  unsigned[isize];
//
//	float step = dim / size;
//	float offset = size / 2;
//
//	int l = 0;
//
//	for (int i = 0; i < vsize; ++i)
//	{
//		float x = (i % vdim) * step - offset;
//		float y = (i / vdim) * step - offset;
//
//		verts[i].pos = { x,y,0,1 };
//		verts[i].color = { 1-(i % vdim),1-(i % vdim),0,1 };
//
//		if (i == 1 && dim > 1 ||
//			i % vdim != 1 &&
//			i / vdim != vdim - 1 &&
//			l < size)
//		{
//			idxs[l++] = i;
//			idxs[l++] = i + 1;
//			idxs[l++] = i + vdim;
//
//			idxs[l++] = i + 1;
//			idxs[l++] = i + vdim;
//			idxs[l++] = i + vdim + 1;
//		}
//	}
//
//	Geometry ret = makeGeometry(verts, vsize, idxs, isize);
//	delete[] verts;
//	delete[] idxs;
//
//	return ret;
//}
