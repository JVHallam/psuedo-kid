#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct myTest{
	int a;
}superFreak;

static char* string_space(char* target_string){
	char* space = malloc(strlen(target_string) + 1);
	strcpy(space, target_string);
	return space;
}

int main(){
	char* a = "This is a test";
	char* b = "this is a test";

	char* arr[] = {a, b};

	char** c = arr;
	for(int i = 0; i < 2; ++i){
		printf("%s\n", *(c++));	
	}

	char* test[] = {
		"This is a test",
		"This is a test"
	};

	puts("Space assigned");

	c = test;
	for(int i = 0; i < 2; ++i){
		printf("%s\n", *(c++));	
	}


	return 0;
}