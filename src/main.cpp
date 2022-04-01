#include "main.h"

int main(int argc, char* argv[])
{
	if (!(windowHere = windowInit()))
		quit(PROGRAM_FAILURE);
	windowSetup();
	drawInit();
	fieldInit();

	while (!glfwWindowShouldClose(window))
	{
		draw();
		glfwPollEvents();
	}
}
