#include "controls.h"

void hitKey(GLFWwindow* window, int key, int scan, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_UP || key == GLFW_KEY_W ||
			key == GLFW_KEY_DOWN || key == GLFW_KEY_S ||
			key == GLFW_KEY_LEFT || key == GLFW_KEY_A ||
			key == GLFW_KEY_RIGHT || key == GLFW_KEY_D)
		{
			moveDirection direction;

			switch (key)
			{
			case GLFW_KEY_UP: case GLFW_KEY_W:
				direction = moveDirection::up;
				break;
			case GLFW_KEY_DOWN: case GLFW_KEY_S:
				direction = moveDirection::down;
				break;
			case GLFW_KEY_LEFT: case GLFW_KEY_A:
				direction = moveDirection::left;
				break;
			case GLFW_KEY_RIGHT: case GLFW_KEY_D:
				direction = moveDirection::right;
				break;
			}
			moveMake(direction);
		}

	}
}
