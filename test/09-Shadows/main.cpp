#include "graphics\Context.h"
#include "graphics\draw.h"
#include "graphics\Load.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "glm\ext.hpp"


int main()
{
	Context context;
	context.init();
// buffers
	Framebuffer screen = { 0, 800, 600 };
	Framebuffer fb_shadow = makeFramebuffer(2048, 2048, 0, true, 0, 0);
	Framebuffer fb_shadow1 = makeFramebuffer(2048, 2048, 0, true, 0, 0);
	// scene

	// floor

	Vertex vquad[] = 
	{
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ {  1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
		{ {  1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } }
	};

	unsigned quadidx[] = { 0,1,3,1,2,3 };

	solveTangents(vquad, 4, quadidx, 6);
	Geometry floor_geo = makeGeometry(vquad, 4, quadidx, 6);
	glm::mat4 floor_model = glm::rotate(glm::radians(90.0f), glm::vec3(-1, 0, 0))*glm::scale(glm::vec3(5, 5, 1));

	//spear
	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	glm::mat4 ss_model;

	//cube 
	Geometry cube_geo = loadGeometry("../../resources/models/cube.obj");
	glm::mat4 cube_model = glm::translate(glm::vec3(2, 1, -1));

	//camera
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 2, 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, screen.width / (float)screen.height, 1.f, 10.f);

	// light
	glm::vec3 light_dir = glm::normalize(glm::vec3(.8f, -1.f, -1.f));
	glm::mat4 light_proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view = glm::lookAt(-light_dir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));


	glm::vec3 light_dir1 = glm::normalize(glm::vec3(-.8f, -1.f, -1.f));
	glm::mat4 light_proj1 = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view1 = glm::lookAt(-light_dir1, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	//shader
	Shader shdr_shadow = loadShader("../../resources/shaders/shadow.vert",
		"../../resources/shaders/shadow.frag");

	Shader shdr_direct = loadShader("../../resources/shaders/direct.vert",
		"../../resources/shaders/direct.frag");

	int loc = 0, slot = 0;
	while (context.step())
	{
		float time = context.getTime();

		ss_model = glm::rotate(time, glm::vec3(0, 1, 0));


		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(fb_shadow, false, true);
		
		loc = 0, slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view, floor_model);
		s0_draw(fb_shadow, shdr_shadow, floor_geo);


		loc = 0, slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view, ss_model);
		s0_draw(fb_shadow, shdr_shadow, ss_geo);


		loc = 0, slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view, cube_model);
		s0_draw(fb_shadow, shdr_shadow, cube_geo);



		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(fb_shadow1, false, true);

		loc = 0, slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj1, light_view1, floor_model);
		s0_draw(fb_shadow1, shdr_shadow, floor_geo);


		loc = 0, slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj1, light_view1, ss_model);
		s0_draw(fb_shadow1, shdr_shadow, ss_geo);


		loc = 0, slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj1, light_view1, cube_model);
		s0_draw(fb_shadow1, shdr_shadow, cube_geo);


		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(screen);

		loc = 0, slot = 0;
		setUniforms(shdr_direct, loc, slot, cam_proj, cam_view, floor_model, 
			light_proj, light_view, fb_shadow.depthTarget, light_proj1, light_view1, fb_shadow1.depthTarget);
		s0_draw(screen, shdr_direct, floor_geo);


		loc = 0, slot = 0;
		setUniforms(shdr_direct, loc, slot, cam_proj, cam_view, ss_model, 
			light_proj, light_view, fb_shadow.depthTarget, light_proj1, light_view1, fb_shadow1.depthTarget);
		s0_draw(screen, shdr_direct, ss_geo);

		loc = 0, slot = 0;
		setUniforms(shdr_direct, loc, slot, cam_proj, cam_view, cube_model, 
			light_proj, light_view, fb_shadow.depthTarget, light_proj1, light_view1, fb_shadow1.depthTarget);
		s0_draw(screen, shdr_direct, cube_geo);
	}
	context.term();
	return 0;
}