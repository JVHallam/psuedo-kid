#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

#include "../include/constants.h"

/*
	Single spot:
		Give it an area, and an area index and a value.

		It then looks to see if the value can only be put into 1 spot. If it can, it puts it
		there.
		It then returns true if it changes a value.

		Else, return false.

	Choice as defined in constants.h
*/
BOOL single_spot_algorithm(int choice, int choice_index, int value, char* key);

/*
	Single occupant:
		Look at a cell

		Find how many valid values it has

		If it has a single occupant that can occupy it without breaking sudoku rule, then set
		that cells value to that occupant.
*/
BOOL single_occupant_algorithm(int choice, int choice_index, int cell_index, char* key);

//Count how many valid values a cell has.
int count_valid_values(int choice, int choice_index, int cell_index, char* key);

BOOL subline_algorithm(int choice, int choice_index, int value, char* key);

//Also known as hidden pairs
BOOL grouping_algorithm(int choice, int choice_index, char* key);

#endif
