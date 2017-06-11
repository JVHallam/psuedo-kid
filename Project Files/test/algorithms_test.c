#include "../include/algorithms.h"
#include "../include/minunit.h"
#include "../include/porcelain.h"
#include <stdio.h>

int tests_run = 0;

static char* run_all_tests();

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
int main(){
	char* result = run_all_tests();

	if(result){
		printf("\n\n%s\n", result);
	}

	printf("Tests run: %i\n", tests_run);
	return result != 0;
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//BOOL single_spot_algorithm(int choice, int choice_index, int value, char* key)

static char* test_single_spot_algorithm(){
	char* puzzle = "test/resources/valid_puzzles/evil.puzzle";
	//char* puzzle = "test/resources/valid_puzzles/hard2.puzzle";
	//char* puzzle = "test/resources/valid_puzzles/super_fiendish.puzzle";

	if(new_puzzle(puzzle)){
		print_grid(puzzle);

		int run_counter = 0;

		BOOL change_was_made = FALSE;

		char* is_puzzle_complete = (is_finished(puzzle)) ? "True" : "False";
		printf("is puzzle complete: %s\n", is_puzzle_complete);

//Single spot start
		for(int i = 0; i < 10; ++i){
		//puts("single spot");

		do{
			change_was_made = FALSE;

			run_counter++;

			for(int choice = 1; choice <= 3; ++choice){

				for(int area_index = 0; area_index < 9; ++area_index){

					for(int value = 1; value <= 7; ++value){

						if(single_spot_algorithm(choice, area_index, value, puzzle)){
							change_was_made = TRUE;
						}

					}
				}
			}
		}
		while(change_was_made == TRUE);

		//puts("single occupant");


		do{
			change_was_made = FALSE;

			run_counter++;

			for(int choice = 1; choice <= 3; ++choice){
				for(int area_index = 0; area_index < 9; ++area_index){
					for(int cell_index = 0; cell_index < 9; ++cell_index){
						if(single_occupant_algorithm(choice, area_index, cell_index, puzzle)){
							change_was_made = TRUE;
						}
					}
				}
			}
		}
		while(change_was_made);


//Single occupant end


		//Subline
		change_was_made = FALSE;

		for(int choice = 1; choice <= 3; ++choice){
			for(int area_index = 0; area_index < 9; ++area_index){
				for(int value = 1; value <= 9; ++value){
					if(subline_algorithm(choice, area_index, value, puzzle)){
						change_was_made = TRUE;
					}
				}
			}
		}

		}


		printf("Run counter: %i\n", run_counter);
		print_grid(puzzle);
		is_puzzle_complete = (is_finished(puzzle)) ? "True" : "False";
		printf("is puzzle complete: %s\n", is_puzzle_complete);

		print_target_grid_valid_values(puzzle);
		return 0;
	}
	else{
		return "Couldn't load valid grid.";
	}
}

static char* second_test(){
	char* puzzle_key = "test/resources/subline.puzzle";

	if(new_puzzle(puzzle_key)){

		//print_target_grid_valid_values(puzzle_key);

		int choice = CHAMBER;
		for(int area_index = 0; area_index < 2; ++area_index){
			for(int value = 1; value <= 9; ++value){
				if(subline_algorithm(choice, area_index, value, puzzle_key)){
					puts("Change was made");
				}
			}
		}
		
		print_target_grid_valid_values(puzzle_key);
	}

	return 0;
}

static char* grouping_algorithm_test(){
	//char* test_puzzle = "test/resources/valid_puzzles/super_fiendish.puzzle";
	//char* test_puzzle = "test/resources/only_zeroes.puzzle";
	char* test_puzzle = "test/resources/grouping_algorithm.puzzle";

	if(new_puzzle(test_puzzle)){
		
		//int choice = COLUMN;
		/*
		for(int choice = 1; choice <= 3; ++choice){
			puts("=-=-=-Choice=-=-=-");
			char* choice_array[] = {"Row", "Column", "Chamber"};
			int choice_index = choice - 1;
			printf("Choice: %s\n", choice_array[choice_index]);

			for(int choice_index = 0; choice_index < 9; ++choice_index){
				printf("Choice_index: %i\n", choice_index);
				grouping_algorithm(choice, choice_index, test_puzzle);
			}
		}
		*/
		int choice = CHAMBER;
		int choice_index = 0;
		
		grouping_algorithm(choice, choice_index, test_puzzle);
		
	}

	return 0;
}

static char* run_all_tests(){
	//mu_run_test(test_single_spot_algorithm);
	//mu_run_test(second_test);
	mu_run_test(grouping_algorithm_test);

	return 0;
}