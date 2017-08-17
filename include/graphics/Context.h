#pragma once

struct GLFWwindow;

class Context
{

	private:
		GLFWwindow *handle;

	public:
		bool init(size_t width = 800, size_t height = 600,
		const char *title = "Graphics");

		bool getKey(int key);
		bool getMouseButton(int button);
		void getMousePosition(double &x_out, double &y_out);
		double getTime();

		bool step();

		bool term();

};
