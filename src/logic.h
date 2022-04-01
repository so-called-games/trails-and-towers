#pragma once
#define PLAYER_FIRST false
#define PLAYER_SECOND true
enum class moveDirection
{
	up, down, left, right
};
const int fieldSize = 11;
extern unsigned short field[fieldSize][fieldSize];
extern unsigned short lastCell[2][2];
extern bool activePlayer;
void fieldInit();
bool movePossible(bool player, moveDirection direction);
void moveMake(moveDirection direction);
