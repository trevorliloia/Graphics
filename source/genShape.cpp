#include "..\include\graphics\genShape.h"
#include"graphics\Context.h"

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

		verts[i] = { {x,y,0,1},{cos(x),sin(y),tan((x + y) / 2),1},{x,y} };

		idxs[i * 3 + 0] = sides;
		idxs[i * 3 + 1] = i;
		idxs[i * 3 + 2] = i == sides-1? 0 : i + 1;
	}


	Geometry ret = makeGeometry(verts, vsize, idxs, isize);
	delete[] verts;
	delete[] idxs;

	return ret;
}

Geometry makeCheckerboard(int dim, float size)
{
	unsigned vdim = dim + 1;
	unsigned vsize = vdim*vdim;
	unsigned isize = 3 * 2 * dim*dim;
	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new  unsigned[isize];

	float step = dim / size;
	float offset = size / 2;

	int l = 0;

	for (int i = 0; i < vsize; ++i)
	{
		float x = (i % vdim) * step - offset;
		float y = (i / vdim) * step - offset;

		verts[i].pos = { x,y,0,1 };
		verts[i].color = { 1-(i % vdim),1-(i % vdim),0,1 };

		if (i == 1 && dim > 1 ||
			i % vdim != 1 &&
			i / vdim != vdim - 1 &&
			l < size)
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
