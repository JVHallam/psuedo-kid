CFLAGS := -g
CC := gcc

all: 
	gcc "src/main.c" "src/psuedokid.c" "src/traversal.c" "src/logic.c" -o "bin/main" -g; 

tests:
	$(CC) $(CFLAGS) "test/traversal test.c" "src/traversal.c" -o "bin/traversal test";
