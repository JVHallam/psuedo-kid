#ifndef LOGIC_H_
#define LOGIC_H_

//Returns either TRUE or FALSE based on whether a value is present in an area.
BOOL is_present(int value, int **area);

//returns TRUE or FALSE based on whether a zero value is found in an area.
BOOL is_full(int **area);

//Return TRUE or FALSE based on whether a cell is suitable to hold a value.
BOOL is_appropriate(int *cell, int value, int* grid_start);

//Goes over an area, if it changes a value, it return TRUE. Else, returns false.
BOOL solve_area(int *cell, int choice, int* grid_start);

#endif