#pragma once
#include <vector>
#include <algorithm>
#define PLAYER_FIRST false
#define PLAYER_SECOND true
using namespace std;
enum class moveDirection
{
	up, down, left, right
};
extern unsigned int fieldSize;
extern vector<vector<unsigned short>> field;
extern unsigned short lastCell[2][2];
extern moveDirection lastDirection[2];
extern unsigned short lastBoost[2];
extern bool activePlayer;
extern unsigned int movesCount;
void fieldInit();
bool stepPossible(bool player, moveDirection direction);
bool stepMake(bool player, moveDirection direction, bool boost = false);
bool moveMake(bool player, moveDirection direction);
