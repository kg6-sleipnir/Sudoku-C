#ifndef HEADER_BOARD
#define HEADER_BOARD

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//number of cells in a box
#define BOX_SIZE 9

//number of boxes in a board
#define BOARD_SIZE 9

//number of cells in a row or column
#define RC_SIZE 9



typedef struct Box
{
	int cells[BOX_SIZE];
} Box;

typedef struct Board
{
	Box boxes[BOARD_SIZE];
} Board;



//get the row at an index as an array of size 9
int* GetRow(int rowNum, Board* b);


//get the column at an index as an array of size 9
int* GetColumn(int colNum, Board* b);


//get cell at an index to be read or modified
int* GetIndex(int row, int col, Board* b);


//check if box contains a number
bool BoxContains(int cell, int num, Board* b);


//check if a row contains a number
bool RowContains(int rowNum, int num, Board* b);


//check if a column contains a number
bool ColumnContains(int colNum, int num, Board* b);


//check if a number at a position is valid
bool CellValid(int rowNum, int colNum, int num, Board* b);


void PrintBoard(Board* b);


void ResetBoard(Board* b);

#endif