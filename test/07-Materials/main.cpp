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

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Shader standard = loadShader("../../resources/shaders/standard.vert",
		"../../resources/shaders/standard.frag");

	Framebuffer screen = { 0, 800, 600 };
	Framebuffer fBuffer = makeFramebuffer(800, 600, 4, true, 3, 1);

	Shader fsq_shader = loadShader("../../resources/shaders/quad.vert",
		"../../resources/shaders/quad.frag");

	////////////////////////
	/// Model Data
	Geometry  ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	glm::mat4 ss_model;

	Texture   ss_normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	Texture   ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Texture   ss_specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	float     ss_gloss = 4.0f;

	//////////////////////////
	// Camera Data
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 2, 3),
		glm::vec3(0, 2, 0),
		glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .2f, 4.f);

	//////////////////////////
	// Light
	glm::vec3 l_dir = glm::normalize(glm::vec3(1, -1, -1));
	glm::vec4 l_color = glm::vec4(.7, .5, .9, 1);
	float     l_intensity = 4.0;
	glm::vec4 l_ambient = glm::vec4(.2, .2, .01, 1);
	int		  l_type = 0;



	while (context.step())
	{
		float time = context.getTime();
		//ss_model = glm::rotate(time, glm::vec3(0, 1, 0));

		//////////////////////////////////////////////////////////////////////////////////////////
		clearFramebuffer(fBuffer);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, slot = 0;

		setUniforms(standard, loc, slot,
			cam_proj, cam_view,	
			ss_model, ss_diffuse, ss_specular, ss_normal, ss_gloss,
			l_dir, l_color, l_intensity, l_ambient, l_type		 
				);
		s0_draw(fBuffer, standard, ss_geo);
		////////////////////////////////////////////////////////////////////////////////////////
		
		clearFramebuffer(screen);
		loc = 0; slot = 0;
		setUniforms(fsq_shader, loc, slot, fBuffer.targets[0]);
		s0_draw(screen, fsq_shader, quad);
		
	}
	context.term();
	return 0;
}