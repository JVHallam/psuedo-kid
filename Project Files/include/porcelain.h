#ifndef PORCELAIN_H_
#define PORCELAIN_H_

#include "../include/grid.h"
/*
	The point of porcelain is to do all of the table management and correspond with the
	following algorithms file.

	The most basic of basic functions:
		porcelain.c should not be returning ANY pointers

		added_to_tables(file_name_that_becomes_key)

		int get_value(cell index, key)

		BOOL set_value(cell_index, key)
			Then goes and updates all other values

		BOOL is_present(area_index)

	Whenever a change is made, porcelain should set all of the valid values of cells that are
	effected.
*/

//Adds the puzzle from the file to the grid.
//file_name then becomes the key to access that puzzle, via the other commands.
BOOL new_puzzle(char* file_name);

//Cleans up the table once finished.
void porcelain_cleanup();


/*
	Have a target cell:
		check if it can contain a value without breaking sudoku rule

		if it can: set it. return TRUE
		if it can't: return FALSE

	choice_index ranges from 0 - 8

	cell_index ranges from 0 - 8

	Where choice is ROW, CHAMBER, COLUMN, CELL, as defined in grid.h
*/
BOOL set_value(int choice, int choice_index, int cell_index, int value, char* key);

int get_value(int choice, int choice_index, int cell_index, char* key);

BOOL is_value_present(int choice, int choice_index, int value, char* key);

BOOL is_value_valid(int choice, int choice_index, int cell_index, int value, char* key);

void print_grid(char* key);

#endif
