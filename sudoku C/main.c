#include <stdio.h>
#include <time.h>
#include <windows.h>


#include "Board.h"
#include "Board Algorithms.h"
#include "Input Processing.h"


int main()
{
	
	int seed = GetInt("Enter a seed for the Sudoku Board: ");
	int numClues = GetInt("Enter the number of clues for the Sudoku Board: ");
	
	Board board;

	ResetBoard(&board); //fill board with 0s

	FillBoard(seed, &board); //populate board with valid numbers

	ItNumRemove(numClues, &board); //remove numbers leaving an amount of clues, making sure it's solvable

	printf("\n\n Completed Sudoku Board: \n\n");

	PrintBoard(&board);

	return 0;

}