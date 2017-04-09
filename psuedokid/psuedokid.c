#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "psuedokid.h"
#include "../traversal/traversal.h"
#include "../constants/constants.h"
#include "../logic/logic.h"

int* parse_file_to_grid(FILE* fp){
	int* board = (int*)calloc(81, sizeof(int));
	int* grid_pointer = board;
	int cell_counter = 0;

	for(int input = 0; (input = fgetc(fp)) != EOF;){
		if(input != '\n' && input != ' '){
			//Minor hack to convert ascii number characters to their integer counterparts.
			int current_char = input - '0';

			if((current_char >= 0 && current_char <= 9) && (cell_counter < 81)){
				*(grid_pointer++) = current_char;
				++cell_counter;
			}
			else{
				//file format invalid.
				if(current_char < 0 || current_char > 9){
					printf("Invalid character '%c' present\n", input);
				}
				else{
					puts("More than 81 valid characters present.");
					++cell_counter;

				}
				break;
			}
		}
	}

	if(cell_counter != 81){
		puts("The wrong amount of cell values were given.");

		char* error = (cell_counter > 81) ? "more than" : "only";

		printf("81 should have been given, where as %s %i are present\n",error,cell_counter);
		free(board);
		board = NULL;
	}
	return board;
}

/*=-=-=-=-Logical Analysis Functions=-=-=-*/












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

void print_board(int* board){
	for(int i = 0, *pGrid = board; i < 81; ++i){
		if(i % 9 == 0){
			putchar('\n');
		}
		printf("%i", *(pGrid++));
	}
}