#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "psuedokid.h"

/*File Parsing*/
int* parse_file_grid(char* file_path){

	FILE *fp = fopen(file_path, "r");

	int* grid = (int*)calloc(81, sizeof(int));
	int* grid_pointer = grid;

	for(int c = 0; (c = fgetc(fp)) != EOF;){
		if(c != '\n' && c != ' '){
			/*This is a bit of a hack, but atoi was being a bitch*/
			int d = c - '0'; 
			*(grid_pointer++) = d;
		}
	}

	fclose(fp);
	return grid;
}

/*=-=-=-Traversing Functions.=-=-=-*/

/*Choice being column, row, chamber, cell*/
int* grid_traverse(int choice, int index, int* grid_start){
	int *destination = grid_start;

	switch(choice){
		case COLUMN:
			destination += index;
			break;
		case ROW:
			destination += (index * 9);
			break;
		case CHAMBER:
			/*desination += (row chamber starts on ) + (column chamber starts on)*/
			destination += ((index / 3) * 27) + ((index % 3) * 3);
			break;

		case CELL:
			destination += index;
			break;
	}
	return destination;
}

/*Is called inside of get_area*/
int* get_area_start(int* current_cell, int choice, int* grid_start){
	int cell_index = current_cell - grid_start;
	
	int choice_index = 0;

	switch(choice){
		case COLUMN:
			choice_index = cell_index % 9;
			break;

		case ROW:
			choice_index = cell_index / 9;
			break;

		case CHAMBER:
			/*
				Remember, this is integer division. These can't be cancelled out.
			*/
			choice_index = (((cell_index / 27) * 3)) + ((cell_index % 9) / 3);
			break;
	}

	return grid_traverse(choice, choice_index, grid_start);
}

/*get_area has calls to Calloc, must always be paired with free.*/
int** get_area(int *cell, int choice, int *grid_start){
	int **container_area = (int**)calloc(9, sizeof(int*));
	int **container_pointer = container_area;

	int *cell_pointer = get_area_start(cell, choice, grid_start);

	int main_increment = 0, secondary_increment = 0;
	/*
		Incrementing over a row or a column is 8 same equal steps.
		Incrementing over a chamber is 3 small steps, then a jump to the next row (6 cells).
	*/
	switch(choice){
		case COLUMN:
			main_increment = 9;
			break;

		case ROW:
			main_increment = 1;
			break;

		case CHAMBER:
			main_increment = 1;
			secondary_increment = 6;
			break;
	}


	for(int secondary_loop = 0; secondary_loop < 3; ++secondary_loop){
	
		for(int main_loop = 0; main_loop < 3; ++main_loop){

			*(container_pointer++) = cell_pointer;
			cell_pointer += main_increment;

		}

		cell_pointer += secondary_increment;
	}

	return container_area;
}

/*=-=-=-=-Logical Analysis Functions=-=-=-*/

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

void compute_board(int *grid_start){
	/*Until a loop over has made no changes, continue to call solve_area*/

	for(BOOL is_changed = TRUE; is_changed;){
		is_changed = FALSE;
	
		for(int choice = 1; choice <= 3; ++choice){

			for(int area_index = 0; area_index < 9; ++area_index){
				int *cell_ptr =  grid_traverse(choice, area_index, grid_start);

				BOOL outcome = solve_area(cell_ptr, choice, grid_start);

				if(!is_changed){
					is_changed = outcome;
				}
			}
		}
	}
}