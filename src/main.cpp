#include <ctime>

#include "config.hpp"
#include "window.hpp"
#include "program.hpp"
#include "particle.hpp"
#include "manager.hpp"
#include "visualizer.hpp"

void draw();
void update();
void resize(GLFWwindow *window, int width, int height);

Window window;
Program program;
Manager manager;
Visualizer visualizer;

clock_t start;

int main()
{
	window.draw = draw;
	window.update = update;
	window.resize = resize;
	window.init();

	program.init();
	manager.init(particlesCount);
	visualizer.init();

	start = clock();
	window.loop();

	visualizer.quit();
	program.quit();
	window.quit();

	return 0;
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	auto now = clock();
	auto diff = now - start;
	start = now;

	G = StaticG * (diff / (float)CLOCKS_PER_SEC);

	program.use();
	visualizer.use(manager.particles);

	visualizer.draw(particlesCount);

	visualizer.release();
	program.release();
}

void update()
{
	manager.update();
}

void resize(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
}
