#include"graphics\Context.h"
#include"graphics\RenderObjects.h"
#include"graphics\Vertex.h"
#include"graphics\draw.h"
#include"graphics\genShape.h"
#include"graphics\Load.h"
#include"glm/ext.hpp"

int main()
{
	Context context;
	context.init(800, 800);

	Texture tex = loadTexture("../Graphics/resources/textures/linksheet.png");

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 } },
		{ { -1,1,0,1 },{},{ 0,1 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };

	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Geometry cube = loadGeometry("../Graphics/resources/models/cube.obj");

	Shader sq = loadShader("../Graphics/resources/shaders/test.vert",
							"../Graphics/resources/shaders/test.frag");

	Shader scube = loadShader("../Graphics/resources/shaders/cube.vert",
							"../Graphics/resources/shaders/cube.frag");

	Framebuffer screen = { 0, 800, 800 };

	float x = 0, y = 0;
	while (context.step())
	{
		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(screen);

		int frame = 3;
		frame += context.getKey('w') * 3;
		frame += context.getKey('A') * 2;
		frame += context.getKey('D') * 1;
		frame %= 4;

		x += context.getKey('D') * 0.16;
		y += context.getKey('W') * 0.16;
		x += context.getKey('A') * 0.16;
		y += context.getKey('S') * 0.16;


		int loc = 0, tslot = 0;

		float time = context.getTime();		
		
		//setUniforms(sq, loc, tslot, tex, (int)(time * 3) % 4 + frame * 4, 4, 4, x, y);
		//setUniforms(sq, loc, tslot, tex);
		glm::mat4 mod_cube = glm::rotate(time, glm::vec3(1, 1, 1));


		//loc = 0, tslot = 0;
		setUniforms(scube, loc, tslot, mod_cube, tex);
		s0_draw(screen, scube, cube);
	}


	context.term();

	return 0;
}