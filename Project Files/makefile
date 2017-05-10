CFLAGS := -g
CC := gcc

main:
	echo "Nothing";

all_test:
	make grid_test; ./bin/grid_tests;
	make traversal_test; ./bin/traversal_test;
	make logic_test; ./bin/logic_test;

grid_test:
	$(CC) $(CFLAGS) "test/grid_tests.c" "src/grid.c" -o "bin/grid_tests";
	./bin/grid_tests;

print_test:
	$(CC) $(CFLAGS) "test/print_grid_tests.c" "src/grid.c" -o "bin/print_test";
	./bin/print_test;

traversal_test:
	$(CC) $(CFLAGS) "test/grid_traversal_test.c" "src/grid_traversal.c" "src/grid.c" -o "bin/grid_traversal_test";
	./bin/grid_traversal_test;

logic_test:
	$(CC) $(CFLAGS) "test/logic_test.c" "src/logic.c" "src/grid.c" "src/grid_traversal.c" -o "bin/logic_test";
	./bin/logic_test;
