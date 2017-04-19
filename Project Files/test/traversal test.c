#include "../include/traversal.h"
#include "minunit.h"
#include "../include/constants.h"
#include <stdio.h>

int test_grid[9][9] = 	{
							{0, 1, 2, 		3, 4, 5, 		6, 7, 8},
							{9, 10, 11, 	12, 13, 14, 	15, 16, 17},
							{18, 19, 20,	21, 22, 23,		24, 25, 26},
							{27, 28, 29,	30, 31, 32, 	33, 34, 35},
							{36, 37, 38,	39, 40, 41, 	42, 43, 44},
							{45, 46, 47, 	48, 49, 50, 	51, 52, 53},
							{54, 55, 56, 	57, 58, 59, 	60, 61, 62},
							{63, 64, 65,	66, 67, 68,		69, 70, 71},
							{72, 73, 74, 	75, 76, 77, 	78, 79, 80},
						};

int tests_run = 0;

//int* grid_traverse(int choice, int index, int* grid_start);
//Where choice is CHAMBER, ROW, COLUMN from constants.h
static char* test_grid_traverse_rows();

static char* test_grid_traverse_columns();

static char* test_grid_traverse_chambers();

//int* get_area_start(int* current_cell, int choice, int* grid_start);

static char* test_get_area_start_rows();

static char* test_get_area_start_columns();

static char* test_get_area_start_chambers();

static char* run_all_tests();

int main(){
	char* result = run_all_tests();

	if(result){
		printf("%s\n", result);
	}
	else{
		printf("All tests in Traversal passed!\n");
	}

	printf("Tests run %d\n", tests_run);
	return result != 0;
}

static char* test_grid_traverse_rows(){
	for(int index = 0; index < 9; ++index){
		int* start_of_choice = grid_traverse(ROW, index, &test_grid[0][0]);

		mu_assert("Did not traverse to the start of the correct ROW!", \
					start_of_choice == &test_grid[index][0]);
	}

	return 0;	
}

static char* test_grid_traverse_columns(){
	for(int index = 0; index < 9; ++index){
		int* start_of_choice = grid_traverse(COLUMN, index, &test_grid[0][0]);

		mu_assert("Did not traverse to the start of the correct COLUMN!", \
					start_of_choice == &test_grid[0][index]);
	}

	return 0;
}

static char* test_grid_traverse_chambers(){
	for(int index = 0; index < 9; ++index){
		int* start_of_choice = grid_traverse(CHAMBER, index, &test_grid[0][0]);

		int* chamber_starts[9] = {
			&test_grid[0][0],
			&test_grid[0][3],
			&test_grid[0][6],
			&test_grid[3][0],
			&test_grid[3][3],
			&test_grid[3][6],
			&test_grid[6][0],
			&test_grid[6][3], 
			&test_grid[6][6]
		};


		mu_assert(	"Did not traverse to the start of the correct CHAMBER!", \
			chamber_starts[index] == start_of_choice);
	}
	return 0;
}

static char* test_get_area_start_rows(){
	//int* get_area_start(int* current_cell, int choice, int* grid_start)

	//We'll just go diagonal to get a cross section

	for(int index = 0; index < 9; ++index){
		int* test_cell = &test_grid[index][index];

		int* area_start = get_area_start(test_cell, ROW, &test_grid[0][0]);

		mu_assert("Not getting the correct area start for ROW!", \
					area_start == &test_grid[index][0]);
	}

	return 0;
}

static char* run_all_tests(){

	mu_run_test(test_grid_traverse_rows);
	mu_run_test(test_grid_traverse_columns);
	mu_run_test(test_grid_traverse_chambers);

	mu_run_test(test_get_area_start_rows);

	return 0;
}