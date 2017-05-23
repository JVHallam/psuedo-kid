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

//Where choice is ROW, CHAMBER, COLUMN, CELL, as defined in grid.h
BOOL set_value(int choice, int choice_index, int cell_index, char* key);
#endif
