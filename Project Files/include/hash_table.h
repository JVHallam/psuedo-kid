#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "../include/constants.h"
#include "../include/grid.h"

typedef struct k_node{
	const char* key;
	struct k_node* next;
}key_node;

typedef struct k_list{
	key_node* head;
	key_node* tail;
}key_list;

//A hash table containing all of the grid's we're currently using.
typedef struct hash_table{
	//An array of grid pointers. Each grid being a cell**
	cell*** grid_array;

	//The length of the table.
	int table_size;

	//A linked list containing the list of keys.
	key_list* keys;
 }grid_table;

//Returns TRUE if the puzzle was added to the table
BOOL new_puzzle(const char* file_name);

key_node* new_key_node(const char* key);

//returns a key_list* that has head and tail set to zero.
key_list* new_key_list();

cell*** new_table_array(int table_size);

grid_table* new_grid_table();

void append_list(const char* key, key_list* current_list);

#endif
