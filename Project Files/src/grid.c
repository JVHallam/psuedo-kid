#include "../include/grid.h"
#include <stdlib.h>
#include <stdio.h>

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
	if(grid_start != 0){
		for(cell** grid_ptr = grid_start; grid_ptr < (grid_start + 81); ++grid_ptr){
			//Free each cell
			free(*grid_ptr);
			*grid_ptr = 0;			
		}
		free(grid_start);
	}
}

cell** parse_file_to_grid(char* file_name){
	FILE *fp = fopen(file_name, "r");

	if(fp){
		cell** grid = new_grid();
		cell** grid_pointer = grid;
		int input = 0;
		int cell_counter = 0;
		BOOL are_invalid_values_present = 0;

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
				if(input == ' ' || input == '\n'){
					continue;
				}
				if(current_char < 0 || current_char > 9){
					are_invalid_values_present = 1;
				}
				else{
					puts("More than 81 valid characters present.");
					++cell_counter;
					break;
				}
			}
		}
		if(cell_counter != 81){
			puts("The wrong amount of cell values were given.");

			char* error = (cell_counter > 81) ? "more than" : "only";

			printf("81 should have been given, where as %s %i are present\n", error, cell_counter);

			if(are_invalid_values_present){
				perror("There were also invalid values present in the file.");
			}

			printf("'%s' is not a valid file\n\n", file_name);

			free_grid(grid);
			grid = 0;
		}
		fclose(fp);
		return grid;
	}
	else{
		perror(file_name);
		return 0;
	}
}

//A better programmer would be able to use things like function pointers
//To do this all wrapped up into 1 function.

void print_grid_values(cell** grid){
	puts(""); //Make it clearer on screen

	cell** grid_ptr = grid;

	for(int row_index = 0; row_index < 9; ++row_index){

		for(int col_index = 0; col_index < 9; ++col_index){
			printf("%i ", (*grid_ptr)->value);
			++grid_ptr;

			if((col_index % 3) == 2){
				printf("\t");
			}
		}
		puts("");

		if((row_index % 3) == 2){
			puts("");
		}
	}

	puts(""); //Make it clearer on screen
}

void print_grid_occupied(cell** grid){
	puts(""); //Make it clearer on screen

	cell** grid_ptr = grid;

	for(int row_index = 0; row_index < 9; ++row_index){

		for(int col_index = 0; col_index < 9; ++col_index){
			printf("%i ", (*grid_ptr)->occupied);
			++grid_ptr;
		}

		puts("");
	}

	puts(""); //Make it clearer on screen
}

void print_cells_valid_values(cell* target_cell){
	for(int valid_value_index = 0; valid_value_index < 9; ++valid_value_index){
		int value_to_print = 0;

		if(target_cell->valid_values[valid_value_index]){
			value_to_print = (valid_value_index + 1);
		}
		
		//Else, it's blank.
		printf("%i, ", value_to_print);
	}
}

void print_grid_valid_values(cell** grid){
	puts(""); //Make it clearer on screen

	cell** grid_ptr = grid;

	for(int row_index = 0; row_index < 9; ++row_index){

		for(int col_index = 0; col_index < 9; ++col_index){

			printf("\nCell %i\n", ((row_index * 9) + col_index));
			print_cells_valid_values(*grid_ptr);
			++grid_ptr;
			printf("\n");
		}
	}

	puts(""); //Make it clearer on screen
}
