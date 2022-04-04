#include "logic.h"
#include "window.h"
#include "graphics.h"
#include <algorithm>
#include <string>
unsigned int fieldSize;
unsigned int towersCount;
unsigned int towersDistance;
vector<vector<unsigned short>> field;
unsigned int endCell;
unsigned short lastCell[2][2];
moveDirection lastDirection[2];
unsigned short lastBoost[2];
unsigned int towersTaken[2];
bool activePlayer;
unsigned int movesCount;
bool winState;

void fieldInit()
{
	winState = false;
	showLastCell = true;
	showPossibleMoves = SHOW_POSSIBLE_MOVES;
	fieldSize = FIELD_SIZE;
	towersCount = TOWERS_COUNT;
	towersDistance = TOWERS_DISTANCE;
	windowSetTitle(WINDOW_TITLE_REGULAR);

	if (fieldSize < 2)
		fieldSize = 2;
	field.clear();
	field.resize(fieldSize, vector<unsigned short>(fieldSize, 0));
	endCell = fieldSize - 1;
	lastCell[0][0] = 0;
	lastCell[0][1] = 0;
	lastCell[1][0] = endCell;
	lastCell[1][1] = endCell;
	lastDirection[0] = moveDirection::left;
	lastDirection[1] = moveDirection::right;
	lastBoost[0] = 0;
	lastBoost[1] = 0;
	towersTaken[0] = 0;
	towersTaken[1] = 0;
	activePlayer = GOES_FIRST;
	movesCount = 0;
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
	int towerAttractor = (isFieldEven ? towerCenter : (towersCount % 2 == 0 ? ceil((float)towersDistance / 2) - 1 : 0));

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
	field[0][0] = 1;
	field[endCell][endCell] = 2;
}

moveDirection getMoveDirectionByTarget(bool player, unsigned int requestedRow, unsigned int requestedColumn)
{
	if (lastCell[player][0] == requestedRow || lastCell[player][1] == requestedColumn)
	{
		moveDirection direction = moveDirection::none;

		if (lastCell[player][0] != requestedRow)
		{
			if (requestedRow < lastCell[player][0])
				direction = moveDirection::up;
			else if (requestedRow > lastCell[player][0])
				direction = moveDirection::down;
		}
		else if (lastCell[player][1] != requestedColumn)
		{
			if (requestedColumn < lastCell[player][1])
				direction = moveDirection::left;
			else if (requestedColumn > lastCell[player][1])
				direction = moveDirection::right;
		}
		return direction;
	}
	return moveDirection::none;
}

bool stepPossible(bool player, moveDirection direction)
{
	if (direction == moveDirection::none)
		return false;
	int requestedRow, requestedColumn;

	if (direction == moveDirection::up)
	{
		requestedRow = lastCell[player][0] - (direction == lastDirection[player] ? lastBoost[player] + 1 : 0) - 1;
		requestedColumn = lastCell[player][1];

		if (requestedRow >= 0)
		{
			if (field[requestedRow][requestedColumn] == 0 || (direction == lastDirection[player] && field[requestedRow][requestedColumn] == 3))
				return true;
		}
		else if (field[0][requestedColumn] == 0)
			return true;
	}
	else if (direction == moveDirection::down)
	{
		requestedRow = lastCell[player][0] + (direction == lastDirection[player] ? lastBoost[player] + 1 : 0) + 1;
		requestedColumn = lastCell[player][1];

		if (requestedRow < fieldSize)
		{
			if (field[requestedRow][requestedColumn] == 0 || (direction == lastDirection[player] && field[requestedRow][requestedColumn] == 3))
				return true;
		}
		else if (field[endCell][requestedColumn] == 0)
			return true;
	}
	else if (direction == moveDirection::left)
	{
		requestedRow = lastCell[player][0];
		requestedColumn = lastCell[player][1] - (direction == lastDirection[player] ? lastBoost[player] + 1 : 0) - 1;

		if (requestedColumn >= 0)
		{
			if (field[requestedRow][requestedColumn] == 0 || (direction == lastDirection[player] && field[requestedRow][requestedColumn] == 3))
				return true;
		}
		else if (field[requestedRow][0] == 0)
			return true;
	}
	else if (direction == moveDirection::right)
	{
		requestedRow = lastCell[player][0];
		requestedColumn = lastCell[player][1] + (direction == lastDirection[player] ? lastBoost[player] + 1 : 0) + 1;
		
		if (requestedColumn < fieldSize)
		{
			if (field[requestedRow][requestedColumn] == 0 || (direction == lastDirection[player] && field[requestedRow][requestedColumn] == 3))
				return true;
		}
		else if (field[requestedRow][endCell] == 0)
			return true;
	}
	return false;
}

bool stepMake(bool player, moveDirection direction)
{
	if (stepPossible(player, direction))
	{
		if (direction == lastDirection[player])
			lastBoost[player]++;
		else
			lastBoost[player] = 0;

		int row, column;

		if (direction == moveDirection::up)
		{
			row = lastCell[player][0] - lastBoost[player] - 1;
			column = lastCell[player][1];
		}
		else if (direction == moveDirection::down)
		{
			row = lastCell[player][0] + lastBoost[player] + 1;
			column = lastCell[player][1];
		}
		else if (direction == moveDirection::left)
		{
			row = lastCell[player][0];
			column = lastCell[player][1] - lastBoost[player] - 1;
		}
		else if (direction == moveDirection::right)
		{
			row = lastCell[player][0];
			column = lastCell[player][1] + lastBoost[player] + 1;
		}

		if (row < 0)
			row = 0;
		else if (row > endCell)
			row = endCell;

		if (column < 0)
			column = 0;
		else if (column > endCell)
			column = endCell;

		if (direction == lastDirection[player])
		{
			if (lastBoost[player] > 0)
			{
				bool rowOrColumn = direction == moveDirection::up || direction == moveDirection::down;
				int first = (rowOrColumn ? lastCell[player][0] + (direction == moveDirection::down ? 1 : -1) : lastCell[player][1] + (direction == moveDirection::right ? 1 : -1)), last = (rowOrColumn ? row : column);

				for (int i = first; first <= last ? i < last : i > last; first <= last ? i++ : i--)
					if (field[rowOrColumn ? i : row][rowOrColumn ? column : i] == 0)
						field[rowOrColumn ? i : row][rowOrColumn ? column : i] = player + 1;
			}
		}

		if (field[row][column] == 3)
			towersTaken[player]++;
		field[row][column] = player + 1;
		lastCell[player][0] = row;
		lastCell[player][1] = column;
		lastDirection[player] = direction;
		return true;
	}
	else
		return false;
}

void moveMake(bool player, moveDirection direction)
{
	if (stepMake(player, direction))
	{
		movesCount++;

		if (checkForWinOrLose(player))
		{
			draw();
			return;
		}
		activePlayer = !player;
		draw();
	}
}

bool checkForWinOrLose(bool player)
{
	bool forTowers = towersTaken[player] >= ceil((float)towersCount / 2);
	bool forDeadEnds = !(stepPossible(player, moveDirection::up) || stepPossible(player, moveDirection::down) || stepPossible(player, moveDirection::left) || stepPossible(player, moveDirection::right));
	bool win = forTowers, lose = forDeadEnds;

	if (win || lose)
	{
		winState = true;
		string title = (player ? !(win || !lose) : (win || !lose)) ? WINDOW_TITLE_FIRST_WIN : WINDOW_TITLE_SECOND_WIN;
		title.append(" in ");
		title.append(to_string(movesCount / 2 + (!player && win ? 1 : 0)));
		title.append(" moves!");
		windowSetTitle(title.c_str());
		showLastCell = false;
		showPossibleMoves = false;
		return true;
	}
	else
		return false;
}
