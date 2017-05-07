#ifndef GRID_TRAVERSAL_H_
#define GRID_TRAVERSAL_H_

//So this is the file used to traverse the grids given by grid.h

//It should return an array to the areas needed.

//Traverse to chamber, row, column.

//Calls to malloc to create  9 x 1 array of pointers.
//Can be cleaned up just using free()
cell*** get_chamber(int chamber_index, cell** grid_start);

cell*** get_column(int column_index, cell** grid_start);

cell*** get_row(int row_index, cell** grid_start);

//cell** traverse_to_areas_cell(int index, int choice, cell** area_start, cell** grid_start);

//If you make calls to get_chamber, get_column or get_row, call this function to clean them up.
void free_area(cell** area);

BOOL is_area_index_valid(int index);

cell** traverse_to_row_start(int index, cell** grid_start);

cell** traverse_to_column_start(int index, cell** grid_start);

cell** traverse_to_chamber_start(int index, cell** grid_start);

//Calls to malloc to create empty 9 x 1 array, can be cleaned up after by using free()
cell*** initialise_new_area_array();

#endif