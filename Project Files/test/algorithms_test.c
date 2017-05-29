#include "../include/algorithms.h"
#include "../include/minunit.h"
#include "../include/porcelain.h"
#include <stdio.h>

int tests_run = 0;

static char* run_all_tests();

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
int main(){
	char* puzzle = "test/resources/super_easy.puzzle";

	if(new_puzzle(puzzle)){
		puts("Okay");

		print_target_grid_valid_values(puzzle);
	}



	char* result = run_all_tests();

	printf("Tests run: %i\n", tests_run);
	return result != 0;
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//BOOL single_spot_algorithm(int choice, int choice_index, int value, char* key)


static char* run_all_tests(){

	return 0;
}