#pragma once
#include "window.h"
#include "logic.h"
extern const float cellThickness;
void drawInit();
void draw();
void drawField();
void drawCell(int row, int column);
void drawPossibles(moveDirection direction);
