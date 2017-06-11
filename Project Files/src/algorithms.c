#include "../include/algorithms.h"
#include "../include/porcelain.h"
#include <stdio.h>
#include <stdlib.h>


//Find how many cells in an area, a selected value can go into.
//If it's only the one, put it there. Else, do nothing.
BOOL single_spot_algorithm(int choice, int choice_index, int value, char* key){
	BOOL was_a_value_changed = FALSE;

	//If we're not wasting our time.
	if(is_value_present(choice, choice_index, value, key) == FALSE){
		

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

//Go to a cell and return how many valid values it has.
int count_valid_values(int choice, int choice_index, int cell_index, char* key){
	//BOOL is_value_valid(int choice, int choice_index, int cell_index, int value, char* key);
	int valid_count = 0;
	for(int value = 1; value <= 9; ++value){
		if(is_value_valid(choice, choice_index, cell_index, value, key)){
			++valid_count;
		}
	}

	return valid_count;
}

//If it has got more than 1 potential occupant, then it returns zero.
int get_single_occupant(int choice, int choice_index, int cell_index, char* key){
	int single_occupant = 0;

	for(int value = 1; value <= 9; ++value){
		if(is_value_valid(choice, choice_index, cell_index, value, key)){
			if(single_occupant == 0){
				single_occupant = value;
			}
			else{
				single_occupant = 0;
				break;
			}
		}
	}

	return single_occupant;
}

BOOL single_occupant_algorithm(int choice, int choice_index, int cell_index, char* key){
	int valid_count = count_valid_values(choice, choice_index, cell_index, key);

	if(valid_count == 1){
		//Get single occupant.
		int new_value = get_single_occupant(choice, choice_index, cell_index, key);

		//Set value to be single occupant.
		BOOL value_was_set = set_value(choice, choice_index, cell_index, new_value, key);

		if(value_was_set){
			return TRUE;
		}
	}

	return FALSE;
}



BOOL subline_algorithm(int choice, int choice_index, int value, char* key){
	/*
		Look at the area.

		Count how many valid cells the value has in that area.

		if 2 or 3:
			check if those cells are in the same CHAMBER
			if yes:
				check if those cells are in the same row:
					if yes, set all other cells in that row to have valid value for "value" 
					to false.

			if no:
				check if those cells are in the same column:
					if yes, set all other cells in that column to have valid value for "value"
					to false.
	*/
	
	//If we're not wasting precious clock cycles on a 3GHz processor.
	if(!is_value_present(choice, choice_index, value, key)){
		//Count how many cells can hold the value
		//Store their index in the bool array.
		int valid_cells_count = 0;

		BOOL can_hold_value[9];
		for(int i = 0; i < 9; ++i){
			can_hold_value[i] = FALSE;
		}

		for(int cell_index = 0; cell_index < 9; ++cell_index){
			if(is_value_valid(choice, choice_index, cell_index, value, key)){
				++valid_cells_count;

				can_hold_value[cell_index] = TRUE;
			}
		}

/*
int cells_chamber_index = get_cells_area_index(	choice, choice_index,\
																	cell_index, CHAMBER, key);
*/

		if(valid_cells_count == 2 || valid_cells_count == 3){
			//Check if they're in the same row or column.
			BOOL are_all_in_same_area = TRUE;
			int secondary_area = 0;
			int secondary_area_index = -1;

			if(choice == CHAMBER){
				int first_cells_chamber = -1;
				
				//Check if all are in the same row.
				for(int cell_index = 0; cell_index < 9; ++cell_index){
					if(can_hold_value[cell_index]){
						int cells_chamber_index = get_cells_area_index(
																		choice, choice_index,\
																		cell_index, ROW, \
																		key \
																	   );

						if(first_cells_chamber == -1){
							first_cells_chamber = cells_chamber_index;
							secondary_area_index = cells_chamber_index;
//int get_cells_area_index(	int choice, int choice_index, int cell_index,\
int wanted_indexes_area, char* key);
						}
						else{
							if(first_cells_chamber != cells_chamber_index){
								are_all_in_same_area = FALSE;
								break;
							}
						}
					}
				}

				if(are_all_in_same_area){
					secondary_area = ROW;
				}
				else{
					//Check if they're all in the same column.
					are_all_in_same_area = TRUE;
					first_cells_chamber = -1;
					for(int cell_index = 0; cell_index < 9; ++cell_index){
						if(can_hold_value[cell_index]){
							int cells_chamber_index = get_cells_area_index(
																			choice, choice_index,\
																			cell_index, COLUMN,\
																			key \
																		   );

							if(first_cells_chamber == -1){
								first_cells_chamber = cells_chamber_index;
								secondary_area_index = cells_chamber_index;
							}
							else{
								if(first_cells_chamber != cells_chamber_index){
									are_all_in_same_area = FALSE;
									break;
								}
							}
						}
					}
					if(are_all_in_same_area){
						secondary_area = COLUMN;
					}
				}
				
			}
			else{//We're checking if they're in the same chamber.
				int first_cells_chamber = -1;
				secondary_area = CHAMBER;

				for(int cell_index = 0; cell_index < 9; ++cell_index){
					if(can_hold_value[cell_index]){
						int cells_chamber_index = get_cells_area_index(
																		choice, choice_index,\
																		cell_index, CHAMBER,\
																		key \
																	   );
						if(first_cells_chamber == -1){
							first_cells_chamber = cells_chamber_index;
							secondary_area_index = cells_chamber_index;
						}
						else{
							if(first_cells_chamber != cells_chamber_index){
								are_all_in_same_area = FALSE;
								break;
							}
						}
					}
				}
			}

			if(are_all_in_same_area){
				//Cycle through the secondary_area.
				//Set all cells to have FALSE for this valid_value
				for(int cell_index = 0; cell_index < 9; ++cell_index){
					edit_valid_value(secondary_area, secondary_area_index,\
												cell_index, value, FALSE, key);
				}

				//Cycle back through using the old list, setting the selected back up
				//To TRUE
				for(int cell_index = 0; cell_index < 9; ++cell_index){
					//can_hold_value[]
					if(can_hold_value[cell_index]){
						edit_valid_value(choice, choice_index, cell_index, value, TRUE, key);
					}
				}
				return TRUE;
			}
			else{
				return FALSE;
			}
		}
		else{
			return FALSE;
		}
	}
	else{
		return FALSE;
	}
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

typedef struct group_struct{
	int length;

	//Varying sized array of int values
	int* values_that_fit; 
}group_holder;

typedef struct p_array{
	//Varying sized array of int*-ers
	int** pointers;
	int length;
}pointer_array;


//Go to an area and count how many valid locations it has.
int count_valid_locations(int choice, int choice_index, int value, char* key){
	int valid_location_count = 0;

	if(!is_value_present(choice, choice_index, value, key)){

		//count how many cells the value can already go into
		for(int cell_index = 0; cell_index < 9; ++cell_index){
			if(is_value_valid(choice, choice_index, cell_index, value, key)){
				++valid_location_count;
			}
		}
	}

	return valid_location_count;
}


/*
	Go to the puzzle of key, and go to area (choice, choice_index)

	take a group_holder and find values valid for that group, that fit group_size.

	load them into the group_holder.
*/
void get_valid_group_values( int choice, int choice_index, char* key,\
						group_holder* current_group, int group_size){

	/*
		For each value that isn't already in an area
			find how many cells it can go into

			if the number of cells == group_size, load it into the array.
	*/

	//All cells are invalid, from the get go.
	BOOL is_cell_valid_state_array[9];
	for(int index = 0; index < 9; ++index){
		is_cell_valid_state_array[index] = FALSE;
	}

	//How many values can fit into our group.
	int current_group_count = 0;

	for(int value = 1; value <= 9; ++value){

		int valid_locations_count = count_valid_locations(choice, choice_index, value, key);

		if(valid_locations_count == group_size){
			int value_index = value - 1;

			is_cell_valid_state_array[value_index] = TRUE;

			++current_group_count;
		}
	}

	if(current_group_count >= group_size){
		current_group->values_that_fit = (int*)calloc(current_group_count, sizeof(int));
		current_group->length = current_group_count;

		int* values_array_ptr = current_group->values_that_fit;

		for(int index = 0; index < 9; ++index){
			if(is_cell_valid_state_array[index]){
				//The index = value - 1
				*values_array_ptr = (index + 1);
				++values_array_ptr;
			}
		}
	}
}

void print_pointer_arrays_array(pointer_array* pointers){
	if(pointers){
		printf("Length: %i\nValues: ", pointers->length);

		for(int i = 0; i < pointers->length; ++i){
			if(*(pointers->pointers + i)){
				printf("%i, ", **(pointers->pointers + i));
			}
		}
		printf("\n\n");
	}
}

void set_pointer_value(int* new_value, int index, pointer_array* pointers){
	//Set the value
	*(pointers->pointers + index) = new_value;
	//If a change is made to the final pointer, trigger the all important 
	//Block of code.

	
	if( (index + 1) == pointers->length){
		print_pointer_arrays_array(pointers);
	}
}

//When a value in the pointer array is incremented, all pointers above it are set to
//The (previous pointers value + 1);
void increment_target(int index, pointer_array* pointers, group_holder* groups){
	int* int_array_end = (groups->values_that_fit + groups->length - 1);

	int* new_value = (*(pointers->pointers + index)) +1;

	for(int offset = index; offset < pointers->length; ++offset){
		if(new_value <= int_array_end){
			set_pointer_value(new_value, offset, pointers);
		}

		new_value = (*(pointers->pointers + offset)) + 1;
	}
}

BOOL analyse_for_valid_groups(pointer_array* pointers, group_holder* groups){

	/*
		Do what the incrementing over arrays's code did, but change what the
		code does on changes to the final pointer.
	*/

	/*
		additional functions needed:
			set_value(int*, index, pointer_array);

		increment_target(0, pointers, values);

		void set_value(int* new_value, int index, pointer_array* pointers)
		void increment_target(int index, pointer_array* pointers, group_holder* groups)
	*/

	//Yes, i am setting the first pointer to point before the array.
	//Yes, i am then incrementing it back on. This way, increment_target sets all
	//Values for all other pointers.
	set_pointer_value(groups->values_that_fit -1, 0, pointers);
	increment_target(0, pointers, groups);

	int level = 0;
	int top_level = (groups->length) - 1;

	int* values_array_end = groups->values_that_fit + (groups->length - 1);

	while(*(pointers->pointers) < groups->values_that_fit){
		if( (*(pointers->pointers + level)) ==  values_array_end){
			--level;
		}
		else{
			//our current pointer isn't pointing to the end.

			//If we're not at the top and the value above us isn't at the end.
			if(
				(level < top_level) && \
				(*(pointers->pointers + level + 1) != values_array_end)
			){
				++level;
			}
			else{
				increment_target(level, pointers, groups);
			}
		}
	}

	//This needs to be an actual return value at some point.
	return FALSE;
}

BOOL grouping_algorithm(int choice, int choice_index, char* key){

	/*
		What we want:
			A list of values that can be a part of our current group.
	*/

	//Group size 0 and 9 achieve nothing as they indicate empty and full chambers.
	for(int group_size = 1; group_size < 9; ++group_size){
		/*	
			What we want is to find all values that fit into our current group.
		*/
		group_holder* current_group = (group_holder*) malloc(sizeof(group_holder));
		current_group->length = 0;
		current_group->values_that_fit = 0;

		get_valid_group_values(choice, choice_index, key, current_group, group_size);

		if(current_group->length > 0){
			//Now we need a pointer array.
			pointer_array* pointers = (pointer_array*)malloc(sizeof(pointer_array));
			pointers->length = group_size;
			pointers->pointers = (int**)calloc(group_size, sizeof(int*));

			BOOL had_effect = analyse_for_valid_groups(pointers, current_group);

			//if(had_effect), get ready to return TRUE;
			/*
				Currently here, code needs to go here to prepare for what to do
				if(has_effect);
			*/

			//Don't forget to free pointers.
			if(pointers){
				if(pointers->pointers){
					free(pointers->pointers);
				}
				free(pointers);
			}
			pointers = 0;
		}

		//Free group_holder, called current_group
		if(current_group->values_that_fit){
			free(current_group->values_that_fit);
		}
		free(current_group);
		current_group = 0;
	}

}
