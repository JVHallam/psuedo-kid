CFLAGS := -g
CC := gcc

tests:
	$(CC) $(CFLAGS) "test/grid_tests.c" "src/grid.c" -o "bin/grid_tests";
main:
	echo "Nothing";

grid_test:
	$(CC) $(CFLAGS) "test/grid_tests.c" "src/grid.c" -o "bin/grid_tests";
	./bin/grid_tests;

print_test:
	$(CC) $(CFLAGS) "test/print_grid_tests.c" "src/grid.c" -o "bin/print_test";
	./bin/print_test;

traversal_test:
	$(CC) $(CFLAGS) "test/grid_traversal_test.c" "src/grid_traversal.c" "src/grid.c" -o "bin/grid_traversal_test";
	./bin/grid_traversal_test;
