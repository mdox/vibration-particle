
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

int main()
{
	window.draw = draw;
	window.update = update;
	window.resize = resize;
	window.init();

	program.init();
	manager.init(particlesCount);
	visualizer.init();

	window.loop();

	visualizer.quit();
	program.quit();
	window.quit();

	return 0;
}

void draw()
{
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
}
