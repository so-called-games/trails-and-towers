#include "logic.h"
const int towerDistance = 1;
unsigned short field[fieldSize][fieldSize];
unsigned short lastCell[2][2] = { {0, 0}, {fieldSize - 1, fieldSize - 1} };
unsigned short lastBoost[2] = { 0, 0 };
bool activePlayer = PLAYER_FIRST;

void fieldInit()
{
	for (int r = 0; r < fieldSize; r++)
	{
		for (int c = 0; c < fieldSize; c++)
		{
			if (r == 0 && c == 0)
				field[r][c] = 1;
			else if (r == fieldSize - 1 && c == fieldSize - 1)
				field[r][c] = 2;
			else if (r == fieldSize / 2 && c == fieldSize / 2)
				field[r][c] = 3;
			else
				field[r][c] = 0;
		}
	}
}

bool movePossible(bool player, moveDirection direction)
{
	if (direction == moveDirection::up)
	{
		if (lastCell[player][0] > 0)
			if (field[lastCell[player][0] - 1][lastCell[player][1]] == 0)
				return true;
	}
	else if (direction == moveDirection::down)
	{
		if (lastCell[player][0] < fieldSize - 1)
			if (field[lastCell[player][0] + 1][lastCell[player][1]] == 0)
				return true;
	}
	else if (direction == moveDirection::left)
	{
		if (lastCell[player][1] > 0)
			if (field[lastCell[player][0]][lastCell[player][1] - 1] == 0)
				return true;
	}
	else if (direction == moveDirection::right)
	{
		if (lastCell[player][1] < fieldSize - 1)
			if (field[lastCell[player][0]][lastCell[player][1] + 1] == 0)
				return true;
	}
	return false;
}

void moveMake(moveDirection direction)
{
	if (movePossible(activePlayer, direction))
	{
		if (direction == moveDirection::up)
		{
			field[lastCell[activePlayer][0] - 1][lastCell[activePlayer][1]] = activePlayer + 1;
			lastCell[activePlayer][0]--;
		}
		else if (direction == moveDirection::down)
		{
			field[lastCell[activePlayer][0] + 1][lastCell[activePlayer][1]] = activePlayer + 1;
			lastCell[activePlayer][0]++;
		}
		else if (direction == moveDirection::left)
		{
			field[lastCell[activePlayer][0]][lastCell[activePlayer][1] - 1] = activePlayer + 1;
			lastCell[activePlayer][1]--;
		}
		else if (direction == moveDirection::right)
		{
			field[lastCell[activePlayer][0]][lastCell[activePlayer][1] + 1] = activePlayer + 1;
			lastCell[activePlayer][1]++;
		}
		activePlayer = !activePlayer;
	}
}
