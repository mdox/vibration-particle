#pragma once

#include <cassert>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	GLFWwindow *window;
	void (*resize)(GLFWwindow *window, int width, int height);
	void (*draw)();
	void (*update)();

	void init()
	{
		glewExperimental = true;
		assert(glfwInit());

		glfwWindowHint(GLFW_SAMPLES, 1);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

		window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
		assert(window);

		glfwMakeContextCurrent(window);
		// glfwSwapInterval(1000 / 100);
		glewExperimental = true;
		assert(glewInit() == GLEW_OK);

		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
		glfwSetFramebufferSizeCallback(window, resize);

		glEnable(GL_PROGRAM_POINT_SIZE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void loop()
	{
		do
		{
			update();
			draw();

			// glfwSwapBuffers(window);
			glFlush();
			glfwPollEvents();
		} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
				 glfwWindowShouldClose(window) == 0);
	}

	void quit()
	{
		glfwTerminate();
	}
};
