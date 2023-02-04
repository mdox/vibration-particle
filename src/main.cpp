#include <ctime>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

glm::mat4 projection = glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 model = glm::mat4(1.0f);

GLuint projectionLoc;
GLuint viewLoc;
GLuint modelLoc;

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

	projectionLoc = glGetUniformLocation(program.program, "projection");
	viewLoc = glGetUniformLocation(program.program, "view");
	modelLoc = glGetUniformLocation(program.program, "model");

	start = clock();
	window.loop();

	visualizer.quit();
	program.quit();
	window.quit();

	return 0;
}

void draw()
{
	// glClear(GL_COLOR_BUFFER_BIT);

	auto now = clock();
	auto diff = now - start;
	start = now;

	G = StaticG * (diff / (float)CLOCKS_PER_SEC);
	// G = StaticG * 0.0001f;

	program.use();

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

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

	float s = width / (float)height;

	projection = glm::ortho(
		-s,
		s,
		-1.0f,
		1.0f);
}
