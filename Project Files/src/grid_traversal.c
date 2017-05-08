#include "../include/grid.h"
#include "../include/grid_traversal.h"
#include <stdlib.h>
#include <stdio.h>

cell*** initialise_new_area_array();

cell*** get_chamber(int chamber_index, cell** grid_start);

cell*** get_row(int row_index, cell** grid_start);

cell*** get_column(int column_index, cell** grid_start);

BOOL is_area_index_valid(int index);

cell** traverse_to_row_start(int index, cell** grid_start);

cell** traverse_to_column_start(int index, cell** grid_start);

cell** traverse_to_chamber_start(int index, cell** grid_start);

cell** traverse_to_areas_cell(int index, int choice, cell** area_start, cell** grid_start);

cell*** initialise_new_area_array(){
	cell*** area_to_return = (cell***)calloc(9, sizeof(cell**));

	for(int cell_index = 0; cell_index < 9; ++cell_index){
		*(area_to_return + cell_index) = 0;
	}

	return area_to_return;
}

cell*** get_chamber(int chamber_index, cell** grid_start){
	cell*** destination_chamber = initialise_new_area_array();
	cell** destination_chamber_start = traverse_to_chamber_start(chamber_index, grid_start);

	if(destination_chamber_start){
		for(int cell_index = 0; cell_index < 9; ++cell_index){
			*(destination_chamber + cell_index) = 	traverse_to_areas_cell(\
													cell_index,\
													CHAMBER,\
													destination_chamber_start,\
													grid_start\
			 									);
		}

		return destination_chamber;
	}
	else{
		return 0;
	}
}

cell*** get_row(int row_index, cell** grid_start){
	cell*** destination_area = initialise_new_area_array();
	cell** destination_row_start = traverse_to_row_start(row_index, grid_start);

	if(destination_row_start){
		for(int cell_index = 0; cell_index < 9; ++cell_index){
			*(destination_area + cell_index) = (destination_row_start + cell_index);
		}

		return destination_area;
	}
	else{
		return 0;
	}
}

cell*** get_column(int column_index, cell** grid_start){
	cell*** destination_area = initialise_new_area_array();
	cell** destination_column_start = traverse_to_column_start(column_index, grid_start);

	if(destination_column_start){
		for(int cell_index = 0; cell_index < 9; ++cell_index){
			*(destination_area + cell_index) = (destination_column_start + (cell_index * 9));
		}
		return destination_area;
	}
	else{
		return 0;
	}
}

BOOL is_area_index_valid(int index){
	if(0 <= index && index <= 9){
		return TRUE;
	}
	else{
		return FALSE;
	}
}


cell** traverse_to_row_start(int index, cell** grid_start){
	if(is_area_index_valid(index)){
		return (grid_start + (index * 9));	
	}
	else{
		return 0;
	}
}


cell** traverse_to_column_start(int index, cell** grid_start){
	if(is_area_index_valid(index)){
		return(grid_start + index);
	}
	else{
		return 0;
	}
}

cell** traverse_to_chamber_start(int index, cell** grid_start){
	if(is_area_index_valid(index)){
		int row = (index / 3) * 3; //This is integer division, so the 3's do not cancel out.
		int column = (index % 3) * 3;
		int cell_offset = (row * 9) + column;

		return (grid_start + cell_offset);
	}
	else{
		return 0;
	}
}

cell** traverse_to_areas_cell(int index, int choice, cell** area_start, cell** grid_start){
	
	if(is_area_index_valid(index) && (0 <= choice && choice <= 3)){
		int offset = 0;
		int col = 0;
		int row = 0;

		switch(choice){
			case ROW:
				offset = (index * 9);
				break;

			case COLUMN:
				offset = index;
				break;

			case CHAMBER:
				col = index % 3;
				row = (index / 3) * 9;
				offset = row + col;
				break;
		}

		cell** destination_cell = area_start + offset;

		if(destination_cell <= grid_start + 80){
			return destination_cell;
		}
		else{
			perror("Out of bounds error in traverse_to_areas_cell");
			return 0;
		}
	}
	else{
		return 0;
	}
}
