#include "../include/hash_table.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//Funciton declarations and global variables:

grid_table* all_grids;

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

key_node* new_key_node(const char* key){
	key_node* current_node = malloc(sizeof(key_node));
	//Check if malloc returned null.
	if(current_node != 0){
		current_node->key = key;
		current_node->next = 0;
	}
	else{
		perror("Malloc failed to assign space for this key node.\n");
	}
	return current_node;
}

key_list* new_key_list(){
	key_list* current_list = malloc(sizeof(key_list));

	if(current_list){
		current_list->head = 0;
		current_list->tail = 0;
	}
	else{
		perror("No value was given from malloc in new_key_list");
	}

	return current_list;
}

cell*** new_table_array(int table_size){
	cell*** current_table = calloc(table_size, sizeof(cell**));

	cell*** table_pointer = current_table;
	for(int i = 0; i < table_size; ++i){
		*table_pointer = 0;
		++table_pointer;
	}

	return current_table;
}

grid_table* new_grid_table(){
	int default_table_size = 100;
	grid_table* current_table = malloc(sizeof(grid_table));

	current_table->grid_array = new_table_array(default_table_size);

	current_table->table_size = default_table_size;

	current_table->keys = new_key_list();

	return current_table;
}

void append_list(const char* key, key_list* current_list){
	key_node* next_node = new_key_node(key);
	
	//Check there is a list.
	if(current_list->head && current_list->tail){
		current_list->tail->next = next_node;
		current_list->tail = next_node;
	}
	else{
		//Else, start the list.
		current_list->head = current_list->tail = next_node;
	}
}

