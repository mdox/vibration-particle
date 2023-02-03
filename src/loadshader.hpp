#pragma once

#include <cassert>

extern "C"
{
#include "GL/glew.h"
}

#include "loadtextfile.hpp"

GLuint LoadShader(const std::string &filepath, GLenum shaderType)
{
	auto sourceCode = LoadTextFile(filepath);
	auto shader = glCreateShader(shaderType);

	const char *sourcePtr = reinterpret_cast<const char *>(sourceCode.data());
	glShaderSource(shader, 1, (const GLchar *const *) &sourcePtr, NULL);
	glCompileShader(shader);

	return shader;
}
