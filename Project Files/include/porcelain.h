#ifndef PORCELAIN_H_
#define PORCELAIN_H_

#include "../include/grid.h"
/*
	Porcelain is the abstraction layer to for psuedo-kid.
	The program should work as follows:
		grid.h creates a grid

		grid_traversal.h manages moving around inside of the grid

		logic.h should manage the logical operations. 
			Is a value present
			setting a cells valid_values
			updating valid_values

		hash_table.h should store all puzzles in use.

		porcelain.h should abstract the user away from all of these layers.
		it should return no pointers to the user and all grid management should be 
		done by this layer, using the previous headers.

		Whenver a change is made by the user, using a porcelain function, everything should
		be done and updated for them.
*/

/*
	Adds the puzzle from the file to the grid-holder hash table.
	file_name then becomes the key to acces that puzzle, via the other commands in this header.

	When adding the puzzle, the puzzle's valid values need to have been set at this point.
	The user should not be setting the valid values for the puzzle manualy.
*/
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

//Returns the value for a cell.
int get_value(int choice, int choice_index, int cell_index, char* key);

//Returns true/false, based on if a value is present in an area.
BOOL is_value_present(int choice, int choice_index, int value, char* key);

//Returns true/false, based on if a value can be put in a cell.
BOOL is_value_valid(int choice, int choice_index, int cell_index, int value, char* key);

/*
	If you have a cell in a chamber, it can be difficult to find the index of it's row 
	and column. This is here to do just that.

	choice + choice_index => are given by you to locate the cell.

	wanted_indexes_area => 	the area (ROW, COLUMN, CHAMBER) that you want to find out for
							the given cell.

*/
int get_cells_area_index(	int choice, int choice_index, int cell_index,\
							int wanted_indexes_area, char* key);

//Prints the grid out.
void print_grid(char* key);

void print_target_grid_valid_values(char* key);

//Returns TRUE if puzzle is in a "Completed" state, Where all values are 1 - 9.
BOOL is_finished(char* key);

#endif
