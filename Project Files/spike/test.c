#include <stdio.h>


int* foo(){
	int holder[3] = {1, 2, 3};

	return holder;
}

int main(){
	int* a;

	a = foo();

	return 0;
}