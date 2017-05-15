#include "../include/hash_table.h"
#include <stdlib.h>

key_list* new_key_list();

grid_table* new_grid_table();

BOOL add_to_table(const char* key, cell** grid_to_add, grid_table* target_table);

void free_table(grid_table* to_free);

value_node** new_value_array();

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
key_list* new_key_list(){
	key_list* current_key_list = (key_list*) malloc(sizeof(key_list));

	current_key_list->head = 0;
	current_key_list->tail = 0;

	return current_key_list;
}

value_node* new_value_node(){
	value_node* current_value_node = (value_node*) malloc(sizeof(value_node));

	current_value_node->key = 0;
	current_value_node->grid = 0;
	current_value_node->next = 0;

	return current_value_node;
}

value_node** new_value_array(){
	value_node** current_value_array = (value_node**) calloc(DEFAULT_ARRAY_SIZE, sizeof(value_node*));
	//Now cycle along the array and initialise all values to zero.

	for(\
		value_node** array_ptr = current_value_array;\
		array_ptr < (current_value_array + DEFAULT_ARRAY_SIZE);\
		++array_ptr
	){
		*array_ptr = 0;
	}

	return current_value_array;
}

grid_table* new_grid_table(){
	grid_table* current_grid_table = (grid_table*) malloc(sizeof(grid_table));

	//Initialise values.
	current_grid_table->keys = new_key_list();
	current_grid_table->size = DEFAULT_ARRAY_SIZE;
	current_grid_table->entries = 0;
	current_grid_table->value_array = new_value_array();

	return current_grid_table;
}

void free_table(grid_table* to_free){
	
	/*
		We must free the table!

		First, the key_list:
			Free each node
			free the list itself.

		Second, the value_node* array:
			Cycle along the table
				if the value isn't null
					free the node

			then free the array

		Finally, free the table.
	*/

}