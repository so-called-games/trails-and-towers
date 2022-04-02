#include "logic.h"
const int towerDistance = 1;
unsigned short field[fieldSize][fieldSize];
unsigned short lastCell[2][2] = { {0, 0}, {fieldSize - 1, fieldSize - 1} };
moveDirection lastDirection[2] = { moveDirection::left,  moveDirection::right };
unsigned short lastBoost[2] = { 0, 0 };
bool activePlayer = PLAYER_FIRST;
unsigned int movesCount = 0;

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

bool stepPossible(bool player, moveDirection direction)
{
	if (direction == moveDirection::up)
	{
		if (lastCell[player][0] > 0)
			if (field[lastCell[player][0] - 1][lastCell[player][1]] == 0 || lastBoost[player] > 0)
				return true;
	}
	else if (direction == moveDirection::down)
	{
		if (lastCell[player][0] < fieldSize - 1)
			if (field[lastCell[player][0] + 1][lastCell[player][1]] == 0 || lastBoost[player] > 0)
				return true;
	}
	else if (direction == moveDirection::left)
	{
		if (lastCell[player][1] > 0)
			if (field[lastCell[player][0]][lastCell[player][1] - 1] == 0 || lastBoost[player] > 0)
				return true;
	}
	else if (direction == moveDirection::right)
	{
		if (lastCell[player][1] < fieldSize - 1)
			if (field[lastCell[player][0]][lastCell[player][1] + 1] == 0 || lastBoost[player] > 0)
				return true;
	}
	return false;
}

bool stepMake(bool player, moveDirection direction, bool boost)
{
	if (stepPossible(player, direction))
	{
		if (direction == moveDirection::up)
		{
			if (field[lastCell[player][0] - 1][lastCell[player][1]] == 0)
				field[lastCell[player][0] - 1][lastCell[player][1]] = player + 1;
			lastCell[player][0]--;
		}
		else if (direction == moveDirection::down)
		{
			if (field[lastCell[player][0] + 1][lastCell[player][1]] == 0)
				field[lastCell[player][0] + 1][lastCell[player][1]] = player + 1;
			lastCell[player][0]++;
		}
		else if (direction == moveDirection::left)
		{
			if (field[lastCell[player][0]][lastCell[player][1] - 1] == 0)
				field[lastCell[player][0]][lastCell[player][1] - 1] = player + 1;
			lastCell[player][1]--;
		}
		else if (direction == moveDirection::right)
		{
			if (field[lastCell[player][0]][lastCell[player][1] + 1] == 0)
				field[lastCell[player][0]][lastCell[player][1] + 1] = player + 1;
			lastCell[player][1]++;
		}

		if (direction == lastDirection[player])
		{
			if (!boost)
			{
				lastBoost[player]++;

				for (int i = 0; i < lastBoost[player]; i++)
					if (!stepMake(player, direction, true))
						lastBoost[player] = 0;
			}
		}
		else
			lastBoost[player] = 0;
		lastDirection[player] = direction;
		return true;
	}
	else
		return false;
}

bool moveMake(bool player, moveDirection direction)
{
	if (stepMake(activePlayer, direction))
	{
		activePlayer = !activePlayer;
		movesCount++;
		return true;
	}
	return false;
}
