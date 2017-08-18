#include "..\include\graphics\genShape.h"

Geometry makeNGon(size_t sides, float r)
{

	unsigned vsize = sides + 1;
	unsigned isize = sides * 3;

	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	float a = (2 * 3.14159265359) / sides;

	verts[sides] = { {0,0,0,1},{1,1,1,1} };

	for (int i = 0; i < sides; ++i)
	{
		float x = sin(i*a)*r;
		float y = cos(i*a)*r;

		verts[i] = { {x,y,0,1},{x/4,y/4,(x+y)/2,1} };

		idxs[i * 3 + 0] = sides;
		idxs[i * 3 + 1] = i;
		idxs[i * 3 + 2] = i == sides-1? 0 : i + 1;
	}


	Geometry ret = makeGeometry(verts, vsize, idxs, isize);
	delete[] verts;
	delete[] idxs;

	return ret;
}
