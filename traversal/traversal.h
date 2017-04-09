#ifndef TRAVERSAL_H_
#define TRAVERSAL_H_

//Traverse to the start of the choice, of index number "index".
int* grid_traverse(int choice, int index, int* grid_start);

//Return the pointer to the cell at the start of choice, in the current area.
int* get_area_start(int* current_cell, int choice, int* grid_start);

//Calls Calloc, creates a 9 x 1 array containing pointers to each cell in given area.
int** get_area(int *cell, int choice, int *grid_start);

#endif