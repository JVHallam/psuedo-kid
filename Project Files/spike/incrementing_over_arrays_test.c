#include <stdio.h>
#include <stdlib.h>

int values_array_length = 9;

int values_array[] = {
	0,
	10,
	20,
	30,
	40,
	50,
	60,
	70,
	80
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
	for(int offset = 0; offset < pointers->length; ++offset){
		char current_char = 'a' + offset;
		printf("%c: %i, ", current_char, (**(pointers->pointers + offset)) );
	}

	printf("\n");
}

void sixth_set_value(int* new_value, int index, pointer_array* pointers){
	*(pointers->pointers + index) = new_value;

	sixth_print_pointer_array(pointers);

	//If it's the final pointer in the array.
	
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

		int level = 0;
		while(*(pointers->pointers) < values_array_end){
			//Are we on the top level?
			if(level != pointers->length){

				//Is the level above us at the end?
				if( *(pointers->pointers + level + 1) < values_array_end){
					//Go on up.
					++level;
				}
				else{
					//It's at the end
					//Is the current level at the end
					if( *(pointers->pointers + level) < values_array_end ){
						//Take us to the end.
						int* new_value = *(pointers->pointers + level) + 1;	
						sixth_set_value(new_value, level, pointers);

						if( *(pointers->pointers + level + 1) < values_array_end){
							*(pointers->pointers + level + 1) = *(pointers->pointers + level);
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
				if(*(pointers->pointers + level) < values_array_end){
					int* new_value = *(pointers->pointers + level) + 1;
					sixth_set_value(new_value, level, pointers);
				}
				else{
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


int main(){
	sixth_function();

	return 0;
}

