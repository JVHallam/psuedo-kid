#ifndef PROCELAIN_H_
#define PROCELAIN_H_

#include "../include/constants.h"

typedef struct k_node{
	const char* key;
	struct key_node* next;
}key_node;

typedef struct k_list{
	key_node* head;
	key_node* tail;
}key_list;

//Returns TRUE if the puzzle was added to the table
BOOL new_puzzle(const char* file_name);

key_list* new_key_list();

key_node* new_key_node(const char* key);

#endif