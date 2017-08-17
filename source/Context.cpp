#include"glinc.h"
#include "..\include\graphics\Context.h"

#ifdef _DEBUG
#include<iostream>
void APIENTRY GL_errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar *message,
	const void *userParam)
{
	std::cerr << message << std::endl;
}

#endif



bool Context::init(size_t width, size_t height, const char * title)
{
	glfwInit();

	handle = glfwCreateWindow(width, height, title, 0, 0);
	glfwMakeContextCurrent(handle);

	glewExperimental = true;
	glewInit();


#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(GL_errorCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);
#endif

	return true;
}

bool Context::getKey(int key)
{
	return glfwGetKey(handle, key);

}


bool Context::getMouseButton(int button)
{
	return glfwGetMouseButton(handle, button);
}

void Context::getMousePosition(double & x_out, double & y_out)
{
	return glfwGetCursorPos(handle, &x_out, &y_out);
}

double Context::getTime()
{
	return glfwGetTime();
}

bool Context::step()
{
	glfwPollEvents();

	glfwSwapBuffers(handle);
	return !glfwWindowShouldClose(handle);
}

bool Context::term()
{
	glfwTerminate();
	handle = nullptr;
	return true;
}
