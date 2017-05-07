#include "../include/minunit.h"
#include "../include/grid.h"
#include "../include/grid_traversal.h"
#include <stdio.h>
#include <stdlib.h>

int tests_run = 0;

cell** test_grid;

static char* test_traverse_to_chamber();

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

		test_chamber = get_chamber(5, test_grid);
		mu_assert("traverse to chamber is returning null for valid input", test_chamber != 0);
		cell* chamber_five[9] = {
			*(test_grid + 33), 
			*(test_grid + 34), 
			*(test_grid + 35), 
			*(test_grid + 42), 
			*(test_grid + 43), 
			*(test_grid + 44), 
			*(test_grid + 51), 
			*(test_grid + 52), 
			*(test_grid + 53)
		};
		cell** chamber_five_ptr = chamber_five;
		test_chamber_ptr = test_chamber;
		for(int index = 0; index < 9; ++index){
			cell* chamber_fives_value = *(chamber_five_ptr + index);
			cell* test_chambers_value = **(test_chamber + index);
			
			mu_assert(\
				"A cell returned for chamber 5 is invalid", \
				test_chambers_value == chamber_fives_value\
			);
		}
		free(test_chamber);

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

	test_row = get_row(5, test_grid);
	mu_assert("get row is returning null with valid args", test_row != 0);
	cell* row_five[9] = {
		*(test_grid + 45),
		*(test_grid + 46),
		*(test_grid + 47),
		*(test_grid + 48),
		*(test_grid + 49),
		*(test_grid + 50),
		*(test_grid + 51),
		*(test_grid + 52),
		*(test_grid + 53)
	};
	for(int cell_index = 0; cell_index < 9; ++cell_index){
		cell* test_rows_cell = **(test_row + cell_index);
		cell* row_fives_cell = row_five[cell_index];

		mu_assert(\
			"Cells being returned by get_row aren't correct",\
			test_rows_cell == row_fives_cell
		);
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

	test_column = get_column(5, test_grid);
	mu_assert("get column is returning null with valid args", test_get_column != 0);
	cell* column_five[9] = {
		*(test_grid + 5),
		*(test_grid + 14),
		*(test_grid + 23),
		*(test_grid + 32),
		*(test_grid + 41),
		*(test_grid + 50),
		*(test_grid + 59),
		*(test_grid + 68),
		*(test_grid + 77)
	};
	for(int cell_index = 0; cell_index < 9; ++cell_index){
		cell* test_columns_cell = **(test_column + cell_index);
		cell* column_fives_cell = column_five[cell_index];

		mu_assert(\
			"Cells being returned by get column aren't corret",
			test_columns_cell == column_fives_cell
		);
	}
	free(test_column);

	return 0;
}

static char* run_all_tests(){
	test_grid = parse_file_to_grid("test/resources/valid1.puzzle");

	mu_run_test(test_get_chamber);
	mu_run_test(test_get_row);
	mu_run_test(test_get_column);

	if(test_grid){
		free_grid(test_grid);
	}
	return 0;
}