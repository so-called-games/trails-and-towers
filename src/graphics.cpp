#include "graphics.h"
const float cellSize = 2.f / fieldSize;
const float cellThickness = cellSize / 35.f;
const float cellInnerSize = cellSize - 2 * cellThickness;

void drawInit()
{
	glfwWindowHint(GLFW_SAMPLES, 8);
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
	glVertex2f(-1.f - 2 * cellThickness, 1.f + 2 * cellThickness);
	glVertex2f(1.f + cellThickness, 1.f + 2 * cellThickness);
	glVertex2f(1.f + cellThickness, -1.f - cellThickness);
	glVertex2f(-1.f - 2 * cellThickness, -1.f - cellThickness);

	for (int r = 0; r < fieldSize; r++)
		for (int c = 0; c < fieldSize; c++)
		{
			glColor3f(0.9f, 0.9f, 0.9f);
			glVertex2f(-1.f + c * cellSize, 1.f - r * cellSize);
			glVertex2f(-1.f + c * cellSize + cellSize, 1.f - r * cellSize);
			glVertex2f(-1.f + c * cellSize + cellSize, 1.f - r * cellSize - cellSize);
			glVertex2f(-1.f + c * cellSize, 1.f - r * cellSize - cellSize);

			if (field[r][c] == 1)
				glColor3f(0.f, 0.f, 1.f);
			else if (field[r][c] == 2)
				glColor3f(1.f, 0.f, 0.f);
			else if (field[r][c] == 3)
				glColor3f(0.f, 0.f, 0.f);
			else
				glColor3f(1.f, 1.f, 1.f);
			glVertex2f(-1.f + c * cellSize + cellThickness, 1.f - r * cellSize - cellThickness);
			glVertex2f(-1.f + c * cellSize + cellInnerSize, 1.f - r * cellSize - cellThickness);
			glVertex2f(-1.f + c * cellSize + cellInnerSize, 1.f - r * cellSize - cellInnerSize);
			glVertex2f(-1.f + c * cellSize + cellThickness, 1.f - r * cellSize - cellInnerSize);
		}
	glEnd();
}
