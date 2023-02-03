#pragma once

#include <vector>
#include <algorithm>
#include <execution>

#include <glm/gtc/random.hpp>

#include "particle.hpp"

class Manager
{
public:
	std::vector<Particle> particles;

	void update()
	{
		for (auto &particle : particles)
		{
			particle.interact(particles);
		}

		for (auto &particle : particles)
		{
			particle.update();
		}
	}

	void init(int count)
	{
		particles.resize(count);

		for (Particle &particle : particles)
		{
			particle.position = glm::diskRand(1.0f);
			particle.color = glm::vec3(0.5f, 0.5f, 0.5f) + glm::ballRand(0.25f);
		}
	}
};
