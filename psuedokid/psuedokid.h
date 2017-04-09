#ifndef PSUEDOKID_H_
#define PSUEDOKID_H_

#include "../constants/constants.h"


//Calls Calloc, returns a 9 x 9 int array representing the sudoku board.
//int* parse_file_grid(char* file_path);

/*
	Calls calloc, returns a 9 x 9 int array representing the sudoku board.
	If the file is not formatted correctly, will return null.
*/
int* parse_file_to_grid(FILE* fp);

/*
	Traversing Functions
	All of these will return pointers to areas. Don't change that actual state of the board.
*/





/*
	Logical Analysis functions
	All of these are designed to logically analyse an area and change it based on the results.
*/













//Takes a pointer to a board and attempts to solve it to the best of the algorithm's abilites.
void compute_board(int *grid_start);


/*
	Misc. Functions.
*/
void print_board(int* board);

#endif
