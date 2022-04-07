// This file includes methods that operate with logic of the game.
#include "logic.h"
#include "debug.h"
#include "window.h"
#include "graphics.h"
#include <cmath>
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
	// Set initial parameters for the game.
	winState = false;
	showLastCell = true;
	showPossibleMoves = SHOW_POSSIBLE_MOVES;
	fieldSize = FIELD_SIZE;
	towersCount = TOWERS_COUNT;
	towersDistance = TOWERS_DISTANCE;
	windowSetTitle(WINDOW_TITLE_REGULAR);

	// It's not possible to play on a field which size is less than 3, so we will set it to 3.
	if (fieldSize < 3)
	{
		warning(WARNING_FIELD_SIZE);
		fieldSize = 3;
	}
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

	// Towers can be placed differently depending on parity of field size and towers count.
	if (isFieldEven)
	{
		// However, there is no way to place odd amount of towers symmetrically on the field of even size, so count of the towers must be increased by one to be even.
		if (towersCount % 2 != 0)
		{
			warning(WARNING_TOWERS_COUNT);
			towersCount++;
		}
	}
	else
	{
		if (towersCount % 2 == 0)
			towerShift = towersDistance;
	}
	// This was a pretty hard part so I don't remember what exactly everything does here (it places the towers).
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
	// Cell requested by player must be on a one row or column with last occupied cell.
	if (lastCell[player][0] == requestedRow || lastCell[player][1] == requestedColumn)
	{
		moveDirection direction = moveDirection::none;

		// Is requsted cell higher or lower than the last cell?
		if (lastCell[player][0] != requestedRow)
		{
			if (requestedRow < lastCell[player][0])
				direction = moveDirection::up;
			else if (requestedRow > lastCell[player][0])
				direction = moveDirection::down;
		}
		// Or more to the left or right than the last cell?
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
	// This condition is used for example when unreachable cell was clicked.
	if (direction == moveDirection::none)
		return false;
	int requestedRow, requestedColumn;

	// If requested cell is empty, or there is a tower that player can take, move is possible.
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
	// Player is taking a move only when it is possible.
	if (stepPossible(player, direction))
	{
		// If player move same direction as the last turn, his boost will increase. Otherwise it's gone.
		if (direction == lastDirection[player])
			lastBoost[player]++;
		else
			lastBoost[player] = 0;
		int row = 0, column = 0;

		// Which cell player moves to?
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

		// He can't get over the field.
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
				// Define origin and target cells.
				int first = (rowOrColumn ? lastCell[player][0] + (direction == moveDirection::down ? 1 : -1) : lastCell[player][1] + (direction == moveDirection::right ? 1 : -1)), last = (rowOrColumn ? row : column);

				// Occupy every free cell between origin and target ones.
				for (int i = first; first <= last ? i < last : i > last; first <= last ? i++ : i--)
					if (field[rowOrColumn ? i : row][rowOrColumn ? column : i] == 0)
						field[rowOrColumn ? i : row][rowOrColumn ? column : i] = player + 1;
			}
		}

		// If player hits target cell with boost and there is a tower, he takes it.
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
	// Try to make a move in chosen direction. If move is possible, check on active player for win or lose.
	if (stepMake(player, direction))
	{
		movesCount++;

		if (checkForWinOrLose(player))
		{
			draw();
			return;
		}
		// Turn is over.
		activePlayer = !player;
		draw();
	}
}

bool checkForWinOrLose(bool player)
{
	/* Setting up win and lose conditions.
	 * Player will win when more than a half towers are taken by him or when he stymied opponent in a dead end.
	 * Player will lose if he puts himself into a dead end. */
	bool forTowers = towersTaken[player] > towersCount / 2;
	bool forDeadEndOnOpponent = !(stepPossible(!player, moveDirection::up) || stepPossible(!player, moveDirection::down) || stepPossible(!player, moveDirection::left) || stepPossible(!player, moveDirection::right));
	bool forDeadEndOnMyself = !(stepPossible(player, moveDirection::up) || stepPossible(player, moveDirection::down) || stepPossible(player, moveDirection::left) || stepPossible(player, moveDirection::right));
	bool win = forTowers || forDeadEndOnOpponent, lose = forDeadEndOnMyself;

	if (win || lose)
	{
		winState = true;
		/* It is possible that win and lose conditions can be true at the same time, for example when player take tower and get stucked in dead end in same turn.
		 * To solve this problem, next statement represent material conditional operation, so player will win with win condition even if lose condition is true too.
		 * Ternary operator is needed to swap window win titles depending on which player's turn is now. */
		string title = (player ? !(win || !lose) : (win || !lose)) ? WINDOW_TITLE_FIRST_WIN : WINDOW_TITLE_SECOND_WIN;
		title.append(" in ");
		title.append(to_string(movesCount / 2 + ((!player != GOES_FIRST) && win ? 1 : 0)));
		title.append(" moves!");
		windowSetTitle(title.c_str());
		// Disable showing possible moves and last occupied cell until new game is started.
		showLastCell = false;
		showPossibleMoves = false;
		return true;
	}
	else
		return false;
}