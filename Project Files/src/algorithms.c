#include "../include/algorithms.h"
#include "../include/porcelain.h"
#include <stdio.h>

BOOL single_spot_algorithm(int choice, int choice_index, int value, char* key){
	BOOL was_a_value_changed = FALSE;

	//If we're not wasting our time.
	if(is_value_present(choice, choice_index, value, key) == FALSE){
		//For each value, in each area
		//Count how many cells it can go in.

		int valid_index = -1;
//BOOL is_value_valid(int choice, int choice_index, int cell_index, int value, char* key);
		for(int cell_index = 0; cell_index < 9; ++cell_index){
			if(is_value_valid(choice, choice_index, cell_index, value, key)){
				if(valid_index == -1){
					valid_index = cell_index;
				}
				else{
					valid_index = -1;
					break;
				}
			}
		}

		if(valid_index != -1){
//BOOL set_value(int choice, int choice_index, int cell_index, int value, char* key);
			set_value(choice, choice_index, valid_index, value, key);
			was_a_value_changed = TRUE;
		}
		
	}
	return was_a_value_changed;
}