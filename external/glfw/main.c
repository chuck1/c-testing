#include <stdlib.h>
#include <unistd.h>
#include <GLFW/glfw3.h>

void render(void)
{
	glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT);

	glBegin (GL_TRIANGLES);
	{
		glColor3f (0.6, 0.3, 0.3);
		glVertex2f (0, .5);
		glVertex2f (-.5, -.5);
		glVertex2f (.5, -.5);
	}
	glEnd ();
}

int main(int argc, char *argv[])
{
	GLFWwindow *win;

	if (!glfwInit()) {
		exit (EXIT_FAILURE);
	}

	win = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!win) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(win);

	while (!glfwWindowShouldClose(win)) {
		render();

		glfwSwapBuffers(win);
		sleep(1);
		glfwPollEvents();
	}

	glfwTerminate();
	exit(EXIT_SUCCESS);
	return 0;
}


