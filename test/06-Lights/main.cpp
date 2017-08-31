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
	context.init(800,600);

	Texture tex = loadTexture("../../resources/textures/linksheet.png");

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 } },
		{ { -1,1,0,1 },{},{ 0,1 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };

	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Geometry cube = loadGeometry("../../resources/models/cube.obj");

	Shader sq = loadShader("../../resources/shaders/test.vert",
		"../../resources/shaders/test.frag");

	Shader scube = loadShader("../../resources/shaders/cube.vert",
		"../../resources/shaders/cube.frag");

	Shader mvplite = loadShader("../../resources/shaders/mvplite.vert",
		"../../resources/shaders/mvplite.frag");

	Geometry ss_geo = loadGeometry("../resources/models/soulspear.obj");

	Texture ss_diffuse = loadTexture("../resources/textures/soulspear_diffuse.tga");

	Shader lambert = loadShader("../resources/shaders/lambert.vert",
		"../resources/shaders/lambert.frag");

	Framebuffer screen = { 0,800,600 };


	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);
	glm::mat4 go_model;


	float x = 0, y = 0;


	glm::vec3 dl_dir = glm::normalize(glm::vec3(1, -1, 1));
	glm::vec4 dl_col = glm::vec4(.7f, .6f, .2f, 1.f);

	while (context.step())
	{
		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);
		int loc = 0, slot = 0;
		setUniforms(lambert, loc, slot,  cam_proj,cam_view, go_model, ss_diffuse,
			dl_dir, dl_col);
		s0_draw(screen, lambert, ss_geo);

		int frame = 3;
		frame += context.getKey('w') * 3;
		frame += context.getKey('A') * 2;
		frame += context.getKey('D') * 1;
		frame %= 4;

		x += context.getKey('D') * 0.16;
		y += context.getKey('W') * 0.16;
		x += context.getKey('A') * 0.16;
		y += context.getKey('S') * 0.16;



		float time = context.getTime();

		//setUniforms(sq, loc, tslot, tex, (int)(time * 3) % 4 + frame * 4, 4, 4, x, y);
		//setUniforms(sq, loc, tslot, tex);
		//glm::mat4 mod_cube = glm::rotate(time, glm::vec3(1, 1, 1));

		//cam_view = glm::lookAt(glm::vec3(0, 3, -4), targetPosition, glm::vec3(0, 1, 0));
		//loc = 0, tslot = 0;
		//setUniforms(ss_shader, loc, tslot, mod_cube, ss_texture);

		setUniforms(mvplite, loc, slot, cam_proj, cam_view, go_model, ss_diffuse);

		s0_draw(screen, mvplite, ss_geo);
	}


	context.term();

	return 0;
}