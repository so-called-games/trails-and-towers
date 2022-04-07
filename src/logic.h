#pragma once
#include "version.h"
#include <vector>
// Define main parameters of the game.
#define FIELD_SIZE 11
#define TOWERS_COUNT 3
#define TOWERS_DISTANCE 1
// Which player goes first?
#define GOES_FIRST PLAYER_ONE
#define PLAYER_ONE false
#define PLAYER_TWO true
using namespace std;
// Define possible move directions.
enum class moveDirection
{
	none, up, down, left, right
};
extern unsigned int fieldSize;
/* There are some variables, which are responsible for main logic of the game.
 * Variable "field" store a state of each cell on the field vector in number values.
 * 0 is for empty cell, 1 is for cell occupied by player one, 2 is for cell ocuppied by player two and 3 is for tower.
 * Variable "endCell" simply store sizes of the field minus one for loop operators.
 * Variable "lastCell" store a row and a column of the last occupied cell for each player.
 * Variable "lastBoost" store recent boost for each player.
 * Variable "towersTaken" store how many towers each player has taken.
 * Variable "activePlayer" store, whose turn is now.
 * Variable "movesCount" store, how many moves has been taken in general.
 * Lastly, variable "winState" store if one of the players won or not. It's used for reset the game later. */
extern vector<vector<unsigned short>> field;
extern unsigned int endCell;
extern unsigned short lastCell[2][2];
extern moveDirection lastDirection[2];
extern unsigned short lastBoost[2];
extern bool activePlayer;
extern bool winState;
void fieldInit();
moveDirection getMoveDirectionByTarget(bool player, unsigned int requestedRow, unsigned int requestedColumn);
bool stepPossible(bool player, moveDirection direction);
bool stepMake(bool player, moveDirection direction);
void moveMake(bool player, moveDirection direction);
bool checkForWinOrLose(bool player);