#include "../include/porcelain.h"
#include "../include/hash_table.h"
#include "../include/grid.h"
#include "../include/logic.h"
#include "../include/grid_traversal.h"
#include <stdio.h>

static grid_table* puzzle_container = 0;

void initalise_puzzle_container(){
	puzzle_container = new_grid_table();
}

void porcelain_cleanup(){
	if(puzzle_container){
		free_table(puzzle_container);
	}
}

BOOL new_puzzle(char* file_name){
	if(!puzzle_container){
		initalise_puzzle_container();
	}
	
	cell** current_grid = parse_file_to_grid(file_name);

	grid_table* quick_test = new_grid_table();

	if(current_grid){
		//Take current_grid and set all of the valid_values for the table.

		return add_to_table(file_name, current_grid, puzzle_container);
	}
	else{
		return FALSE;
	}
}

cell** get_cell_from_table(int choice, int choice_index, int cell_index, char* key){
	cell** target_grid = get_from_table(key, puzzle_container);

	cell*** target_area = 0;

	cell** target_cell = 0;

	switch(choice){
		case ROW:
			target_area = get_row(choice_index, target_grid);
			break;

		case COLUMN:
			target_area = get_column(choice_index, target_grid);
			break;

		case CHAMBER:
			target_area = get_chamber(choice_index, target_grid);
			break;

		default:
			printf("Incorrect choice Value given\n");
	}

	if(target_area){
		if(0 <= cell_index && cell_index <= 8){
			target_cell = *(target_area + cell_index);
		}
		else{
			printf("cell_index wasn't in the range: 0 <= cell_index <= 8\n");
		}
	}
	else{
		printf("No target area was recieved\n");
	}

	return target_cell;
}

//Can only set values to be 1 through 9
BOOL is_new_value_valid(int value){
	if(1 <= value && value <= 9){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

BOOL is_index_valid(int index){
	if(0 <= index && index <= 8){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

/*
	Choice is defined in constants.h as:
		#define ROW 1
		#define COLUMN 2
		#define CHAMBER 3
*/
BOOL is_choice_valid(int choice){
	if(1 <= choice && choice <= 3){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

BOOL set_value(int choice, int choice_index, int cell_index, int value, char* key){
	//First off, validate the input:	
	cell** target_cell = 0;
	BOOL is_cell_occupied = TRUE;

	if(\
		is_choice_valid(choice) && \
		is_index_valid(choice_index) && \
		is_new_value_valid(value)
	){
		target_cell = get_cell_from_table(choice, choice_index, cell_index, key);	
		if(target_cell){
			is_cell_occupied = (*target_cell)->occupied;
		}
	}

	if(target_cell && !(is_cell_occupied)){
		//Check that value is valid for the cell.
		int value_index = value - 1;

		if((*target_cell)->valid_values[value_index] == TRUE){
			(*target_cell)->value = value;

			cell** target_grid = get_from_table(key, puzzle_container);

			update_surrounding_areas(target_cell, target_grid);

			(*target_cell)->occupied = TRUE;

			return TRUE;
		}
	}
	else{
		return FALSE;
	}
}

int get_value(int choice, int choice_index, int cell_index, char* key){
	//First off, validate the input:	
	cell** target_cell = 0;
	BOOL is_cell_occupied = TRUE;

	if(\
		is_choice_valid(choice) && \
		is_index_valid(choice_index)
	){
		target_cell = get_cell_from_table(choice, choice_index, cell_index, key);	
	} 

	if(target_cell){
		return (*target_cell)->value;
	}
	
	return 0;
}

void print_grid(char* key){
	cell** target_table = get_from_table(key, puzzle_container);

	print_grid_values(target_table);
}

//From logic.h
//BOOL is_present(cell*** given_area, int value);

BOOL is_value_present(int choice, int choice_index, int value, char* key){

	BOOL was_value_present = FALSE;

	if(\
		is_choice_valid(choice) && \
		is_index_valid(choice_index) && \
		is_new_value_valid(value)
	){
		//Next, get the area based on choice.
		cell*** desired_area = 0;

		cell** target_grid = get_from_table(key, puzzle_container);

		if(target_grid){
			switch(choice){
				case ROW:
					desired_area = get_row(choice_index, target_grid);
					break;

				case COLUMN:
					desired_area = get_column(choice_index, target_grid);
					break;

				case CHAMBER:
					desired_area = get_chamber(choice_index, target_grid);
					break;
			}
			was_value_present = is_present(desired_area, value);
		}
		else{
			printf("Key given to is_value_present was invalid.\n");
		}
	}
	else{
		printf("Values given to function is_value_present were incorrect.\n");
	}

	return was_value_present;
}