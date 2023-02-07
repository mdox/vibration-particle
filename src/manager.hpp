#pragma once

#include <vector>
#include <algorithm>
#include <execution>

#include <omp.h>

#include <glm/gtc/random.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "particle.hpp"

class Manager
{
public:
	std::vector<Particle> particles;

	void update()
	{
		#pragma omp parallel for
		for (auto &particle : particles)
		{
			particle.interact(particles);
		}

		// std::for_each(
		// 	std::execution::par_unseq,
		// 	particles.begin(),
		// 	particles.end(),
		// 	[&](auto &particle)
		// 	{
		// 		particle.interact(particles);
		// 	});

		#pragma omp parallel for
		for (auto &particle : particles)
		{
			particle.update();
		}

		// std::for_each(
		// 	std::execution::par_unseq,
		// 	particles.begin(),
		// 	particles.end(),
		// 	[&](auto &particle)
		// 	{
		// 		particle.update();
		// 	});
	}

	void init(int count)
	{
		particles.resize(count);

		int index = 0;

		for (Particle &particle : particles)
		{
			glm::vec3 pos3 = glm::rotateZ(glm::vec3(0.0f, 0.125f, 0.0f), glm::radians(360.0f * index / count));

			index++;

			particle.position = glm::vec2(pos3.x, pos3.y);
			particle.velocity = glm::vec2(pos3.y, pos3.x) * 0.001f;
			particle.color = glm::vec3(0.5f, 0.5f, 0.5f) + glm::ballRand(0.5f);
		}
	}
};
