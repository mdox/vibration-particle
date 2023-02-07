#pragma once

#include <vector>
#include <algorithm>
#include <execution>

#include <glm/glm.hpp>

#include "config.hpp"

class Particle
{
public:
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec3 color;

	void update()
	{
		position += velocity;
	}

	void react(const Particle &other)
	{
		auto d = other.position - position;
		auto r = glm::dot(d, d);
		auto m = 0.0001f;

		if (r < 0.0000000001f)
			return;
		else if (r < m)
			d *= -1.0f * m;

		velocity += d * G * m / r * r * glm::sqrt(r);
	}

	void interact(std::vector<Particle> &others)
	{
		// for (auto &other : others)
		// {
		// 	other.react(*this);
		// }

		std::for_each(
			std::execution::par_unseq,
			others.begin(),
			others.end(),
			[&](auto &other)
			{
				other.react(*this);
			});
	}
};
