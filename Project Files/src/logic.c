#include "../include/logic.h"
#include "../include/constants.h"
#include "../include/grid_traversal.h"

#include <stdio.h>

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

void update_areas_valid_values(int value, cell*** target_area){
	for(cell*** area_ptr = target_area; area_ptr < (target_area + 9); ++area_ptr){
		(**(area_ptr))->valid_values[value - 1] = FALSE;
	}
}

void update_row(cell** target_cell, cell** grid_start){
	int target_row_index = get_cells_row_index(target_cell, grid_start);

	cell*** target_area = get_row(target_row_index, grid_start);

	update_areas_valid_values((*target_cell)->value, target_area);
}

void update_column(cell** target_cell, cell** grid_start){
	int target_column_index = get_cells_column_index(target_cell, grid_start);

	cell*** target_area = get_column(target_column_index, grid_start);

	update_areas_valid_values((*target_cell)->value ,target_area);
}

void update_chamber(cell** target_cell, cell** grid_start){
	int target_chamber_index = get_cells_chamber_index(target_cell, grid_start);

	cell*** target_area = get_chamber(target_chamber_index, grid_start);

	update_areas_valid_values((*target_cell)->value, target_area);
}

void update_surrounding_areas(cell** target_cell, cell** grid_start){
	update_row(target_cell, grid_start);

	update_column(target_cell, grid_start);

	update_chamber(target_cell, grid_start);
}

BOOL is_puzzle_complete(cell** grid_start){
	BOOL has_completed_puzzle = TRUE;

	for(cell** grid_ptr = grid_start; grid_ptr < (grid_start + 81); ++grid_ptr){
		int cell_value = (*grid_ptr)->value;

		//If it's a completed cell
		if(1 <= cell_value && cell_value <= 9){
			continue;
		}
		else{ //It's not a completed cell, thus the grid isn't completed.
			has_completed_puzzle = FALSE;
			break;
		}
	}

	return has_completed_puzzle;
}