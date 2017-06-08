#include "../include/porcelain.h"
#include "../include/algorithms.h"
#include "../include/grid.h"
#include "../include/grid_traversal.h"
#include "../include/logic.h"
#include <stdlib.h>

void test_algorithms(char* puzzle_key){
	if(new_puzzle(puzzle_key)){
		for(int choice = 1; choice <= 3; ++choice){
			for(int choice_index = 0; choice_index < 9; ++choice_index){
				for(int value = 1; value <= 9; ++value){
					single_spot_algorithm(choice, choice_index, value, puzzle_key);
				}

				for(int cell_index = 0; cell_index < 9; ++cell_index){
					single_occupant_algorithm(choice, choice_index, cell_index, puzzle_key);
				}
			}
		}

		porcelain_cleanup();
	}
}

void test_porcelain(char* puzzle_key){
	if(new_puzzle(puzzle_key)){
		//Test them all!
		for(int choice = 1; choice <= 3; ++choice){
			for(int choice_index = 0; choice_index < 9; ++choice_index){
				for(int cell_index = 0; cell_index < 9; ++cell_index){
					int a = get_value(choice, choice_index, cell_index, puzzle_key);
				}
			}
		}

		porcelain_cleanup();
	}
}

void test_grid_h(char* puzzle){
	//Make a new puzzle
	cell** test_grid = parse_file_to_grid(puzzle);

	if(test_grid){
		free_grid(test_grid);
	}
}

void test_traversal(char* puzzle){
	cell** test_grid = parse_file_to_grid(puzzle);

	if(test_grid){
		for(int area_index = 0; area_index < 9; ++area_index){
			
			cell*** area = get_chamber(area_index, test_grid);
			free(area);
			
			area = get_column(area_index, test_grid);
			free(area);

			area = get_row(area_index, test_grid);
			free(area);

			area = 0;
		}
		free_grid(test_grid);
	}
}

void test_logic(char* puzzle){
	cell** test_puzzle = parse_file_to_grid(puzzle);

	if(test_puzzle){
		int offset = 35;

		cell** test_cell = test_puzzle + offset;

		get_cell_index(test_cell, test_puzzle);

		free_grid(test_puzzle);
	}
}

int main(){
	char* puzzle_key = "test/resources/almost_complete.puzzle";
	char* zeroes = "test/resources/only_zeroes.puzzle";

	while(1){	
		test_porcelain(zeroes);

		test_algorithms(zeroes);
	}	
	return 0;
}