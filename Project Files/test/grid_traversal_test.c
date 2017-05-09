#include "../include/minunit.h"
#include "../include/grid.h"
#include "../include/grid_traversal.h"
#include <stdio.h>
#include <stdlib.h>

/*NOTES*/
	/*
		This set of tests is extremely messy!

		I thought, for some dumb reason, that hardcoding values would be the best 
		way to achieve these tests. After some careful consideration, with logic_test.c
		I decided that it's better to use a forloop, increment over the grid, and
		check values as i go.

		If i use hard values to check first, just to make sure it passes that test
		Then increment over the board, it will condense this file down, make it
		cleaner, cover more outcomes and be easier to maintain.

		God damn, do we write some bad code some days.
	*/
/*NOTES*/


int tests_run = 0;

cell** test_grid;

static char* test_traverse_to_chamber();

static char* test_get_row();

static char* test_get_column();

static char* run_all_tests();

int main(){
	char* result = run_all_tests();

	if(result){
		printf("\n%s\n\n", result);
	}

	printf("Tests run: %i\n", tests_run);
	return result != 0;
}

static char* test_get_chamber(){
	//This one's easy to improve, grab the forloop from the logic_test.c file


	if(test_grid){
		//Check that it won't take indexes outside of the 0 - 9 range
		mu_assert(\
			"Function is taking invalid args and not returning null",\
			get_chamber(-1, test_grid) == 0
		);

		mu_assert(\
			"Function is taking invalid args and not returning null",\
			get_chamber(10, test_grid) == 0
		);

		cell*** test_chamber = get_chamber(0, test_grid);
		mu_assert("traverse to chamber is returning null for valid input", test_chamber != 0);
		//Check by hand that the values for chamber 0 are correct
		cell* chamber_zero[9] = {
			*(test_grid),
			*(test_grid + 1),
			*(test_grid + 2),
			*(test_grid + 9),
			*(test_grid + 10),
			*(test_grid + 11),
			*(test_grid + 18),
			*(test_grid + 19),
			*(test_grid + 20)
		};
		cell** chamber_zero_ptr = chamber_zero;
		cell*** test_chamber_ptr = test_chamber;
		//Don't forget, we're comparing cell* here
		//Therefore, you must dereference accordingly.
		for(int index = 0; index < 9; ++index){
			cell* chamber_zeros_value = *(chamber_zero_ptr + index);
			cell* test_chambers_value = **(test_chamber + index);
			
			mu_assert(\
				"A cell returned for chamber 0 is invalid", \
				test_chambers_value == chamber_zeros_value\
			);
		}
		free(test_chamber);

		/*
			This is going to be a little bit more complicated than for the others:

		for(int row_of_chambers = 0; row_of_chambers < 3; ++row_of_chambers){
			for(int row_in_chamber = 0; row_in_chamber < 3; ++row_in_chamber){
				for(int each_chamber = 0; each_chamber < 3; ++each_chamber){
					for(int column = 0; column < 3; ++column){

		The best way to do this may be to:
			call get_chamber 9 times

			put these chambers into a new grid

			compare the 2 grids.

			I honestly can't see anything wrong with that.
		*/

		return 0;
	}
	else{
		return "Test grid is null";
	}
	return 0;
}

static char* test_get_row(){
	//check it's validating atleast some of the input
	mu_assert(\
		"Function is taking invalid args and not returning null",\
		get_row(-1, test_grid) == 0
	);

	mu_assert(\
		"Function is taking invalid args and not returning null",\
		get_row(10, test_grid) == 0
	);


	cell*** test_row = get_row(0, test_grid);
	mu_assert("get row is returning null with valid args", test_row != 0);
	cell* row_zero[9] = {
		*(test_grid),
		*(test_grid + 1),
		*(test_grid + 2),
		*(test_grid + 3),
		*(test_grid + 4),
		*(test_grid + 5),
		*(test_grid + 6),
		*(test_grid + 7),
		*(test_grid + 8),
	};
	for(int cell_index = 0; cell_index < 9; ++cell_index){
		cell* test_rows_cell = **(test_row + cell_index);
		cell* row_zeros_cell = row_zero[cell_index];

		mu_assert(\
			"Cells being returned from get_row aren't correct", \
			test_rows_cell == row_zeros_cell
		);
	}
	free(test_row);
	test_row = 0;

	for(int row_index = 0; row_index < 9; ++row_index){
		test_row = get_row(row_index, test_grid);
		cell** actual_row_start = test_grid + (row_index * 9);

		for(int cell_index = 0; cell_index < 9; ++cell_index){
			cell** test_rows_cell = *(test_row + cell_index);
			cell** actual_rows_cell = actual_row_start + cell_index;

			mu_assert(\
				"Values being returned from get_row are incorrect",\
				test_rows_cell == actual_rows_cell
			);
		}
		free(test_row);
		test_row = 0;
	}
	return 0;
}

static char* test_get_column(){
	//check it's validating atleast some of the input
	mu_assert(\
		"Function is taking invalid args and not returning null",\
		get_row(-1, test_grid) == 0
	);

	mu_assert(\
		"Function is taking invalid args and not returning null",\
		get_row(10, test_grid) == 0
	);

	cell*** test_column = get_column(0, test_grid);
	mu_assert("get column is returning null with valid args", test_get_column != 0);
	cell* column_zero[9] = {
		*(test_grid),
		*(test_grid + 9),
		*(test_grid + 18),
		*(test_grid + 27),
		*(test_grid + 36),
		*(test_grid + 45),
		*(test_grid + 54),
		*(test_grid + 63),
		*(test_grid + 72),
	};
	for(int cell_index = 0; cell_index < 9; ++cell_index){
		cell* test_columns_cell = **(test_column + cell_index);
		cell* column_zeros_cell = column_zero[cell_index];

		mu_assert(\
			"Cells being returned from get_column aren't correct",
			test_columns_cell = column_zeros_cell
		);
	}

	free(test_column);
	test_column = 0;

	for(int column_index = 0; column_index < 9; ++column_index){
		test_column = get_column(column_index, test_grid);
		cell** actual_column_start = (test_grid + column_index);

		for(int cell_index = 0; cell_index < 9; ++cell_index){
			cell** test_columns_cell = *(test_column + cell_index);
			cell** actual_columns_cell = (actual_column_start + (cell_index * 9));
			
			mu_assert(\
				"Error, get_column is returning incorrect values",\
				test_columns_cell == actual_columns_cell	
			);
		}
		free(test_column);
		test_column = 0;
	}
	
	return 0;
}

static char* run_all_tests(){
	test_grid = parse_file_to_grid("test/resources/valid1.puzzle");

	if(test_grid){
		mu_run_test(test_get_chamber);
		mu_run_test(test_get_row);
		mu_run_test(test_get_column);

		free_grid(test_grid);

		return 0;
	}
	else{
		return "Error, test_grid was not created";
	}
}