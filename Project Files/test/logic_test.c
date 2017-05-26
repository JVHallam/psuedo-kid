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
		printf("\n%s\n\n", result);
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

static char* test_set_all_valid_values(){
	/*
		puzzles to test this with:
			only_zeroes.puzzle:
				This is full of only zeroes for cells. That way,
				all cells should have all values as a valid value.

			completed.puzzle:
				This is a completed puzzle, therefore, all cells should have
				no valid values.

			set_valid_values1.puzzle
				for each chamber_index:
					cell 1 of each chamber should have that chamber's index + 1 as an
					invalid value

					cell 1 of each row should have that rows index + 1 as an invalid
					value too.
	*/	

	cell** only_zeroes = parse_file_to_grid("test/resources/only_zeroes.puzzle");
	if(only_zeroes){

		//Being only zeroes, each cell should have valid_values[x] == TRUE
		set_all_valid_values(only_zeroes);

		for(cell** grid_ptr = only_zeroes; grid_ptr < (only_zeroes + 81); ++grid_ptr){
			for(\
				BOOL* valid_values_ptr = (*grid_ptr)->valid_values;\
				valid_values_ptr < ((*grid_ptr)->valid_values) + 9;\
				++valid_values_ptr
			){
				//For each valid value, it should be TRUE.
				mu_assert(\
					"A valid value for an all zero grid has been set to false",\
					*valid_values_ptr == TRUE
				);
			}
		}
		free_grid(only_zeroes);
	}
	else{
		return "Failed to parse file to grid";
	}

	cell** completed = parse_file_to_grid("test/resources/completed.puzzle");
	if(completed){

		set_all_valid_values(completed);

		//Being completed, all valid values should be set to FALSE

		for(cell** grid_ptr = completed; grid_ptr < (completed + 81); ++grid_ptr){
			for(\
				BOOL* valid_values_ptr = (*grid_ptr)->valid_values;\
				valid_values_ptr < ((*grid_ptr)->valid_values) + 9;
				++valid_values_ptr
			){
				mu_assert(\
					"A valid value has been set to TRUE, even though the grid is completed",\
					*valid_values_ptr == FALSE
				);	
			}
		}

		free_grid(completed);
	}
	else{
		return "Failed to parse file to grid";
	}

	cell** set_valid_values1 = parse_file_to_grid("test/resources/set_valid_values1.puzzle");
	if(set_valid_values1){
		set_all_valid_values(set_valid_values1);

		for(int chamber_index = 0; chamber_index < 9; ++chamber_index){
			//cell*** get_chamber(int chamber_index, cell** grid_start);
			cell*** current_chamber = get_chamber(chamber_index, set_valid_values1);

			//For each cell, check that the above is correct.

			for(\
				cell*** area_ptr = current_chamber;\
				area_ptr < (current_chamber + 9);
				++area_ptr
			){
				BOOL target_valid_value = (**area_ptr)->valid_values[chamber_index];

				mu_assert(\
					"Target value was not set to FALSE.",\
					target_valid_value == FALSE
				);
			}

			free(current_chamber);
		}

		free_grid(set_valid_values1);
	}
	else{
		return "Failed to parse file to grid";
	}

	return 0;
}


/*
	This test is bad:
		It only tests for what we need

		Doesn't check if it's changing things it shouldn't.
*/
BOOL is_cell_in_area(cell** target_cell, cell*** target_area){
	for(cell*** area_ptr = target_area; area_ptr < (target_area + 9); ++area_ptr){
		if(*area_ptr == target_cell){
			return TRUE;
		}
	}
	return FALSE;
}


//Only tested on a single cell, but it works. I can't be bothered to write some clever and
//Comprehensive test that does everything that i need. Do i look like a QA tester to you?
//No, i'm a C programmer. I program and pray it doesn't break.
static char* test_update_surrounding_areas(){
	
	cell** zeroes_grid = parse_file_to_grid("test/resources/only_zeroes.puzzle");

	int desired_value = 1;

	(*zeroes_grid)->value = desired_value;

	update_surrounding_areas(zeroes_grid, zeroes_grid);

	cell*** test_column = get_column(0, zeroes_grid);
	cell*** test_row = get_row(0, zeroes_grid);
	cell*** test_chamber = get_chamber(0, zeroes_grid);

	for(cell** grid_ptr = zeroes_grid; grid_ptr < (zeroes_grid + 81); ++grid_ptr){
		int cell_index = get_cell_index(grid_ptr, zeroes_grid);

		if(\
			is_cell_in_area(grid_ptr, test_row) || \
			is_cell_in_area(grid_ptr, test_column) || \
			is_cell_in_area(grid_ptr, test_chamber)
		){
			//In the area that should be effected.
			mu_assert(\
				"Cells in the effected area aren't having valid_values[0] set to false",\
				(*grid_ptr)->valid_values[0] == FALSE
			);

			for(int i = 1; i < 9; ++i){
				mu_assert(\
					"update_surrounding_areas is also making changes to additional slots "
					"in the valid_values array, when it shouldn't be.",\
					(*grid_ptr)->valid_values[i] == TRUE
				);				
			}

		}
		else{
			//In the area that should NOT be effected.
			for(int i = 0; i < 9; ++i){
				mu_assert(\
					"Cells in the uneffected areas are having their valid_values changed.",\
					(*grid_ptr)->valid_values[i] == TRUE
				);				
			}

		}

	}
	free(test_column);
	free(test_row);
	free(test_chamber);

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
		mu_run_test(test_set_all_valid_values);
		mu_run_test(test_update_surrounding_areas);

		free_grid(test_grid);
		return 0;
	}
	else{
		return "Failed to create a valid value for test_grid";
	}
}