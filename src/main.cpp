#include "main.h"

int main(int argc, char* argv[])
{
	if (!(windowHere = windowInit()))
		windowQuit(PROGRAM_FAILURE);
	windowSetup();
	drawInit();
	fieldInit();

	while (!glfwWindowShouldClose(window))
	{
		draw();
		glfwPollEvents();
	}
	windowQuit(PROGRAM_SUCCESS);
}
