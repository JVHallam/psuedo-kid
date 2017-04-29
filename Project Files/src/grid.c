#include "../include/grid.h"
#include <stdlib.h>

/*
typedef struct cstruct{
	int value;

	int occupied;
	
	BOOL valid_values[9];
}cell;
*/

//Calls Malloc
cell* new_cell(){
	cell* created_cell = (cell*)malloc(sizeof(cell));

	created_cell->value = 0;

	created_cell->occupied = 0;

	for(int index = 0; index < 9; ++index){
		created_cell->valid_values[index] = TRUE;
	}

	return created_cell;
}


cell** new_grid(){
	cell** created_grid = (cell**)calloc((9 * 9), sizeof(cell*));

	//Initialise the grid

	for(cell** grid_ptr = created_grid; grid_ptr < (created_grid + 81); ++grid_ptr){
		*grid_ptr = new_cell();
	}

	return created_grid;
}

void free_grid(cell** grid_start){
	for(cell** grid_ptr = grid_start; grid_ptr < (grid_start + 81); ++grid_ptr){
		//Free each cell
		free(*grid_ptr);
	}
	free(grid_start);
}
