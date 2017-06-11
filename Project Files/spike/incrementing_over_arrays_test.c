#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int BOOL;


int values_array_length = 12;

int values_array[] = {
	0,
	10,
	20,
	30,
	40,
	50,
	60,
	70,
	80,
	90,
	100,
	110
};

void first_function(){
	int* a = 0;
	int* b = 0;
	int* c = 0;

	int* values_array_end = values_array + values_array_length;

	for(a = values_array; a < values_array_end; ++a){
		for(b = a + 1; b < values_array_end; ++b){
			for(c = b + 1; c < values_array_end; ++c){
				printf("a: %i, b: %i, c: %i\n", *a, *b, *c);
			}
		}
	}
}

void print_pointer_array(int** a, int array_length){
	char level = 'a';

	for(int offset = 0; offset < array_length; ++offset){
		printf("%c: %i, ", (level + offset), **(a + offset));
	}
	printf("\n");
}

void second_function(){

	int* ptr_array[] = {0, 0, 0};

	int* values_array_end = values_array + values_array_length;

	for((ptr_array[0]) = values_array; \
		(ptr_array[0]) < values_array_end; \
		++((ptr_array[0]))){

		for((ptr_array[1]) = (ptr_array[0] + 1); \
			(ptr_array[1]) < values_array_end;\
			++((ptr_array[1]))){

			for((ptr_array[2]) = (ptr_array[1] + 1); \
				(ptr_array[2]) < values_array_end; \
				++((ptr_array[2]))){

				print_pointer_array(&ptr_array[0], 3);
			}

		}

	}

}

void third_function(){

	int* ptr_array[] = {0, 0, 0};

	int* values_array_end = values_array + values_array_length;

	for((ptr_array[0]) = values_array; \
		(ptr_array[0]) < values_array_end; \
		++((ptr_array[0]))){

		int level = 0;

		for((ptr_array[++level]) = (ptr_array[level - 1] + 1); \
			(ptr_array[level]) < values_array_end;\
			++((ptr_array[level]))){

			for((ptr_array[++level]) = (ptr_array[level - 1] + 1); \
				(ptr_array[level]) < values_array_end; \
				++((ptr_array[level]))){

				print_pointer_array(&ptr_array[0], 3);
			}

		}

	}

}

void forloops_fn(	int current_level, int final_level, int* previous, \
					int** ptr_array, int ptr_array_length);

void fourth_function(){
	int* values_array_end = values_array + values_array_length;

	int* ptr_array[] = {0, 0, 0};
	int ptr_array_length = 3;


	int initial_level = 0;
	int final_level = ptr_array_length - 1;
	int* previous = 0;

	forloops_fn(initial_level, final_level, previous, ptr_array, ptr_array_length);

}

void forloops_fn(	int current_level, int final_level, int* previous, \
					int* ptr_array[], int ptr_array_length){
	
	if(!previous){
		previous = values_array;
	}
	else{
		previous = previous + 1;
	}

	int* values_array_end = values_array + values_array_length;

	for(ptr_array[current_level] = previous; \
		ptr_array[current_level] < values_array_end; \
		++(ptr_array[current_level])){

		if(current_level < final_level){
			forloops_fn(	(current_level + 1), final_level, ptr_array[current_level], \
							ptr_array, ptr_array_length);
		}
		else{
			print_pointer_array(ptr_array, ptr_array_length);
		}
	}
}

void set_value(int index, int** ptr_array, int array_length){
	if(index == (array_length - 1) ){
		puts("Yes");
	}
}

void fifth_function(){
	int* values_array_end = values_array + values_array_length;
	int* ptr_array[] = {0, 0, 0};
	int ptr_array_length = 3;

	int initial_level = 0;
	int final_level = ptr_array_length - 1;

	int* previous = values_array;

	for(int level = 0; level < ptr_array_length; ++level){
		ptr_array[level] = previous++;
	}

	/*
		start at the bottom level:
			if we're not on the final level
				if the next level isn't at the end
					go up a level

					increment to the end
						execute purposeful code

				else
					increment the current level

					reset next level
	*/

	int level = initial_level;

	values_array_end = values_array_end - 1;

	print_pointer_array(ptr_array, ptr_array_length);
	while(ptr_array[initial_level] < values_array_end){

		//Are we on the top level
		if( (level != final_level) ){
			//Look up
			//Is it at the end:
			if(ptr_array[level + 1] < values_array_end){
				//Go up there
				++level;
			}
			else{
				//It's at the end.
				//Are we at the end?
				if(ptr_array[level] < values_array_end){
					//Take us to the end
					++ptr_array[level];

					if(ptr_array[level] < values_array_end){
						ptr_array[level + 1] = ptr_array[level];
					}
					else{
						--level;
					}
				}
				else{
					//We're at the end too
					--level;
				}
			}
		}
		else{
			//We're on the final level
			//are we at the end:
			if(ptr_array[level] < values_array_end){
				++ptr_array[level];
				print_pointer_array(ptr_array, ptr_array_length);
			
				//void set_value(int index, int* ptr_array[], int array_length){
				int index = level;				
			}
			else{
				--level;
			}
		}
	}

	puts("Finished:");
	print_pointer_array(ptr_array, ptr_array_length);
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
typedef struct v_array{
	int* values;
	int length;
}value_array;

typedef struct p_array{
	int** pointers;
	int length;
}pointer_array;

void sixth_print_pointer_array(pointer_array* pointers){

	for(int offset = 0; offset < (pointers->length); ++offset){
		//If the pointer is null, don't dereference it.
		if(*(pointers->pointers + offset)){
			printf("%i: %i, ", offset, (**(pointers->pointers + offset)) );
		}
	}

	printf("\n");
}

void sixth_set_value(int* new_value, int index, pointer_array* pointers){
	*(pointers->pointers + index) = new_value;	
	if( (index + 1) == pointers->length){
		sixth_print_pointer_array(pointers);
	}
}

void sixth_function(){
	/*
		Fifth function pretty much nails it bar 1 point:
			When we want the higher level code to execute.

			We need to to execute everytime we set the final value of the array.

			This includes on it's first set.

		How we set the values of the array:
			passing an int pointer.
	*/
	value_array* values = (value_array*) malloc(sizeof(value_array));
	pointer_array* pointers = (pointer_array*) malloc(sizeof(pointer_array));

	int* ptr_array[] = {0, 0, 0};
	int ptr_array_length = 3;

	if(values && pointers){
		values->values = values_array;
		values->length = values_array_length;

		pointers->pointers = ptr_array;
		pointers->length = ptr_array_length;

		//Initialise the ptr_array.
		for(int level = 0; level < pointers->length; ++level){
			int* new_value = values->values + level;
			sixth_set_value( new_value, level, pointers);
		}

		//Just repeat what we've already written in fifth function.
		//=-=-=-=-=-=-=-=-=-=-=-=-=-

		int* values_array_end = values->values + (values->length - 1);

		const int initial_level = 0;

		int level = initial_level;
		int top_level = (pointers->length) - 1;

		while(*(pointers->pointers) < values_array_end){
			//Are we on the top level?
			if(level < top_level){

				//If the level above ISN'T at the end
				if( *(pointers->pointers + level + 1) < values_array_end){
					//Go up to it
					++level;
				}
				else{
					//The level above is at the end

					//If the current level isn't at the end
					if( *(pointers->pointers + level) < values_array_end ){

						//first check if the level above is at the end
						if( *(pointers->pointers + level ) < values_array_end){
							//==-=-=-=-=-=-=-Problem code

							//Increment us by 1
							int* second_new_value = *(pointers->pointers + level) + 1;	
							sixth_set_value(second_new_value, level, pointers);

							//set the level above to be 1 past us
							int* new_value = *(pointers->pointers + level) + 1;
							sixth_set_value(new_value, level + 1, pointers);
							
							//Then go up
							++level;
							//==-=-=-=-=-=-=-Problem code
						}
						else{
							//Leave the level above us at the end, go down a level.
							--level;
						}
					}
					else{
						//We're at the end too. So go down a level.
						--level;
					}
				}
			}
			else{
				//We're on the top level

				//If we're not at the end, move us along 1.
				if(*(pointers->pointers + level) < values_array_end){
					int* new_value = *(pointers->pointers + level) + 1;
					sixth_set_value(new_value, level, pointers);
				}
				else{
					//Go down a level.
					--level;
				}
			}
		}


		//=-=-=-=-=-=-=-=-=-=-=-=-=-
		free(values);
		values = 0;
		free(pointers);
		pointers = 0;
	}
	else{
		printf("Failed to initialise values or pointers.\n");
	}

}
//void sixth_set_value(int* new_value, int index, pointer_array* pointers)

//In this case, index is level
void increment_target(int index, pointer_array* pointers, value_array* values){
	//void sixth_print_pointer_array(pointer_array* pointers)
	//sixth_print_pointer_array(pointers);

	int* values_array_end = (values->values + (values->length - 1));

	int* new_value = (*(pointers->pointers + index)) + 1;

	for(int offset = index; offset < pointers->length; ++offset){

		if( new_value <= values_array_end ){
			sixth_set_value(new_value, offset, pointers);	
		}

		new_value = (*(pointers->pointers + offset)) + 1;		
	}
}

//This function worked brilliantly, with no usage of recursion.
void seventh_function(){

	value_array* values = (value_array*) malloc(sizeof(value_array));
	pointer_array* pointers = (pointer_array*) malloc(sizeof(pointer_array));

	int* values_array_end = values->values + (values->length - 1);

	int* ptr_array[] = {0, 0, 0, 0};
	int ptr_array_length = 4;

	if(values && pointers){
		values->values = values_array;
		values->length = values_array_length;

		pointers->pointers = ptr_array;
		pointers->length = ptr_array_length;

		//Initialise the ptr_array=-=-=-==-=-=-=-
		//Risky, i know. Setting the first value to before the values array.
		//But it works.
		sixth_set_value( values->values -1, 0, pointers);
		increment_target(0, pointers, values);
		//=-=-Initialisation end=-=-=-=-=-

		int* values_array_end = values->values + (values->length - 1);

		int level = 0;
		int top_level = (pointers->length) - 1;

		//The super problematic code begins!
		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

		//While the first level isn't at the end
		while(*(pointers->pointers) < values_array_end){

			//If we're not the top level
			if(level != top_level){

				//check if the level above us is at the end
				if(*(pointers->pointers + level + 1) == values_array_end){

					//Increment ourselves.
					increment_target(level, pointers, values);

					//If we're at the end now.
					if(*(pointers->pointers + level) == values_array_end){
						//Go down a level
						--level;
						continue;
					}
					else{
						continue;
					}
				}
				else{
					//It's not at the end, so go up there.
					++level;
					//Start again.
					continue;
				}
			}
			else{
				//It is the top level
				while(*(pointers->pointers + level) < values_array_end){
					increment_target(level, pointers, values);
				}

				//Go back down
				--level;
			}
		}
		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		free(values);
		values = 0;
		free(pointers);
		pointers = 0;
	}
	else{
		printf("Failed to initialise values or pointers.\n");
	}
}

void eighth_function(){

	value_array* values = (value_array*) malloc(sizeof(value_array));
	pointer_array* pointers = (pointer_array*) malloc(sizeof(pointer_array));

	int* values_array_end = values->values + (values->length - 1);

	int* ptr_array[] = {0, 0, 0, 0};
	int ptr_array_length = 4;

	if(values && pointers){
		values->values = values_array;
		values->length = values_array_length;

		pointers->pointers = ptr_array;
		pointers->length = ptr_array_length;

		//Initialise the ptr_array=-=-=-==-=-=-=-
		//Risky, i know. Setting the first value to before the values array. But it works.
		sixth_set_value( values->values -1, 0, pointers);
		increment_target(0, pointers, values);

		int* values_array_end = values->values + (values->length - 1);

		int level = 0;
		int top_level = (pointers->length) - 1;

		while(*(pointers->pointers) < values_array_end){
			
			if( (*(pointers->pointers + level)) == values_array_end){
				--level;
			}
			else{
				//Our current level isn't at the end.

				//If we're not at the top and the value above us isn't at the end.
				if( 
					(level < top_level) && \
					(*(pointers->pointers + level + 1) != values_array_end)
				){
					++level;
				}
				else{
					//We are at the top and are being evaluated by the first statement
					//or we're not at the top but the level above us is at the end.
					increment_target(level, pointers, values);
				}
			}
		}
		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		free(values);
		values = 0;
		free(pointers);
		pointers = 0;
	}
	else{
		printf("Failed to initialise values or pointers.\n");
	}
}

int main(){
	eighth_function();

	return 0;
}

