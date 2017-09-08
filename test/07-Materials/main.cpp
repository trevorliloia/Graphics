#include "graphics\Context.h"
#include "graphics\draw.h"
#include "graphics\Load.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "glm\ext.hpp"


int main()
{
	Context context;
	context.init(1280, 720);

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

	Framebuffer screen = { 0, 1280, 720 };


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
	glm::mat4 cam_proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 5.f);

	//////////////////////////
	// Light
	glm::vec3 l_dir = glm::normalize(glm::vec3(.2, -1, -1));
	glm::vec4 l_color = glm::vec4(1.0, .5, 1.0, 1);
	float     l_intensity = 4.0;
	glm::vec4 l_ambient = glm::vec4(.2, .5, .1, 1);
	int		  l_type = 0;


	Framebuffer fBuffer = makeFramebuffer(1280, 720, 4, true, 3, 1);

	Shader fsq_shader = loadShader("../../resources/shaders/quad.vert",
		"../../resources/shaders/quad.frag");
	while (context.step())
	{
		float time = context.getTime();
		ss_model = glm::rotate(time, glm::vec3(0, 1, 0));

		//////////////////////////////////////////////
		//////// Frame Buffer Pass
		clearFramebuffer(fBuffer);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, slot = 0;
		setUniforms(standard, loc, slot,
			cam_proj, cam_view,	// Camera data!
			ss_model, ss_diffuse, ss_specular, ss_normal, ss_gloss, // model data!
			l_dir, l_color, l_intensity, l_ambient, l_type		  // light data!
		);

		s0_draw(fBuffer, standard, ss_geo);

		//////////////////////////////////////////////
		//////// Screen Pass
		clearFramebuffer(screen);
		loc = 0, slot = 0;
		setUniforms(fsq_shader, loc, slot, fBuffer.targets[1],
			fBuffer.targets[2],
			fBuffer.targets[3],
			time);
		s0_draw(screen, fsq_shader, quad);
	}
	context.term();
	return 0;
}










//#include "graphics\Context.h"
//#include "graphics\draw.h"
//#include "graphics\Load.h"
//#include "graphics\RenderObjects.h"
//#include "graphics\Vertex.h"
//#include "glm\ext.hpp"
//#include "graphics\GameObjects.h"
//
//int main()
//{
//	Context context;
//	context.init();
//
//	Vertex vquad[] = {
//		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
//		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
//		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
//		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } }
//	};
//
//	unsigned quadidx[] = { 0,1,3, 1,2,3 };
//	solveTangents(vquad, 4, quadidx, 6);
//	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);
//
//	Shader standard = loadShader("../../resources/shaders/standard.vert",
//		"../../resources/shaders/standard.frag");
//
//	Framebuffer screen = { 0, 800, 600 };
//	Framebuffer fBuffer = makeFramebuffer(800, 600, 4, true, 3, 1);
//
//	Shader fsq_shader = loadShader("../../resources/shaders/quad.vert",
//		"../../resources/shaders/quad.frag");
//
//	////////////////////////
//	/// Model Data
//	SpecGloss sceneObj[2];
//	
//
//	sceneObj[0].geo = loadGeometry("../../resources/models/soulspear.obj");
//	sceneObj[0].model;
//
//	sceneObj[0].normal = loadTexture("../../resources/textures/soulspear_normal.tga");
//	sceneObj[0].diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
//	sceneObj[0].specular = loadTexture("../../resources/textures/soulspear_specular.tga");
//	sceneObj[0].gloss = 4.0f;
//
//
//	sceneObj[1].geo = loadGeometry("../../resources/models/soulspear.obj");
//	sceneObj[1].model = glm::rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
//
//	sceneObj[1].normal = loadTexture("../../resources/textures/soulspear_normal.tga");
//	sceneObj[1].diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
//	sceneObj[1].specular = loadTexture("../../resources/textures/soulspear_specular.tga");
//	sceneObj[1].gloss = 4.0f;
//
//	//////////////////////////
//	// Camera Data
//	Camera cam;
//
//	cam.view = glm::lookAt(glm::vec3(0, 2, 3),
//		glm::vec3(0, 2, 0),
//		glm::vec3(0, 1, 0));
//	cam.proj = glm::perspective(45.f, 800.f / 600.f, 1.f, 5.f);
//
//	//////////////////////////
//	// Light
//	StandardLight l;
//
//	l.dir = glm::normalize(glm::vec3(1, -1, -1));
//	l.color = glm::vec4(.7, .5, .9, 1);
//	l.intensity = 4.0;
//	l.ambient = glm::vec4(.2, .2, .01, 1);
//	l.type = 0;
//
//
//
//	while (context.step())
//	{
//		float time = context.getTime();
//		//ss_model = glm::rotate(time, glm::vec3(0, 1, 0));
//
//		//////////////////////////////////////////////////////////////////////////////////////////
//		clearFramebuffer(fBuffer);
//		setFlags(RenderFlag::DEPTH);
//
//		for (int i = 0; i < 2; ++i)
//		{
//			int loc = 0, slot = 0;
//
//			setUniforms(standard, loc, slot,
//			cam.proj, cam.view,	
//				sceneObj[i].model, sceneObj[i].diffuse, sceneObj[i].specular, sceneObj[i].normal, sceneObj[i].gloss,
//			l.dir, l.color, l.intensity, l.ambient, l.type
//				);
//			s0_draw(fBuffer, standard, sceneObj[i].geo);
//		}
//		
//
//
//
//		///////////////////////////////////////////////////////////////////////////////////////
//		
//		clearFramebuffer(screen);
//		int loc = 0, slot = 0;
//		setUniforms(fsq_shader, loc, slot, fBuffer.targets[1], fBuffer.targets[2], fBuffer.targets[3], time);
//		s0_draw(screen, fsq_shader, quad);
//		
//	}
//	context.term();
//	return 0;
//}




