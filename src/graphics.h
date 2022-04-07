#pragma once
#include "logic.h"
// Define field grid thickness in proportion to a cell size. Possible to be set to zero for hide the grid.
#define GRID_THICKNESS 1 / 100
// Define colors of graphic elements such as grid, towers, player bases, last occupied cells etc.
#define COLOR_FIELD_BACKGROUND 1.f, 1.f, 1.f
#define COLOR_FIELD_GRID 0.9f, 0.9f, 0.9f
#define COLOR_EMPTY_CELL 1.f, 1.f, 1.f
#define COLOR_PLAYER_ONE 0.f, 0.f, 1.f
#define COLOR_PLAYER_TWO 1.f, 0.f, 0.f
#define COLOR_TOWER 0.f, 0.f, 0.f
#define COLOR_PLAYER_ONE_LAST_CELL 0.f, 0.f, 0.5f
#define COLOR_PLAYER_TWO_LAST_CELL 0.5f, 0.f, 0.f
#define COLOR_POSSIBLE_MOVE 0.f, 1.f, 0.f
// Define if possible moves are to be shown.
#define SHOW_POSSIBLE_MOVES true
extern float cellSize;
extern float cellThickness;
// You can flip the field with this values. Notice that field data array will remain the same, just graphics and controls will be flipped.
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