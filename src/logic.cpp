#include "logic.h"
unsigned int fieldSize = 11;
unsigned int towersCount = 3;
unsigned int towersDistance = 1;
vector<vector<unsigned short>> field;
unsigned short lastCell[2][2];
moveDirection lastDirection[2];
unsigned short lastBoost[2];
unsigned int towersTaken[2];
bool activePlayer;
unsigned int movesCount;

void fieldInit()
{
	if (fieldSize < 2)
		fieldSize = 2;
	field.clear();
	field.resize(fieldSize, vector<unsigned short>(fieldSize, 0));
	lastCell[0][0] = 0;
	lastCell[0][1] = 0;
	lastCell[1][0] = fieldSize - 1;
	lastCell[1][1] = fieldSize - 1;
	lastDirection[0] = moveDirection::left;
	lastDirection[1] = moveDirection::right;
	lastBoost[0] = 0;
	lastBoost[1] = 0;
	towersTaken[0] = 0;
	towersTaken[1] = 0;
	activePlayer = PLAYER_FIRST;
	movesCount = 0;
	field[0][0] = 1;
	field[fieldSize - 1][fieldSize - 1] = 2;
	bool isFieldEven = fieldSize % 2 == 0;
	int towerCenter = fieldSize / 2, towerShift = 0;

	if (isFieldEven)
	{
		if (towersCount % 2 != 0)
			towersCount++;
	}
	else
	{
		if (towersCount % 2 == 0)
			towerShift = towersDistance;
	}
	int towerAttractor = (isFieldEven ? towersDistance / 2 : (towersCount % 2 == 0 ? ceil((float)towersDistance / 2) - 1 : 0));

	for (int t = (isFieldEven ? 1 : 0); t < ceil((float)towersCount / 2) + (isFieldEven ? 1 : 0); t++)
	{
		int row = towerCenter - towerShift - t * (towersDistance + 1) + towerAttractor;
		int column = towerCenter + towerShift + t * (towersDistance + 1) - towerAttractor - (isFieldEven ? 1 : 0);

		if (row >= 0 && row < fieldSize && column >= 0 && column < fieldSize)
			field[row][column] = 3;
		row = towerCenter + towerShift + t * (towersDistance + 1) - towerAttractor - (isFieldEven ? 1 : 0);
		column = towerCenter - towerShift - t * (towersDistance + 1) + towerAttractor;

		if (row >= 0 && row < fieldSize && column >= 0 && column < fieldSize)
			field[row][column] = 3;
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
