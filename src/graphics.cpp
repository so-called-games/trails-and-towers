#include "graphics.h"
const float cellSize = 2.f / fieldSize;
const float cellThickness = cellSize / 35.f;
const float cellInnerSize = cellSize - 2 * cellThickness;
bool flipRows = false;
bool flipColumns = false;
bool showPossibles = true;

void drawInit()
{
	glfwWindowHint(GLFW_SAMPLES, 8);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.f - cellThickness, 1.f + cellThickness, -1.f - cellThickness, 1.f + cellThickness);
	glClearColor(1.f, 1.f, 1.f, 1.f);
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
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(-1.f - cellThickness, 1.f + cellThickness);
	glVertex2f(1.f + cellThickness, 1.f + cellThickness);
	glVertex2f(1.f + cellThickness, -1.f - cellThickness);
	glVertex2f(-1.f - cellThickness, -1.f - cellThickness);

	for (int r = 0; r < fieldSize; r++)
		for (int c = 0; c < fieldSize; c++)
		{
			if (field[r][c] == 1)
				glColor3f(0.f, 0.f, 1.f);
			else if (field[r][c] == 2)
				glColor3f(1.f, 0.f, 0.f);
			else if (field[r][c] == 3)
				glColor3f(0.f, 0.f, 0.f);
			else
				glColor3f(1.f, 1.f, 1.f);
			drawCell(r, c);
		}

	if (showPossibles)
	{
		glColor3f(0.f, 1.f, 0.f);
		drawPossibles(moveDirection::up);
		drawPossibles(moveDirection::down);
		drawPossibles(moveDirection::left);
		drawPossibles(moveDirection::right);
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

void drawPossibles(moveDirection direction)
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

			if (row < 0 || row > (fieldSize - 1) || column < 0 || column > (fieldSize - 1))
				break;

			if (field[row][column] != 1 && field[row][column] != 2)
				drawCell(row, column);
			i++;
		} while (i <= lastBoost[activePlayer] + 2 && lastDirection[activePlayer] == direction);
	}
}
