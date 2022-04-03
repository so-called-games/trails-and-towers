#pragma once
#pragma comment (lib, "glu32.lib")
#include "window.h"
#include "logic.h"
#include <gl/glu.h>
#include <GLFW/glfw3.h>
extern const float cellThickness;
extern bool flipRows;
extern bool flipColumns;
extern bool showPossibles;
void drawInit();
void draw();
void drawField();
void drawCell(int row, int column);
void drawPossibles(moveDirection direction);
