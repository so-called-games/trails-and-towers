#pragma once
#include "logic.h"
#define GRID_THICKNESS 1 / 100
#define COLOR_FIELD_BACKGROUND 1.f, 1.f, 1.f
#define COLOR_FIELD_GRID 0.9f, 0.9f, 0.9f
#define COLOR_EMPTY_CELL 1.f, 1.f, 1.f
#define COLOR_PLAYER_FIRST 0.f, 0.f, 1.f
#define COLOR_PLAYER_SECOND 1.f, 0.f, 0.f
#define COLOR_TOWER 0.f, 0.f, 0.f
#define COLOR_FIRST_LAST_CELL 0.f, 0.f, 0.5f
#define COLOR_SECOND_LAST_CELL 0.5f, 0.f, 0.f
#define COLOR_POSSIBLE_MOVE 0.f, 1.f, 0.f
#define SHOW_POSSIBLE_MOVES true
extern float cellSize;
extern float cellThickness;
const bool flipRows = false;
const bool flipColumns = false;
extern bool showLastCell;
extern bool showPossibleMoves;
void drawInit();
void cellResize(float thicknessMultiplier);
void draw();
void drawField();
void drawCell(int row, int column);
void drawPossibleMoves(moveDirection direction);
