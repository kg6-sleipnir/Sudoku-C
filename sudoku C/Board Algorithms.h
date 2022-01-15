#ifndef BOARD_ALG
#define BOARD_ALG

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#include "Board.h"

//iterative algorithm for filling the board using a linked list
void FillBoard(int seed, Board* board);

//check if board is solvable
bool BoardSolvable(Board* board);

//randomly remove numbers from board, leaving a number of clues, while making sure it's still solvable
//theoretical minimum clues for any Sudoku board is 17
int ItNumRemove(int numClues, Board* board);


#endif