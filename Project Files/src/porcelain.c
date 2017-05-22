#include "../include/porcelain.h"
#include "../include/hash_table.h"
#include "../include/grid.h"

static grid_table* puzzle_container = 0;

void initalise_puzzle_container(){
	puzzle_container = new_grid_table();
}

void porcelain_cleanup(){
	if(puzzle_container){
		free_table(puzzle_container);
	}
}

BOOL new_puzzle(char* file_name){
	if(!puzzle_container){
		initalise_puzzle_container();
	}
	
	cell** current_grid = parse_file_to_grid(file_name);

	grid_table* quick_test = new_grid_table();

	if(current_grid){
		return add_to_table(file_name, current_grid, puzzle_container);
	}
	else{
		return FALSE;
	}
}

