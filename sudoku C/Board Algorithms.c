#include "Board Algorithms.h"



void FillBoard(int seed, Board* board)
{

	srand(seed);

	//counter to check how many times we backtracked to previous cell
	int tries = 0;

	//index of cell we backtrack from
	int bRow = 0;
	int bCol = 0;


	//iterate over rows and columns in the board
	for (int row = 0; row < 9; row++)
	{

		for (int col = 0; col < 9; col++)
		{

			//arbitrary number between 0 and 8 to be modified later
			int num = rand() % 9;


			//cell at the current index
			int* cell = GetIndex(row, col, board);


			//if the cell already has a number because of backtracking, set the arbitrary number to its value
			if (*cell != 0)
			{

				num = *cell;

			}


			//bool to check if there is a valid number for the cell - if false we backtrack to last cell
			bool cellValid = false;


			//iterate over possible values for a cell
			for (int i = 0; i < 9; i++)
			{

				//modified number for each iteration, doing this allows it to increment by 1 and wrap around to 1 after reaching 9
				int modNum = ((num + i) % 9) + 1;

				*cell = modNum;


				//display numbers changing in realtime
				printf("\033[H");

				printf("Filling Board...\n");

				PrintBoard(board);


				//set current cell to 0
				*cell = 0;


				//check if cell is valid using modified number
				if (CellValid(row, col, modNum, board))
				{

					cellValid = true;

					//set current cell to the current modified number and continue to next cell
					*cell = modNum;
					break;

				}

			}



			//backtrack if no valid number for current cell
			if (!cellValid)
			{

				tries++;


				//keep backtracking if there continues to be no valid state for a cell
				for (int i = 0; i < floor(tries / 4) + 2; i++)
				{

					//zero out the cells between the furthest cell we visited, and the cell we backtrack to
					cell = GetIndex(row, col, board);
					*cell = 0;

					//make sure we backtrack to valid cell index
					if (col != 0)
					{
						col -= 1;
					}
					else
					{
						row--;
						col = 8;
					}

				}

			}
			else
			{

				//check to see if this is the furthest cell we visited
				if (row > bRow || (col > bCol && bRow == row))
				{
					bRow = row;
					bCol = col;
					tries = 0;
				}

			}

		}

	}

}


bool BoardSolvable(Board* board)
{

	Board* boardCopy = malloc(sizeof(Board));

	ResetBoard(boardCopy);

	memcpy(boardCopy, board, sizeof(Board));

	printf("\033[H\033[J");

	for (int row = 0; row < RC_SIZE; row++)
	{

		for (int col = 0; col < RC_SIZE; /*increment col after checking if current cell is valid towards end of loop*/)
		{
			//continue if cell contains clue
			if (*GetIndex(row, col, board) != 0)
			{
				col++;
				continue;
			}


			bool cellValid = false; //variable to check if cell has a valid value

			int* cell = GetIndex(row, col, boardCopy); //current cell to be checked for valid state


			//check for possible values in cell
			for (int i = *cell + 1; i <= 9; i += 1)
			{

				printf("\033[H"); //reset console cursor position to top left

				printf("Checking for Possible Solutions... \n");

				PrintBoard(boardCopy); //write copy of board that checks if board is solvable

				printf("\nOriginal Board: \n");

				PrintBoard(board); //print original board that we remove numbers from

				if (CellValid(row, col, i, boardCopy))
				{
					*cell = i;
					cellValid = true;
					break;
				}

			}


			//check if cell has no valid value
			if (!cellValid)
			{
				
				//reset value of cell if no valid value
				*cell = 0;


				//backtrack to previous cell that isn't a clue if there is one
				for (int i = 0; i < RC_SIZE * RC_SIZE + 1; i++)
				{

					col--;

					//go to previous row if in first col
					if (col < 0)
					{
						col = 8;
						row--;
					}

					//if first cell not valid then board has no valid solutions
					if (row < 0)
					{
						return false;
					}

					if (*GetIndex(row, col, board) == 0)
					{

						break;

					}

				}

			}
			else
			{
				col++; //increment column if current cell is valid
			}

		}

	}


	return true;

}


//randomly remove numbers from board, leaving a number of clues, while making sure it's still solvable
//theoretical minimum clues for any Sudoku board is 17
int ItNumRemove(int numClues, Board* board)
{

	srand(time(NULL));

	
	//it is impossible to solve a sudoku board with less than 17 clues
	if (numClues < 17)
	{
		printf("Number of clues cannot be less than 17 due to the theoretical minimum for all Sudoku boards.\n");
		return -1;
	}


	for (int i = 81; i > numClues; i--)
	{

		//maximum amount of tries to remove cells
		int tries = 5;

		

		//try to remove cells from board up to an amount
		while (tries > 0)
		{

			int* removeCell; //cell to be removed


			//find a cell that has not been removed yet
			do
			{

				int row = rand() % 9;
				int col = rand() % 9;

				removeCell = GetIndex(row, col, board);

			} while (*removeCell == 0);


			int cellRecall = *removeCell; //value of the cell we remove in case the board is not solvable

			*removeCell = 0;//remove the cell


			//check if board can be solved
			if (BoardSolvable(board) == true)
			{
				break;
			}
			else //if the board cannot be solved, reset the cell with a solvable value
			{
				*removeCell = cellRecall;
				tries--;
			}

		}

		if (tries == 0)
		{
			break;
		}

	}


	return 0;

}