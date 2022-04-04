#include "controls.h"
#include "window.h"
#include "graphics.h"
#include "logic.h"

void hitKey(GLFWwindow* window, int key, int scan, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		if (winState)
		{
			fieldInit();
			draw();
			return;
		}

		if (key == GLFW_KEY_UP || key == GLFW_KEY_W ||
			key == GLFW_KEY_DOWN || key == GLFW_KEY_S ||
			key == GLFW_KEY_LEFT || key == GLFW_KEY_A ||
			key == GLFW_KEY_RIGHT || key == GLFW_KEY_D)
		{
			moveDirection direction;

			switch (key)
			{
			case GLFW_KEY_UP: case GLFW_KEY_W:
				direction = flipRows ? moveDirection::down : moveDirection::up;
				break;
			case GLFW_KEY_DOWN: case GLFW_KEY_S:
				direction = flipRows ? moveDirection::up : moveDirection::down;
				break;
			case GLFW_KEY_LEFT: case GLFW_KEY_A:
				direction = flipColumns ? moveDirection::right : moveDirection::left;
				break;
			case GLFW_KEY_RIGHT: case GLFW_KEY_D:
				direction = flipColumns ? moveDirection::left : moveDirection::right;
				break;
			}
			moveMake(activePlayer, direction);
		}
	}
}

void hitMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		if (winState)
		{
			fieldInit();
			draw();
			return;
		}
		double xPosition, yPosition;
		glfwGetCursorPos(window, &xPosition, &yPosition);
		bool isWidthOrHeightLarger = windowWidth >= windowHeight;
		double shiftPosition = (isWidthOrHeightLarger ? windowWidth - windowHeight : windowHeight - windowWidth) / 2.f;
		unsigned int clickedRow = floor((yPosition - (isWidthOrHeightLarger ? 0 : shiftPosition)) / (isWidthOrHeightLarger ? windowHeight : windowWidth) / (cellSize / 2)), clickedColumn = floor((xPosition - (isWidthOrHeightLarger ? shiftPosition : 0)) / (isWidthOrHeightLarger ? windowHeight : windowWidth) / (cellSize / 2));
		moveDirection direction = getMoveDirectionByTarget(activePlayer, clickedRow, clickedColumn);

		if (stepPossible(activePlayer, direction))
			moveMake(activePlayer, direction);
	}
}
