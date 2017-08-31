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
	context.init();

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Texture floor_normal = loadTexture("../../resources/textures/Ezra.png");

	Shader standard = loadShader("../../resources/shaders/standard.vert",
		"../../resources/shaders/standard.frag");

	Framebuffer screen = { 0, 800, 600 };





	// Camera
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);

	// Model
	glm::mat4 go_model;

	// Light
	glm::vec3 light_direction = glm::normalize(glm::vec3(1, -1, 1));



	while (context.step())
	{
		float time = context.getTime();
		go_model = glm::rotate(time, glm::vec3(1, 0, 0));


		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, slot = 0;
		setUniforms(standard, loc, slot,
			cam_proj, cam_view,			// Camera information
			go_model, floor_normal,		// Surface information
			light_direction);




		s0_draw(screen, standard, quad);
	}
	context.term();
	return 0;
}
