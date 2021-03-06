#ifndef LOGIC_H_
#define LOGIC_H_

#include "grid.h"
#include "constants.h"

//Gets the cells index in the grid, relative to the first cell
int get_cell_index(cell** target_cell, cell** grid_start);

//Gets the index of the row the cell is in
int get_cells_row_index(cell** target_cell, cell** grid_start);

//gets the index of the column that the cell is in
int get_cells_column_index(cell** target_cell, cell** grid_start);

//Gets the index of the chamber that the cell is in
int get_cells_chamber_index(cell** target_cell, cell** grid_start);

//Check if a value is present in an area, and then return TRUE / FALSE
BOOL is_present(cell*** given_area, int value);

//Updates the valid_values of every cell in a grid.
//If a cell has a value That is non-zero, set all of it's valid values to FALSE
void set_all_valid_values(cell** grid_start);

//Takes a cell that has just had it's value changed. It then updates the row, column and chamber
//That this cell is in and updates the valid_values list for all cells in these areas.
void update_surrounding_areas(cell** target_cell, cell** grid_start);

//A puzzle is thought to be complete when all cells contain values from 1 to 9.
BOOL is_puzzle_complete(cell** grid_start);

#endif