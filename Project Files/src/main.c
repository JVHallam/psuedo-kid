#include <stdio.h>
#include "../include/porcelain.h"
#include "../include/algorithms.h"
#include "../include/constants.h"

char* parse_arguments(int argc, char* argv[]);

BOOL run_single_occupant_on_entire_puzzle(char* puzzle_key);

BOOL run_single_spot_on_entire_puzzle(char* puzzle_key);

int main(int argc, char* argv[]){
	//Take the users commandline argument

	char* puzzle_key = parse_arguments(argc, argv);

	if(puzzle_key){
		if(new_puzzle(puzzle_key)){

			//This section would go far better if i understood how to use function pointers.
			BOOL was_change_made = TRUE;
			int passes_made = 0;

			while( (!is_finished(puzzle_key)) && was_change_made){
				++passes_made;
				was_change_made = FALSE;

//BOOL single_spot_algorithm(int choice, int choice_index, int value, char* key);
				BOOL is_single_spot_effective = FALSE;
				do{
					is_single_spot_effective = run_single_spot_on_entire_puzzle(puzzle_key);
					if(is_single_spot_effective){
						was_change_made = TRUE;
					}

				}
				while(is_single_spot_effective);

				BOOL is_single_occupant_effective = FALSE;
				do{
					is_single_occupant_effective = run_single_occupant_on_entire_puzzle(puzzle_key);
					if(is_single_occupant_effective){
						was_change_made = TRUE;
					}
				}
				while(is_single_occupant_effective);

			}//End of the algorithms loop.
			
			char* grid_state = (is_finished(puzzle_key)) ? "Completed" : "Incomplete";

			printf("\nGrid state: %s\n", grid_state);
			printf("Passes made: %i\n", passes_made);

			print_grid(puzzle_key);

			porcelain_cleanup();
		}
		else{
			return 1;
		}
	}
	else{
		puts("Not enough arguments given.");

		return 1;
	}

	return 0;
}

char* parse_arguments(int argc, char* argv[]){
	char* puzzle_key = 0;

	if(argc > 1){
		puzzle_key = argv[1];
	}

	return puzzle_key;
}

BOOL run_single_occupant_on_entire_puzzle(char* puzzle_key){
	BOOL was_change_made = FALSE;

	for(int choice = 1; choice <= 3; ++choice){
		for(int choice_index = 0; choice_index < 9; ++choice_index){
			for(int cell_index = 0; cell_index < 9; ++cell_index){
				if(single_occupant_algorithm(	choice, choice_index, \
												cell_index, puzzle_key)){
					was_change_made = TRUE;
				}
			}
		}
	}

	return was_change_made;
}

BOOL run_single_spot_on_entire_puzzle(char* puzzle_key){

	BOOL was_change_made = FALSE;

	for(int choice = 1; choice <= 3; ++choice){
		for(int choice_index = 0; choice_index < 9; ++choice_index){
			for(int value = 1; value <= 9; ++value){
				if(single_spot_algorithm(	choice, choice_index, value, \
											puzzle_key)){
					was_change_made = TRUE;
				}
			}
		}
	}

	return was_change_made;
}