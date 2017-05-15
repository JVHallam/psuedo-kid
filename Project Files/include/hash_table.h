#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "../include/grid.h"
#include "../include/constants.h"
#include <stdint.h>

#define DEFAULT_ARRAY_SIZE 101

typedef struct k_node{
	const char* key;
	struct k_node* next;
}key_node;

typedef struct k_list{
	key_node* head;
	key_node* tail;
}key_list;

typedef struct v_node{
	const char* key;
	cell** grid;
	struct v_node* next;
}value_node;

//default size for the table should be 101 if using linear probing.
typedef struct g_table{
	key_list* keys;

	int size;

	//Store the number of entries so far
	int entries;

	//Array of value_node*
	value_node** value_array;
}grid_table;

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Create a new table, defaulting it's size
grid_table* new_grid_table();

//Frees all values.
void free_table(grid_table* to_free);

//adds a new grid to the table, stores it's key and returns TRUE/FALSE based on whether or not
//it was added.
BOOL add_to_table(const char* key, cell** grid_to_add, grid_table* target_table);

//returns a cell** from the table, based on the key.
cell** get_from_table(const char* key, grid_table* target_table);

//That hashing algorithm i found online somewhere.
uint32_t FNV32(const char *s);


#endif
