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

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

typedef struct group_struct{
	int length;

	//Varying sized array of int values
	int* values_that_fit; 

	//The location of the group too
	int choice;
	int choice_index;
	char* puzzle_key;

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

/*
	pointers contains an array of length x
		x = pointers->length

	each pointer in the array is pointing to a value.

	each value can only go in x number of spaces

	we're checking if each value can only go in the same spots as one another
	if they can all only exist in the same cells
		those cells can only contain those values.

		set those cells' valid_values arrays to only contain those values.

	else
		return false.
*/
BOOL are_values_in_same_cells(pointer_array* pointers, group_holder* groups){
	/*
		Take the first value in pointers

		Go to groups->choice, groups->choice_index

		find the first cell where the first value appears.
			make sure that all other values also occur in that cell


			if not, exit, return false.

		do so for the rest of the cells.

		if they all exist in the same cells, return true.
	*/
	BOOL were_all_values_in_same_cells = TRUE;

	int first_value = **(pointers->pointers);

	int choice = groups->choice;
	int choice_index = groups->choice_index;
	char* key = groups->puzzle_key;

	for(int cell_index = 0; cell_index < 9; ++cell_index){

		if(is_value_valid(choice, choice_index, cell_index, first_value, key)){
			//Then see if all other values in the array are valid.
			BOOL are_all_values_valid = TRUE;

			for(int pointer_offset = 1; pointer_offset < pointers->length; ++pointer_offset){
				int current_value = **(pointers->pointers + pointer_offset);

				if(!is_value_valid(choice, choice_index, cell_index, current_value, key)){
					are_all_values_valid = FALSE;

					break;
				}
			}

			if(!are_all_values_valid){
				were_all_values_in_same_cells = FALSE;

				break;
			}
		}
	}

	return were_all_values_in_same_cells;
}

void set_valid_values_to_group_only(pointer_array* pointers, group_holder* groups){

	int first_value = **(pointers->pointers);
	int choice = groups->choice;
	int choice_index = groups->choice_index;
	char* key = groups->puzzle_key;

	for(int cell_index = 0; cell_index < 9; ++cell_index){
		if(is_value_valid(choice, choice_index, cell_index, first_value, key)){
			
			//Set all valid values for that cell to FALSE
			for(int value = 1; value <= 9; ++value){
				edit_valid_value(choice, choice_index, cell_index, value, FALSE, key);
			}

			//Then set the valid_Value for each value in pointers to true.
			for(int pointer_offset = 0; pointer_offset < pointers->length; ++pointer_offset){
				int value = **(pointers->pointers + pointer_offset);

				edit_valid_value(choice, choice_index, cell_index, value, TRUE, key);
			}
		}
	}


}

BOOL run_hidden_groups(pointer_array* pointers, group_holder* groups){

	/*
		I think there's a problem.
			Let's say there's a valid group evaluted on round 1.
			On the rest of round 1, no changes by other algorithms are made.

			Round 2, the same group is re-evaluated to be valid.
			This returns a True.

			We then get stuck in an infinite loop, being told that the same group
			is valid, over and over again.

	*/
	BOOL was_a_valid_group_found = FALSE;

	if(are_values_in_same_cells(pointers, groups)){
		//Set all cells that can hold 
		set_valid_values_to_group_only(pointers, groups);

		was_a_valid_group_found = TRUE;

		//puts("Hidden Groups Set Values");
	}

	return was_a_valid_group_found;
}

BOOL set_pointer_value(int* new_value, int index, pointer_array* pointers, \
						group_holder* groups){

	BOOL was_hidden_groups_successful = FALSE;

	//Set the value
	*(pointers->pointers + index) = new_value;
	//If a change is made to the final pointer, trigger the all important 
	//Block of code.

	
	if( (index + 1) == pointers->length){
		//Run the desired code.

		//print_pointer_arrays_array(pointers);

		was_hidden_groups_successful = run_hidden_groups(pointers, groups);
	}

	return was_hidden_groups_successful;
}

//When a value in the pointer array is incremented, all pointers above it are set to
//The (previous pointers value + 1);
BOOL increment_target(int index, pointer_array* pointers, group_holder* groups){
	int* int_array_end = (groups->values_that_fit + groups->length - 1);

	BOOL was_hidden_groups_successful = FALSE;

	int* new_value = (*(pointers->pointers + index)) +1;

	for(int offset = index; offset < pointers->length; ++offset){
		if(new_value <= int_array_end){
			was_hidden_groups_successful = set_pointer_value(new_value, offset, pointers, groups);
		}

		new_value = (*(pointers->pointers + offset)) + 1;
	}

	return was_hidden_groups_successful;
}

BOOL analyse_for_valid_groups(pointer_array* pointers, group_holder* groups){
	/*
		This code creates an array of pointers. 
		These pointers are pointing to a list of possibilities.

		Each pointer is pointing to a unique value in this list, higher than the previous
		pointer.

		When one pointer is incremented, the pointers later in the list are set
		to be 1 past it, then the next to be 1 past that, etc.

		Whenever the last pointer in the list has it's value changed, in the 
		set_pointer_value function, it assumes a new valid group has been formed
		and runs the grouping code.


		Say we have a list of values: 0, 1, 2, 3, 4, 5

		and 3 pointers:
		p1, p2, p3

		p1 = 0;
		p2 = 1;
		p3 = 2;

		That's one list. We then increment p3, until it's at the end of the list, p3 = 5.
		When p3 = 5, we go down and increment p2. If p2 is incremented, then we set p3 = p2+1;

		This goes on until p2 = 5; When p2 = 5, set p1=1, p2=2, p3=3.

		All pointers must be pointing at unique values when the grouping code runs.

		So whenever p3 changes value, it runs the code.
	*/

	//Yes, i am setting the first pointer to point before the array.
	//Yes, i am then incrementing it back on. This way, increment_target sets all
	//Values for all other pointers.
	BOOL was_change_made = FALSE;

	set_pointer_value(groups->values_that_fit -1, 0, pointers, groups);
	increment_target(0, pointers, groups);

	int level = 0;
	int top_level = (pointers->length) - 1;

	int* values_array_end = (groups->values_that_fit) + (groups->length - 1);

	while(*(pointers->pointers) < values_array_end){ 
		if( (*(pointers->pointers + level)) ==  values_array_end){
			--level;
		}
		else{
			//our current pointer isn't pointing to the end.

			//If we're not at the top and the value above us isn't at the end.
			if(
				(level < top_level) && \
				(*(pointers->pointers + level + 1)) < values_array_end
			){
				++level;
			}
			else{
				BOOL was_hidden_groups_successful = increment_target(level, pointers, groups);
				if(was_hidden_groups_successful && !was_change_made){
					was_change_made = TRUE;
				}
			}
		}
	}

	//This needs to be an actual return value at some point.
	return was_change_made;
}

BOOL grouping_algorithm(int choice, int choice_index, char* key){
	BOOL was_change_made = FALSE;
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
		current_group->choice = choice;
		current_group->choice_index = choice_index;
		current_group->puzzle_key = key;

		get_valid_group_values(choice, choice_index, key, current_group, group_size);

		if(current_group->length > 0){
			//Now we need a pointer array.
			pointer_array* pointers = (pointer_array*)malloc(sizeof(pointer_array));
			pointers->length = group_size;
			pointers->pointers = (int**)calloc(group_size, sizeof(int*));


			BOOL had_effect = analyse_for_valid_groups(pointers, current_group);
			if(had_effect){
				was_change_made = TRUE;
			}

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
