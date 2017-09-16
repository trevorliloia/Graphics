#include "graphics\GameObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Load.h"
#include "glm\ext.hpp"
#include "graphics\Context.h"
#include "graphics\draw.h"
#include "graphics\AssetManager.h"

void main()
{
	Context context;
	context.init(1280, 720);

	Scene curScene;
	AssetManager manager;

	Vertex vquad[] = { { { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } } };
	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);
	
	// Game objects/geometry
	SpecGloss objects[8];

	/// floor
	objects[0].initLoad("quad", quad, "four_diffuse.tga", "four_specular.tga", "four_normal.tga", 4);

	manager.objects[objects[0].name] = objects[0];

	objects[0].model = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0)) * glm::scale(glm::vec3(5, 5, 1));
	/// Soulspear
	objects[1].initLoad("spear", "soulspear.obj", "soulspear_diffuse.tga", 
						"soulspear_specular.tga", "soulspear_normal.tga", 4);
	/// Earth
	objects[2].initLoad("sphere", "sphere.obj", "earth_diffuse.jpg",
						"earth_specular.jpg", "earth_normal.jpg", 4);
	objects[2].model = glm::scale(glm::vec3(2, 2, 2)) * glm::translate(glm::vec3(2, 1, -1));

	curScene.initCam();

	DirectionalLight dlights[2];
	dlights[0].initLight("dLightZero", 10, 1, glm::vec4(1, 1, 0, 1), glm::vec3(1, 0, 0));
	dlights[1].initLight("dLightOne", 10, 1, glm::vec4(0, 0, 1, 1), glm::vec3(-1, 0, 0));

	Shader gpass = loadShader("../../resources/shaders/gpass.vert", "../../resources/shaders/gpass.frag");
	Shader cpass = loadShader("../../resources/shaders/cpass.vert", "../../resources/shaders/cpass.frag");
	Shader lpassD = loadShader("../../resources/shaders/lpassD.vert", "../../resources/shaders/lpassD.frag");
	Shader spassD = loadShader("../../resources/shaders/shadow.vert", "../../resources/shaders/shadow.frag");
	
	curScene.initBuffer();


	Framebuffer gbuffer = makeFramebuffer(1280, 720, 4, true, 2, 2);
	Framebuffer lbuffer = makeFramebuffer(1280, 720, 4, false, 2, 0);
	Framebuffer sbuffer = makeFramebuffer(1024, 1034, 0, true, 0, 0);
	int loc = 0, slot = 0;
	while (context.step())
	{
		clearFramebuffer(gbuffer, true, true);
		setFlags(RenderFlag::DEPTH);
		for (int i = 0; i < 3; ++i)
		{
			loc = slot = 0;
			setUniforms(gpass, loc, slot, curScene.cam, objects[i]);
			s0_draw(gbuffer, gpass, objects[i].geo);
		}
		////////////////////
		//Lpass
		clearFramebuffer(lbuffer);
		
		for (int i = 0; i < 2; ++i)
		{
			clearFramebuffer(sbuffer);
			setFlags(RenderFlag::DEPTH);
			loc = slot = 0;
			for (int i = 0; i < 3; ++i)
			{
				loc = slot = 0;
				setUniforms(spassD, loc, slot, dlights[i].getProj(), dlights[i].getView(), objects[i].model);
				s0_draw(sbuffer, spassD, objects[i].geo);
			}


			setFlags(RenderFlag::ADDITIVE);
			loc = slot = 0;
			setUniforms(lpassD, loc, slot, curScene.cam, dlights[i], gbuffer.targets[3], gbuffer.targets[2], sbuffer.depthTarget);
			s0_draw(lbuffer, lpassD, quad);
		}
		//////////////////////
		/////Cpass

		loc = slot = 0;
		clearFramebuffer(curScene.screen);
		setUniforms(cpass, loc, slot,gbuffer.targets[0], lbuffer.targets[0]);
		s0_draw(curScene.screen, cpass, quad);
	}
	context.term();
}