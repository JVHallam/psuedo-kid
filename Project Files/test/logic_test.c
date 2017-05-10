#include "../include/minunit.h"
#include "../include/logic.h"
#include "../include/grid.h"
#include "../include/grid_traversal.h"
#include <stdlib.h>
#include <stdio.h>

int tests_run = 0;

cell** test_grid;

static char* run_all_tests();

static char* test_get_cell_index();

static char* test_get_cells_column_index();

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
int main(){
	char* result = run_all_tests();

	if(result){
		printf("\n\n%s\n", result);
	}

	printf("Tests run: %i\n", tests_run);
	return result != 0;
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

static char* test_get_cell_index(){
	for(int index = 0; index < 81; ++index){
		cell** test_cell = test_grid + index;
		mu_assert(\
			"get_cell_index is not returning the correct values.",\
			get_cell_index(test_cell, test_grid) == index
		);
	}
	return 0;
}

static char* test_get_cells_row_index(){
	for(int row_index = 0; row_index < 9; ++row_index){
		for(int column_index = 0; column_index < 9; ++column_index){
			cell** test_cell = test_grid + ((row_index * 9) + column_index);
			int cells_row_index = get_cells_row_index(test_cell, test_grid);

			mu_assert(\
				"Values from get_cells_row_index are incorrect!",\
				cells_row_index == row_index
			);
		}
	}
	return 0;
}

static char* test_get_cells_column_index(){
	for(int row_index = 0; row_index < 9; ++row_index){
		for(int column_index = 0; column_index < 9; ++column_index){
			cell** test_cell = test_grid + ((row_index * 9) + column_index);
			int cells_column_index = get_cells_column_index(test_cell, test_grid);

			mu_assert(\
				"Values from get_cells_column_index are incorrect!",\
				cells_column_index == column_index
			);
		}
	}
	return 0;
}

static char* test_get_cells_chamber_index(){
	for(int row_of_chambers = 0; row_of_chambers < 3; ++row_of_chambers){
		for(int row_in_chamber = 0; row_in_chamber < 3; ++row_in_chamber){
			for(int each_chamber = 0; each_chamber < 3; ++each_chamber){
				for(int column = 0; column < 3; ++column){

					int chamber_were_in = (row_of_chambers * 3) + each_chamber;
					int cell_index = \
						(row_of_chambers * 27) \
						+ (row_in_chamber * 9) \
						+ (each_chamber * 3) \
						+ column;

					cell** test_cell = test_grid + cell_index;

					int test_cells_chamber_index = get_cells_chamber_index(test_cell, test_grid);

					mu_assert(\
						"Test cells chamber index is not returning the correct values!",\
						chamber_were_in == test_cells_chamber_index	
					);

				}
			}
		}
	}

	return 0;
}

//Where choice is ROW, CHAMBER or COLUMN from grid.h
static char* test_is_present_for_area(char* file_name, int choice){
	cell** is_present_test_grid = parse_file_to_grid(file_name);

	if(is_present_test_grid){

		for(int area_index = 0; area_index < 9; ++area_index){
			for(int value = 1; value <= 9; ++value){
				cell*** test_area = 0;

				switch(choice){
					case ROW:
						test_area = get_row(area_index, is_present_test_grid);
						break;

					case COLUMN:
						test_area = get_column(area_index, is_present_test_grid);
						break;

					case CHAMBER:
						test_area = get_chamber(area_index, is_present_test_grid);
						break;
				}

				/*
					is_present should return true when:
						value != (area_index + 1)

					is_present should return true when the value isn't the same as the
					area_index + 1:
						chamber 0, 1 is missing. Therefore, is_present returns false
						for value 1;

						chamber 1, 2 is missing, therefore, is_present returns false 
						for value 2;

						Etc. But should return true for all remaining values from one
						to nine.
				*/
				BOOL expected_outcome = (value != (area_index + 1));
				BOOL actual_outcome = is_present(test_area, value);

				mu_assert(\
					"is_present is returning an unexpected value",\
					expected_outcome == actual_outcome
				);
				free(test_area);
			}
		}
	}
	else{
		return "Couldn't parse given file to grid.";
	}
}

static char* test_is_present(){
	//test_is_present_for_area(char* file_name, int choice)
	char* result = 0;

	result = test_is_present_for_area("test/resources/is_present_row_test.puzzle", ROW);
	if(result){
		return result;
	}

	result = test_is_present_for_area("test/resources/is_present_column_test.puzzle", COLUMN);
	if(result){
		return result;
	}

	result = test_is_present_for_area("test/resources/is_present_chamber_test.puzzle", CHAMBER);
	if(result){
		return result;
	}

	return 0;
}

static char* run_all_tests(){
	test_grid = parse_file_to_grid("test/resources/valid1.puzzle");
	if(test_grid){
		mu_run_test(test_get_cell_index);
		mu_run_test(test_get_cells_row_index);
		mu_run_test(test_get_cells_column_index);
		mu_run_test(test_get_cells_chamber_index);
		mu_run_test(test_is_present);

		free_grid(test_grid);
		return 0;
	}
	else{
		return "Failed to create a valid value for test_grid";
	}
}