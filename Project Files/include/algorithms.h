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

#endif
