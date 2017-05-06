#include <stdio.h>
#include "../include/minunit.h"
#include "../include/grid.h"
#include <stdlib.h>

static char* test_new_cell();

static char* test_new_grid();

static char* test_parse_file_to_grid_with_valid_input();

static char* test_parse_file_to_grid_with_invalid_input();
//Other
static char* run_all_tests();
int tests_run = 0;

int main(){

	char* result = "Error, a function didn't return a value";
	result = run_all_tests();

	if(result){
		puts("Testing Encountered this failure:");
		printf("\n%s\n\n", result);
	}
	else{
		puts("Testing completed with no errors");
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


static char* test_parse_file_to_grid_with_invalid_input(){

	//Don't forget to make sure that number_of_files is the number of invalid files
	//Otherwise, segfaults. Yay! Best error ever. So descriptive.
	int number_of_files = 5;
	static char* invalid_files[] = {
		"test/resources/invalid1.puzzle",
		"test/resources/invalid2.puzzle",
		"test/resources/empty.puzzle",
		"invalid file name",
		"another invalid file name"
	};
	
	for( \
		char** file_name = invalid_files; \
		file_name < (invalid_files + number_of_files); \
		++file_name
	){
		cell** parsed_grid = parse_file_to_grid(*file_name);
		mu_assert("Pointer not null, even though files are invalid", parsed_grid == 0);
	}

	return 0;
}

static char* test_parse_file_to_grid_with_valid_input(){
	int number_of_files = 2;
	char* valid_files[] = {
		"test/resources/valid1.puzzle",
		"test/resources/valid2.puzzle"
	};

	for( \
		char** cur_file = valid_files; \
		cur_file < &(valid_files[number_of_files]); \
		++cur_file
	){
		cell** parsed_grid = parse_file_to_grid(*cur_file);

		cell** grid_ptr = parsed_grid;

		mu_assert("Error, a null pointer was returned", parsed_grid != 0);

		for(int col_index = 0; col_index < 9; ++col_index){

			for(int row_index = 0; row_index < 9; ++row_index){

				//Validate each cell's value
				mu_assert( \
					"Value of a cell, x, was not: 0 <= x <= 9", \
					(((*grid_ptr)->value >= 0) && ((*grid_ptr)->value >= 0))
				);

				//Validateeach cells occupied state is 1 / 0
				mu_assert(\
					"Value of a cell's occupied state is no 1 / 0",\
					( ((*grid_ptr)->occupied == 0) || ((*grid_ptr)->occupied == 1) )
				);

				//Check that each cell's valid values list has 0 in each entry
				BOOL* valid_values_pointer = (*grid_ptr)->valid_values;
				for(int valid_value_index = 0; valid_value_index < 9; ++valid_value_index){
					mu_assert(
						"Valid value's state is not set to 1 or 0",\
						( ((*valid_values_pointer) == 0) || ((*valid_values_pointer) == 1) )
					);
					++valid_values_pointer;
				}

				++grid_ptr;
			}
		}
		free_grid(parsed_grid);
		parsed_grid = 0;

	}//end

	return 0;
}

static char* test_parse_file_to_grid(){
	//Have file name
	char* test_file = "test/resources/valid.puzzle";

	//Call parse file to grid on file name
	cell** parsed_grid = parse_file_to_grid(test_file);

	cell** grid_ptr = parsed_grid;

	mu_assert("Error, a null pointer was returned", parsed_grid != 0);

	for(int col_index = 0; col_index < 9; ++col_index){

		for(int row_index = 0; row_index < 9; ++row_index){

			//Validate each cell's value
			mu_assert( \
				"Value of a cell, x, was not: 0 <= x <= 9", \
				(((*grid_ptr)->value >= 0) && ((*grid_ptr)->value >= 0))
			);

			//Validateeach cells occupied state is 1 / 0
			mu_assert(\
				"Value of a cell's occupied state is no 1 / 0",\
				( ((*grid_ptr)->occupied == 0) || ((*grid_ptr)->occupied == 1) )
			);

			//Check that each cell's valid values list has 0 in each entry
			BOOL* valid_values_pointer = (*grid_ptr)->valid_values;
			for(int valid_value_index = 0; valid_value_index < 9; ++valid_value_index){
				mu_assert(
					"Valid value's state is not set to 1 or 0",\
					( ((*valid_values_pointer) == 0) || ((*valid_values_pointer) == 1) )
				);
				++valid_values_pointer;
			}

			++grid_ptr;
		}
	}
	free_grid(parsed_grid);
	parsed_grid = 0;

	//Check that the function returns null when it should


	return 0;
}

static char* run_all_tests(){
	//1
	mu_run_test(test_new_cell); 
	//2
	mu_run_test(test_new_grid); 
	//3
	mu_run_test(test_parse_file_to_grid_with_valid_input);
	//4
	mu_run_test(test_parse_file_to_grid_with_invalid_input);

	return 0;
}