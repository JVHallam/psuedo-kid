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
	char* puzzle = "test/resources/super_easy.puzzle";

	if(new_puzzle(puzzle)){
		print_grid(puzzle);

//BOOL single_spot_algorithm(int choice, int choice_index, int value, char* key);
		for(int i = 0; i < 100; ++i){
			for(int choice = 1; choice <=3; ++choice){
				for(int choice_index = 0; choice_index < 9; ++choice_index){
					for(int value = 1; value <= 9; ++value){
						
						single_spot_algorithm(choice, choice_index, value, puzzle);
					}
				}
			}
			
		}

		print_grid(puzzle);		
	}

	return 0;
}

static char* run_all_tests(){
	mu_run_test(test_single_spot_algorithm);

	return 0;
}