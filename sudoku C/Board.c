#include "Board.h"



//get the row at an index as an array of size 9
int* GetRow(int rowNum, Board* b)
{
	//create row buffer
	static int row[9];

	//this works because the boxes of index 0, 3, 6 are the start of each row of boxes
	int startBox = floor(rowNum / 3) * 3;

	//because startBox index is equal to the index of the first row in that box, the row we want is always +0, +1, or +2, rows from that number
	int startNum = (rowNum - startBox) * 3;


	int it = 0;


	//get the next 2 boxes after the starting box
	for (int i = startBox; i < startBox + 3; i++)
	{

		//get the next 2 numbers after the starting number - the starting number index is the same for every box
		for (int j = startNum; j < startNum + 3; j++)
		{

			row[it] = b->boxes[i].cells[j];
			it++;

		}

	}

	return row;
}


//get the column at an index as an array of size 9
int* GetColumn(int colNum, Board* b)
{

	static int col[9];

	//the first box in the column is either 0, 1, or 2, and since there are 9 columns, the start box can be found by flooring the colNum / 3
	int startBox = floor(colNum / 3);

	//the first number is always at index 0, 1, or 2 in the startbox - multiplying the startbox by 3 will always give the first column in that box
	int startNum = colNum - (startBox * 3);


	int it = 0;

	//since there are three rows of boxes, and each box in a column is at index n+3 from the one above it, adding 3 and 6 gives the second and third box in a column
	for (int i = startBox; i <= startBox + 6; i += 3)
	{

		//same logic as above
		for (int j = startNum; j <= startNum + 6; j += 3)
		{

			col[it] = b->boxes[i].cells[j];
			it++;

		}

	}


	return col;
}


//get cell at an index to be read or modified
int* GetIndex(int row, int col, Board* b)
{

	//getting the index of the first box in the correct row plus the index of the first box in a column gets us the desired box
	int rowBox = floor(row / 3) * 3;
	int colBox = floor(col / 3);
	int curBox = rowBox + colBox;


	//same logic for the cell inside the box
	int rowBoxIndex = (row - rowBox) * 3;
	int colBoxIndex = col - (colBox * 3);
	int boxIndex = rowBoxIndex + colBoxIndex;


	return &b->boxes[curBox].cells[boxIndex];

}


//check if box contains a number
bool BoxContains(int cell, int num, Board* b)
{

	//get numbers in a box
	int cells[9];


	memcpy(cells, b->boxes[cell].cells, sizeof(cells));

	bool contains = false;


	//check every number in the box
	for (int i = 0; i < BOX_SIZE; i++)
	{

		//compare the numbers in the cell to the wanted number
		if (cells[i] == num)
		{

			contains = true;
			break;

		}

	}


	return contains;

}


//check if a row contains a number
bool RowContains(int rowNum, int num, Board* b)
{

	int* cells = GetRow(rowNum, b);

	bool contains = false;


	//check every number in the row
	for (int i = 0; i < RC_SIZE; i++)
	{

		//compare the number in row to wanted number
		if (*(cells + i) == num)
		{

			contains = true;
			break;

		}

	}


	return contains;

}


//check if a column contains a number
bool ColumnContains(int colNum, int num, Board* b)
{

	int* cells = GetColumn(colNum, b);

	bool contains = false;


	//check every number in the column
	for (int i = 0; i < RC_SIZE; i++)
	{

		//compare number in column to wanted number
		if (*(cells + i) == num)
		{

			contains = true;
			break;

		}

	}


	return contains;

}


//check if a number at a position is valid
bool CellValid(int rowNum, int colNum, int num, Board* b)
{

	bool valid = true;


	//check if a row or column contains the number
	if (RowContains(rowNum, num, b) || ColumnContains(colNum, num, b))
	{

		valid = false;

		//skip extra math if we know we return false
		return valid;

	}


	//math for finding the correct box
	int rowBox = floor(rowNum / 3) * 3;
	int colBox = floor(colNum / 3);
	int curBox = rowBox + colBox;


	//check if the box contains the number
	if (BoxContains(curBox, num, b))
	{

		valid = false;

	}

	return valid;

}


void PrintBoard(Board* b)
{

	for (int i = 0; i < BOARD_SIZE; i++)
	{

		int* nums = GetRow(i, b);

		for (int j = 0; j < BOX_SIZE; j++)
		{

			//print the numbers in every row
			printf("%d ", *(nums + j));


			//print extra space after every 3 columns to distinguish boxes
			if ((j + 1) % 3 == 0)
			{

				printf(" ");

			}

		}


		//print extra space after every 3 lines to distinguish boxes
		if ((i + 1) % 3 == 0)
		{

			printf("\n");

		}

		printf("\n");

	}

}


void ResetBoard(Board* b)
{

	for (int i = 0; i < BOARD_SIZE; i++)
	{

		for (int j = 0; j < BOX_SIZE; j++)
		{

			b->boxes[i].cells[j] = 0;

		}

	}

}
