#include "../constants/constants.h"
#include "../traversal/traversal.h"
#include <stdlib.h>

/*Return true if a value is present in an area*/
BOOL is_present(int value, int **area){
	for(int **area_ptr = area; area_ptr < (area + 9); ++area_ptr){
		if(**area_ptr == value){
			return TRUE;
		}
	}
	return FALSE;
}

BOOL is_full(int **area){
	return is_present(0, area);
}

/*Function Doesn't take into account if the cell has a non-zero value*/
BOOL is_appropriate(int *cell, int value, int* grid_start){
	/*
		Don't try to optimise this function. It's written so that free can be called in an
		easy and careful manor.
	*/
	BOOL is_cell_appropriate = TRUE;

	for(int choice = 1; choice <= 3; ++choice){
		int **area = get_area(cell, choice, grid_start);

		BOOL is_value_present = is_present(value, area);
		free(area);
		area = 0;

		if(is_value_present){
			is_cell_appropriate = FALSE;
			break;
		}
	}
	return is_cell_appropriate;
}

/*Should Be set to return TRUE if a value was changed, FALSE if not.*/
BOOL solve_area(int *cell, int choice, int* grid_start){
	int **area = get_area(cell, choice, grid_start);
	BOOL is_changed = FALSE;

	for(int value = 1; value <= 9; ++value){
		if(is_present(value, area)){
			continue;
		}

		else{
			int *appropriate_cell = 0;
			
			for(int **cell_ptr = area; cell_ptr < (area + 9); ++cell_ptr){

				if(**cell_ptr == 0 && is_appropriate(*cell_ptr, value, grid_start)){

					if(!appropriate_cell){
						appropriate_cell = *cell_ptr;
					}

					else{
						appropriate_cell = 0;
						break;
					}

				}
			}

			if(appropriate_cell){
				*appropriate_cell = value;
				is_changed = TRUE;
			}
		}
	}

	free(area);
	area = 0;
	return is_changed;
}