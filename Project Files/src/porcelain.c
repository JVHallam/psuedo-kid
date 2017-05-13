#include "../include/porcelain.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

key_list* new_key_list();

key_node* new_key_node(const char* key);

//First we need a linked list to hold the keys


key_node* new_key_node(const char* key){
	key_node* current_node = malloc(sizeof(key_node));

	current_node->key = key;
	current_node->next = 0;

	return current_node;
}



key_list* new_key_list(){
	key_list* current_list = malloc(sizeof(key_list));

	current_list->head = 0;
	current_list->tail = 0;

	return current_list;
}

