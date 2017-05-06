CFLAGS := -g
CC := gcc

main:
	echo "Nothing";

tests:
	$(CC) $(CFLAGS) "test/grid_tests.c" "src/grid.c" -o "bin/grid_tests";
	./bin/grid_tests;

print_test:
	$(CC) $(CFLAGS) "test/print_grid_tests.c" "src/grid.c" -o "bin/print_test";
	./bin/print_test;
