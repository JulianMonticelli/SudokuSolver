#include "Main.h"

const int NUM_TILES = 9 * 9;

int tiles[9][9];


int main(int argc, char** argv)
{
	// The sudoku board should be piped into the program, using 0's as empty spaces
	for (int i = 0; i < NUM_TILES; i++)
	{
		int currentNum;
		std::cin >> currentNum;
		tiles[i / 9][i % 9] = currentNum;
		if (currentNum < 0 || currentNum > 9)
		{
			std::cout << "Invalid number " << currentNum << "! Exiting program." << std::endl;
			exit(-1);
		}
	}

	// Assert valid sudoku puzzle?

	// Try to solve the sudoku puzzle
	bool solved = solveSudoku(0, 0);

	if (solved)
	{
		// Write to output
		for (int y = 0; y < 9; y++)
		{
			std::cout << std::endl;
			for (int x = 0; x < 9; x++)
			{
				std::cout << tiles[x][y] << " ";
			}
		}
	}
	else
	{
		std::cout << std::endl << "There is no solution to this sudoku puzzle :(" << std::endl;
	}
}



bool solveSudoku(int x, int y)
{
	// Determine next tile after this recursive case
	int nextX = x + 1;
	int nextY = y;
	if (nextX > 8) {
		nextY += 1;
		nextX = 0;
	}

	// Sudoku solved base case
	if (y == 9) {
		return true;
	}

	// If there is a number in the tile already,
	// let's continue recursing and return the result
	if (tiles[x][y] > 0) {
		return solveSudoku(nextX, nextY);
	}

	// Go through possible numbers and backtrack if there are none
	for (int i = 1; i <= 9; i++)
	{
		if (validNumberForTile(x, y, i))
		{
			tiles[x][y] = i;
			if (solveSudoku(nextX, nextY))
			{
				return true;
			}
			tiles[x][y] = 0;
		}
	}
	return false;
}

bool validNumberForTile(int x, int y, int n)
{
	// Confirm row does not already have the number
	// in consideration
	for (int xRow = 0; xRow < 9; xRow++)
	{
		if (tiles[xRow][y] == n)
		{
			return false;
		}
	}

	// Confirm column does not already have the number
	// in consideration
	for (int yCol = 0; yCol < 9; yCol++)
	{
		if (tiles[x][yCol] == n)
		{
			return false;
		}
	}

	// Confirm the block/region doesn't contain
	// the number in consideration
	int xCorner = x - (x % 3);
	int yCorner = y - (y % 3);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tiles[xCorner + i][yCorner + j] == n)
			{
				return false;
			}
		}
	}
	return true;
}