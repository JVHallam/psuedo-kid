#include <stdio.h>
#include <minunit.h>
#include "../include/grid.h"
#include <stdlib.h>

static char* test_new_cell();

static char* test_new_grid();

//Other
static char* run_all_tests();
int tests_run = 0;

int main(){

	char* result = run_all_tests();

	if(result){
		printf("\n%s\n\n", result);
	}

	printf("Tests run: %i\n", tests_run);
	return result != 0;
}

static char* test_targeted_cell(cell* test_cell){

	//Check that a pointer was actually created.
	mu_assert("A non-null pointer wasn't returned", test_cell != 0);

	//Check that all of the values have been initialised correctly
	mu_assert("Value not set to zero", test_cell->value == 0);
	mu_assert("Occupied not set to zero", test_cell->occupied == 0);

	for(int index = 0; index < 9; ++index){
		mu_assert("Not all of the valid values have been set to true", \
				  test_cell->valid_values[index] == TRUE);
	}

	return 0;
}

static char* test_new_cell(){
	cell* test_cell = new_cell();

	test_targeted_cell(test_cell);

	free(test_cell);
	return 0;
}

static char* test_new_grid(){
	cell** test_grid = new_grid();
	//A grid should be a 9 x 9 array of cells.
	mu_assert("new_grid returned null", test_grid != 0);

	for(cell** grid_ptr = test_grid; grid_ptr < (test_grid + 81); ++grid_ptr){
		char* cell_test_result = test_targeted_cell(*grid_ptr);
		mu_assert("Error with the cells inside of the test_grid", cell_test_result == 0);
	}

	//Then free up the resources.
	for(cell** grid_ptr = test_grid; grid_ptr < (test_grid + 81); ++grid_ptr){
		free(*grid_ptr);
	}
	free(test_grid);

	return 0;
}

static char* run_all_tests(){
	mu_run_test(test_new_cell);
	mu_run_test(test_new_grid);

	return 0;
}