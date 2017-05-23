#include "../include/logic.h"
#include "../include/constants.h"
#include "../include/grid_traversal.h"

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
			return TRUE;
		}
	}
	return FALSE;
}

void set_valid_values_using_area(cell** target_cell, cell*** area_ptr){
	for(int index = 0; index < 9; ++index){
		int cell_value = (**area_ptr)->value;
		if(cell_value){
			(*target_cell)->valid_values[(cell_value - 1)] = FALSE;
		}
		++area_ptr;
	}
}

void set_all_cells_valid_values(cell** target_cell, cell** grid_start){
	//Get the row, cell and chamber index;
	int row_index = get_cells_row_index(target_cell, grid_start);
	int column_index = get_cells_column_index(target_cell, grid_start);
	int chamber_index = get_cells_chamber_index(target_cell, grid_start);

	//Get the areas.
	cell*** cells_row = get_row(row_index, grid_start);
	cell*** cells_column = get_column(column_index, grid_start);
	cell*** cells_chamber = get_chamber(chamber_index, grid_start);

	//Now we have the areas, we must set the valid values up.
	set_valid_values_using_area(target_cell, cells_row);
	set_valid_values_using_area(target_cell, cells_column);
	set_valid_values_using_area(target_cell, cells_chamber);

	//Free the Areas.
	free(cells_row);
	free(cells_column);
	free(cells_chamber);
}

void set_all_valid_values(cell** target_grid){
	for(cell** target_cell = target_grid; target_cell < (target_grid + 81); ++target_cell){
		set_all_cells_valid_values(target_cell, target_grid);
	}
}