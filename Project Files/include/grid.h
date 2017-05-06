#ifndef GRID_H_
#define GRID_H_

#include "constants.h"
/*
	The value is the value that it holds

	Occupied is:
		1 if occupied
		0 if empty
		-1 if phantom occupancy

	valid values is a bool array. Where each entry represents a value.

	valid_values[0] -> represents 1. If valid_values[0] is TRUE then 1 can go in this cell.
*/
typedef struct cstruct{
	int value;

	int occupied;
	
	BOOL valid_values[9];
}cell;

/*
	Calls Malloc and sets:
		Value to 0
		Occupied to FALSE
		each value in valid_values is set to TRUE
*/
cell* new_cell();

//Create a 9 x 9 array of cell pointers.
cell** new_grid();

//Free the grid after usage
void free_grid(cell** grid_start);

cell** parse_file_to_grid(char* file_name);

//Sometimes it's easier to use a bunch of printfs, rather than a debugger.
void print_grid_values(cell** grid);

void print_grid_occupied(cell** grid);

void print_grid_valid_values(cell** grid);

#endif