#pragma comment (lib, "glu32.lib")
#include "graphics.h"
#include "window.h"
#include <gl/glu.h>
#include <GLFW/glfw3.h>
float cellSize;
float cellThickness;
float cellInnerSize;
const bool mindThicknessAdapt = true;
bool showLastCell = true;
bool showPossibleMoves = SHOW_POSSIBLE_MOVES;

void drawInit()
{
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	cellResize((float)screenHeight / (windowWidth <= windowHeight ? windowWidth : windowHeight));
	glfwWindowHint(GLFW_SAMPLES, 8);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.f - cellThickness, 1.f + cellThickness, -1.f - cellThickness, 1.f + cellThickness);
	glClearColor(COLOR_FIELD_BACKGROUND, 1.f);
	draw();
}

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
	glVertex2f(-1.f - cellThickness, 1.f + cellThickness);
	glVertex2f(1.f + cellThickness, 1.f + cellThickness);
	glVertex2f(1.f + cellThickness, -1.f - cellThickness);
	glVertex2f(-1.f - cellThickness, -1.f - cellThickness);

	for (int r = 0; r < fieldSize; r++)
		for (int c = 0; c < fieldSize; c++)
		{
			if (field[r][c] == 1)
				glColor3f(COLOR_PLAYER_FIRST);
			else if (field[r][c] == 2)
				glColor3f(COLOR_PLAYER_SECOND);
			else if (field[r][c] == 3)
				glColor3f(COLOR_TOWER);
			else
				glColor3f(COLOR_EMPTY_CELL);
			drawCell(r, c);
		}

	if (showLastCell)
	{
		if (!activePlayer)
			glColor3f(COLOR_FIRST_LAST_CELL);
		else
			glColor3f(COLOR_SECOND_LAST_CELL);
		drawCell(lastCell[activePlayer][0], lastCell[activePlayer][1]);
	}

	if (showPossibleMoves)
	{
		glColor3f(COLOR_POSSIBLE_MOVE);
		drawPossibleMoves(moveDirection::up);
		drawPossibleMoves(moveDirection::down);
		drawPossibleMoves(moveDirection::left);
		drawPossibleMoves(moveDirection::right);
	}
	glEnd();
}

void drawCell(int row, int column)
{
	if (flipRows)
		row = fieldSize - row - 1;

	if (flipColumns)
		column = fieldSize - column - 1;
	glVertex2f(-1.f + column * cellSize + cellThickness, 1.f - row * cellSize - cellThickness);
	glVertex2f(-1.f + column * cellSize + cellInnerSize, 1.f - row * cellSize - cellThickness);
	glVertex2f(-1.f + column * cellSize + cellInnerSize, 1.f - row * cellSize - cellInnerSize);
	glVertex2f(-1.f + column * cellSize + cellThickness, 1.f - row * cellSize - cellInnerSize);
}

void drawPossibleMoves(moveDirection direction)
{
	if (stepPossible(activePlayer, direction))
	{
		int rowDirection = 0, columnDirection = 0;

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

			if (row < 0 || row > endCell || column < 0 || column > endCell)
				break;

			if (field[row][column] != 1 && field[row][column] != 2 && i < lastBoost[activePlayer] + 2)
				drawCell(row, column);
			i++;
		} while (i <= lastBoost[activePlayer] + 2 && lastDirection[activePlayer] == direction);
	}
}
