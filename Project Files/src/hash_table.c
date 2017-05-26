#include "../include/hash_table.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define FNV_PRIME_32 16777619
#define FNV_OFFSET_32 2166136261U

uint32_t FNV32(const char *s);

key_list* new_key_list();

key_node* new_key_node(const char* key_to_set);

value_node* new_value_node();

value_node** new_value_array();

grid_table* new_grid_table();

void free_key_list(key_list* to_free);

void free_value_node_chain(value_node* to_free);

void free_value_array(value_node** to_free);

void free_table(grid_table* to_free);

BOOL add_to_table(const char* key, cell** grid_to_add, grid_table* target_table);

cell** get_from_table(const char* key, grid_table* target_table);

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
uint32_t FNV32(const char *s){

    uint32_t hash = FNV_OFFSET_32, i;
    for(i = 0; i < strlen(s); i++)
    {
        hash = hash ^ (s[i]); // xor next byte into the bottom of the hash
        hash = hash * FNV_PRIME_32; // Multiply by prime number found to work well
    }
    return hash;
} 

key_list* new_key_list(){
	key_list* current_key_list = (key_list*) malloc(sizeof(key_list));

	current_key_list->head = 0;
	current_key_list->tail = 0;

	return current_key_list;
}

key_node* new_key_node(const char* key_to_set){
	key_node* current_key_node = (key_node*) malloc(sizeof(key_node));
	current_key_node->key = key_to_set;
	current_key_node->next = 0;

	return current_key_node;
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

void free_key_list(key_list* to_free){
	//Cycle through it, freeing each key node.
	key_node* node_ptr = to_free->head;
	key_node* next_ptr = 0;

	while(node_ptr){
		next_ptr = node_ptr->next;
		free(node_ptr);
		node_ptr = next_ptr;
	}

	free(to_free);
}

void free_value_node_chain(value_node* to_free){
	//Free the cell** grid, then free it itself and move on.
	value_node* current = to_free;

	//If there's a value at current.
	while(current){
		value_node* next_in_line = current->next;

		if(current->grid){
			free_grid(current->grid);
		}
		free(current);
		current = next_in_line;
	}
}


void free_value_array(value_node** to_free){
	/*
		Cycle along the array
		If there's a node that's not null, free it.	
	*/

	for(\
		value_node** array_ptr = to_free;\
		array_ptr < (to_free + DEFAULT_ARRAY_SIZE);\
		++array_ptr
	){
		if(*array_ptr){
			free_value_node_chain(*array_ptr);
		}
	}

	free(to_free);
}

void free_table(grid_table* to_free){
	free_key_list(to_free->keys);

	free_value_array(to_free->value_array);

	free(to_free);
}

void append_key_list(key_list* target_list, const char* key){
	key_node* new_key = new_key_node(key);

	//If we have an entry, it's business as normal.
	if(target_list->head){
		target_list->tail->next = new_key;
	}
	else{
		//Initialise head.
		target_list->head = new_key;
	}

	//Aim tail back to the end of the list.
	target_list->tail = new_key;
}

BOOL is_key_present(grid_table* target_table, const char* key){
	//Trawl list to see if the key is present
	key_node* walker = target_table->keys->head;

	BOOL is_value_present = FALSE;

	while(walker){
		if( strcmp(walker->key, key) == 0){
			is_value_present = TRUE;
			break;
		}
		walker = walker->next;
	}

	return is_value_present;
}

//Returns true if added to table, else, returns false.
BOOL add_to_table(const char* key, cell** grid_to_add, grid_table* target_table){
	/*
		Trawling through the key_list is an extremely slow way to validate
		if a key is already in use on the table. But it's the best approach i 
		currently have. Other than hashing the key, going to the location and seeing
		if key is already present.
	*/

	if(!is_key_present(target_table, key)){
		value_node* newest_value_node = new_value_node();
		newest_value_node->key = key;
		newest_value_node->grid = grid_to_add;

		append_key_list(target_table->keys, key);

		uint32_t hash_value = FNV32(key);
		int index = hash_value % (target_table->size);

		//Go to the given index:
		value_node** destination = (target_table->value_array + index);

		//If there's a collision, resolve it.
		if(*destination){
			value_node* head = *destination;

			value_node* walker = head;
			while(walker->next){
				walker = walker->next;
			}

			walker->next = newest_value_node;
		}
		else{
			*destination = newest_value_node;
		}
		return TRUE;
	}
	else{
		//Key is already present.
		return FALSE;
	}


}

cell** get_from_table(const char* key, grid_table* target_table){
	cell** desired_value = 0;

	//Reject null keys
	if(key){
		uint32_t keys_hash = FNV32(key);

		int index = keys_hash % target_table->size;

		value_node** destination = (target_table->value_array) + index;

		

		if(*destination){
			value_node* head = *destination;
			value_node* walker = head;

			//While the keys don't match && there's another value in the chain.
			while( (strcmp(walker->key, key) != 0) && walker->next){
				walker = walker->next;
			}

			//Check the keys.
			if(strcmp(walker->key, key) == 0){
				desired_value = walker->grid;
			}
		}
	}
	
	//else, it's just null.
	return desired_value;
}