// This file includes methods that handles mouse and keyboard events.
#include "controls.h"
#include "debug.h"
#include "window.h"
#include "graphics.h"
#include "logic.h"
#include <cmath>

void hitKey(GLFWwindow* window, int key, int scan, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_ESCAPE)
			windowQuit(PROGRAM_SUCCESS);

		// Restart the game by hitting R or any key after one of the players won.
		if (winState || key == GLFW_KEY_R)
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

			// Associate specific key with move direction and try to move at this direction.
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
		// Same as for the keys.
		if (winState)
		{
			fieldInit();
			draw();
			return;
		}
		// This is to identify, what exact cell on the field is being clicked.
		double xPosition, yPosition;
		glfwGetCursorPos(window, &xPosition, &yPosition);
		bool isWidthOrHeightLarger = windowWidth >= windowHeight;
		double shiftPosition = (isWidthOrHeightLarger ? windowWidth - windowHeight : windowHeight - windowWidth) / 2.f;
		/* Position shifting is useful when window aspect ratio isn't square.
		 * Next long line determines which row and column is being clicked by dividing X and Y position of the cursor on a width and height of the window.
		 * If you then divide each of this values by calculated cell size (which depends on field size), you can get exact clicked row and column. */
		unsigned int clickedRow = floor((yPosition - (isWidthOrHeightLarger ? 0 : shiftPosition)) / (isWidthOrHeightLarger ? windowHeight : windowWidth) / (cellSize / 2)), clickedColumn = floor((xPosition - (isWidthOrHeightLarger ? shiftPosition : 0)) / (isWidthOrHeightLarger ? windowHeight : windowWidth) / (cellSize / 2));
		// Check if one of the possible move directions from last occupied cell is on a clicked row or column and try to move in that direction.
		moveDirection direction = getMoveDirectionByTarget(activePlayer, clickedRow, clickedColumn);
		moveMake(activePlayer, direction);
	}
}