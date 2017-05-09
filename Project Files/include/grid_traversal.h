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

#endif