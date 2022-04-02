#pragma once
#define PLAYER_FIRST false
#define PLAYER_SECOND true
enum class moveDirection
{
	up, down, left, right
};
const int fieldSize = 11;
const int towersCount = 3;
const int towersDistance = 1;
extern unsigned short field[fieldSize][fieldSize];
extern unsigned short lastCell[2][2];
extern moveDirection lastDirection[2];
extern unsigned short lastBoost[2];
extern bool activePlayer;
extern unsigned int movesCount;
void fieldInit();
bool stepPossible(bool player, moveDirection direction);
bool stepMake(bool player, moveDirection direction, bool boost = false);
bool moveMake(bool player, moveDirection direction);
