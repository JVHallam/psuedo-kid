#include "../include/grid.h"
#include <stdlib.h>

/*
typedef struct cstruct{
	int value;

	int occupied;
	
	BOOL valid_values[9];
}cell;
*/

//Calls Malloc
cell* new_cell(){
	cell* created_cell = (cell*)malloc(sizeof(cell));

	created_cell->value = 0;

	created_cell->occupied = 0;

	for(int index = 0; index < 9; ++index){
		created_cell->valid_values[index] = TRUE;
	}

	return created_cell;
}


cell** new_grid(){
	cell** created_grid = (cell**)calloc((9 * 9), sizeof(cell*));

	//Initialise the grid

	for(cell** grid_ptr = created_grid; grid_ptr < (created_grid + 81); ++grid_ptr){
		*grid_ptr = new_cell();
	}

	return created_grid;
}

void free_grid(cell** grid_start){
	for(cell** grid_ptr = grid_start; grid_ptr < (grid_start + 81); ++grid_ptr){
		//Free each cell
		free(*grid_ptr);
	}
	free(grid_start);
}



cell** parse_file_to_grid(char* file_name){
	FILE *fp = fopen(file_name, 'r');

	if(fp){
		cell** grid = new_grid();
		cell** grid_pointer = grid;
		int input = 0;
		int cell_counter = 0;

		for(input = fgetc(fp); input != EOF; input = fgetc(fp)){
			int current_char = input - '0';

			if((current_char >= 0 && current_char <= 9) && (cell_counter < 81)){
				(*grid_pointer)->value = current_char;
				if(current_char != 0){
					(*grid_pointer)->occupied = TRUE;
				}

				++grid_pointer;
				++cell_counter;
			}
			else{
				if(current_char < 0 || current_char > 9){
					printf("Invalid Character '%c' present\n", input);
				}
				else{
					puts("More than 81 valid character present.");
					++cell_counter;
				}
				break;
			}
		}
		if(cell_counter != 81){
			puts("The wrong amount of cell values were given.");

			char* error = (cell_counter > 81) ? "more than" : "only";

			printf("81 should have been given, where as %s %i are present\n", error, cell_counter);

			free_grid(grid);
			grid = 0;
		}
		return grid;
	}
	else{
		return 0;
	}
}


