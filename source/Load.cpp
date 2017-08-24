
#include"graphics\Load.h"
#include"graphics\RenderObjects.h"

#define STB_IMAGE_IMPLEMENTATION
#include"STB\stb_image.h"


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
