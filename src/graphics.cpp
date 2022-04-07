// This file includes methods that draw game's graphics.
#include "graphics.h"
#include "window.h"
#include <GL/glu.h>
#include <GLFW/glfw3.h>
float cellSize;
float cellThickness;
float cellInnerSize;
// This sets if grid thickness needed to be the same when window is resized.
const bool mindThicknessAdapt = true;
bool showLastCell = true;
bool showPossibleMoves = SHOW_POSSIBLE_MOVES;

void drawInit()
{
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	cellResize((float)screenHeight / (windowWidth <= windowHeight ? windowWidth : windowHeight));
	// Set MSAA value.
	glfwWindowHint(GLFW_SAMPLES, 8);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// This sets projection little above the field to show grid borders which located next to the field borders.
	gluOrtho2D(-1.f - cellThickness, 1.f + cellThickness, -1.f - cellThickness, 1.f + cellThickness);
	// Set color outside the field.
	glClearColor(COLOR_FIELD_BACKGROUND, 1.f);
	draw();
}

// This method updates size of the cells and grid if it is needed, for example when window was resized.
void cellResize(float thicknessMultiplier)
{
	cellSize = 2.f / fieldSize;
	cellThickness = cellSize * GRID_THICKNESS * (mindThicknessAdapt ? thicknessMultiplier : 2.5f);
	cellInnerSize = cellSize - 2 * cellThickness;
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawField();
	glfwSwapBuffers(window);
}

void drawField()
{
	glBegin(GL_QUADS);
	glColor3f(COLOR_FIELD_GRID);
	/* Draw field backing.
	 * You can notice that the grid isn't actually the "grid", it's a square which drawn below the field,
	 * and cells itself appear to be a little smaller to make effect like there is a grid. */
	glVertex2f(-1.f - cellThickness, 1.f + cellThickness);
	glVertex2f(1.f + cellThickness, 1.f + cellThickness);
	glVertex2f(1.f + cellThickness, -1.f - cellThickness);
	glVertex2f(-1.f - cellThickness, -1.f - cellThickness);

	// Draw every cell on the field.
	for (int r = 0; r < fieldSize; r++)
		for (int c = 0; c < fieldSize; c++)
		{
			if (field[r][c] == 1)
				glColor3f(COLOR_PLAYER_ONE);
			else if (field[r][c] == 2)
				glColor3f(COLOR_PLAYER_TWO);
			else if (field[r][c] == 3)
				glColor3f(COLOR_TOWER);
			else
				glColor3f(COLOR_EMPTY_CELL);
			drawCell(r, c);
		}

	// Draw additional cell of different color on a last occupied cell for each player.
	if (showLastCell)
	{
		if (!activePlayer)
			glColor3f(COLOR_PLAYER_ONE_LAST_CELL);
		else
			glColor3f(COLOR_PLAYER_TWO_LAST_CELL);
		drawCell(lastCell[activePlayer][0], lastCell[activePlayer][1]);
	}

	if (showPossibleMoves)
	{
		glColor3f(COLOR_POSSIBLE_MOVE);
		// Try to show possible moves in all directions.
		drawPossibleMoves(moveDirection::up);
		drawPossibleMoves(moveDirection::down);
		drawPossibleMoves(moveDirection::left);
		drawPossibleMoves(moveDirection::right);
	}
	glEnd();
}

void drawCell(int row, int column)
{
	// Invert rows or columns if field flip options are on.
	if (flipRows)
		row = fieldSize - row - 1;

	if (flipColumns)
		column = fieldSize - column - 1;
	// Draw square.
	glVertex2f(-1.f + column * cellSize + cellThickness, 1.f - row * cellSize - cellThickness);
	glVertex2f(-1.f + column * cellSize + cellInnerSize, 1.f - row * cellSize - cellThickness);
	glVertex2f(-1.f + column * cellSize + cellInnerSize, 1.f - row * cellSize - cellInnerSize);
	glVertex2f(-1.f + column * cellSize + cellThickness, 1.f - row * cellSize - cellInnerSize);
}

void drawPossibleMoves(moveDirection direction)
{
	// We will draw a green cells only if there is a reason to.
	if (stepPossible(activePlayer, direction))
	{
		int rowDirection = 0, columnDirection = 0;

		// It is easier to define some add and subtract values and then assign row and column ones than assign it for every direction.
		if (direction == moveDirection::up)
		{
			rowDirection = -1;
			columnDirection = 0;
		}
		else if (direction == moveDirection::down)
		{
			rowDirection = 1;
			columnDirection = 0;
		}
		else if (direction == moveDirection::left)
		{
			rowDirection = 0;
			columnDirection = -1;
		}
		else if (direction == moveDirection::right)
		{
			rowDirection = 0;
			columnDirection = 1;
		}
		int i = 1, row, column;

		do
		{
			row = lastCell[activePlayer][0] + i * rowDirection;
			column = lastCell[activePlayer][1] + i * columnDirection;

			// Cells that are beyond the borders (when boost can throw player over the field) doesn't meant to be drawn.
			if (row < 0 || row > endCell || column < 0 || column > endCell)
				break;

			// Cell will be green on empty cells and on tower, if it is a target.
			if (field[row][column] == 0 || field[row][column] == 3 && i == lastBoost[activePlayer] + 2)
				drawCell(row, column);
			i++;
		} while (i <= lastBoost[activePlayer] + 2 && lastDirection[activePlayer] == direction); // Draw one green cells or several depending on player's boost.
	}
}