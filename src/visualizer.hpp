#pragma once

#include <vector>
#include <cassert>

extern "C"
{
#include <GL/glew.h>
}

#include "particle.hpp"

static const GLuint aPositionLoc = 0;
static const GLuint aColorLoc = 1;

class Visualizer
{
public:
	GLuint vao;
	GLuint vbo;

	void draw(GLsizei count) {
		glDrawArrays(GL_POINTS, 0, count);
	}

	void use(const std::vector<Particle> &particles)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), &particles[0], GL_STREAM_DRAW);

		glBindVertexArray(vao);
		
		glVertexAttribPointer(aPositionLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
		glVertexAttribPointer(aColorLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const void *)offsetof(Particle, color));

		glEnableVertexAttribArray(aPositionLoc);
		glEnableVertexAttribArray(aColorLoc);
	}

	void release()
	{
		glDisableVertexAttribArray(aPositionLoc);
		glDisableVertexAttribArray(aColorLoc);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void init()
	{
		glGenVertexArrays(1, &vao);
		glCreateBuffers(1, &vbo);

		assert(vao);
		assert(vbo);
	}

	void quit()
	{
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}
};
