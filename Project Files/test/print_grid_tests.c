#include <stdio.h>
#include "../include/grid.h"

int main(){
	cell** test_grid = parse_file_to_grid("test/resources/valid1.puzzle");

	if(test_grid != 0){

		print_grid_values(test_grid);

		print_grid_occupied(test_grid);

		print_grid_valid_values(test_grid);

		free_grid(test_grid);

	}
	else{
		puts("Failed to parse file");
	}

	return 0;
}