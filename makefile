all: 
	gcc main.c "psuedokid/psuedokid.c" "traversal/traversal.c" "logic/logic.c" -o main -g; 
	./main;
