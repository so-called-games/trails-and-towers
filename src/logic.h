#pragma once
#include "version.h"
#include <vector>
#define FIELD_SIZE 11
#define TOWERS_COUNT 3
#define TOWERS_DISTANCE 1
#define GOES_FIRST FIRST_PLAYER
#define FIRST_PLAYER false
#define SECOND_PLAYER true
using namespace std;
enum class moveDirection
{
	none, up, down, left, right
};
extern unsigned int fieldSize;
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
