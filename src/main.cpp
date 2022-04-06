#include "main.h"

int main(int argc, char* argv[])
{
	if (!(windowHere = windowInit()))
		windowQuit(PROGRAM_FAILURE);
	windowSetup();
	fieldInit();
	drawInit();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
	windowQuit(PROGRAM_SUCCESS);
}