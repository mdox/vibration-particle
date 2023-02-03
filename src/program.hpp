#pragma once

#include <cstdlib>
#include <iostream>

extern "C"
{
#include <GL/glew.h>
#include <GLFW/glfw3.h>
}

#include "loadshader.hpp"

class Program
{
public:
	GLuint program;

	void use()
	{
		glUseProgram(program);
	}

	void release()
	{
		glUseProgram(0);
	}

	void init()
	{
		program = glCreateProgram();

		assert(program);
		
		auto vertexShader = LoadShader("shaders/particle.vs", GL_VERTEX_SHADER);
		auto fragmentShader = LoadShader("shaders/particle.fs", GL_FRAGMENT_SHADER);

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		GLint infoLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
		if (infoLength > 0)
		{
			std::string info(infoLength + 1, '\0');
			glGetProgramInfoLog(program, infoLength, nullptr, &info[0]);
			std::cout << info << "\n";
			exit(1);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void quit()
	{
		glDeleteProgram(program);
	}
};
