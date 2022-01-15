#include <stdio.h>
#include <time.h>
#include <windows.h>


#include "Board.h"
#include "Board Algorithms.h"


int main()
{
	
	Board board;

	ResetBoard(&board);

	FillBoard(time(NULL), &board);

	ItNumRemove(40, &board);

	printf("\n\n Completed Sudoku Board: \n\n");

	PrintBoard(&board);

	return 0;

}