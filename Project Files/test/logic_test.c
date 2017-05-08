#include "../include/minunit.h"
#include "../include/logic.h"
#include "../include/grid.h"
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

static char* test_is_present(){

	return 0;
}

static char* run_all_tests(){
	test_grid = parse_file_to_grid("test/resources/valid1.puzzle");

	mu_run_test(test_get_cell_index);
	mu_run_test(test_get_cells_row_index);
	mu_run_test(test_get_cells_column_index);
	mu_run_test(test_get_cells_chamber_index);

	if(test_grid){
		free_grid(test_grid);
	}
	return 0;
}