#include "../include/logic.h"
#include "../include/constants.h"

int get_cell_index(cell** target_cell, cell** grid_start){
	return target_cell - grid_start;
}

int get_cells_row_index(cell** target_cell, cell** grid_start){
	int cell_index = get_cell_index(target_cell, grid_start);

	return (cell_index / 9);
}

int get_cells_column_index(cell** target_cell, cell** grid_start){
	int cell_index = get_cell_index(target_cell, grid_start);

	return (cell_index % 9);
}

int get_cells_chamber_index(cell** target_cell, cell** grid_start){
	int row_index = get_cells_row_index(target_cell, grid_start);
	int column_index = get_cells_column_index(target_cell, grid_start);

	return (((row_index / 3) * 3) + (column_index / 3));
}

BOOL is_present(cell*** test_area, int value){

	for(int index = 0; index < 9; ++index){
		cell*** current_cell = test_area + index;

		if( (**current_cell)->value == value){
			return FALSE;
		}
	}
	
	return TRUE;
}