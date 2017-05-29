CFLAGS := -g
CC := gcc

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

logic_test:
	$(CC) $(CFLAGS) "test/logic_test.c" "src/logic.c" "src/grid.c" "src/grid_traversal.c" -o "bin/logic_test";
	./bin/logic_test;


hash_table_test:
	$(CC) $(CFLAGS) "test/hash_table_test.c" "src/hash_table.c" "src/grid.c" -o "bin/hash_table_test"
	./bin/hash_table_test

porcelain_test:
	$(CC) $(CFLAGS) "test/porcelain_test.c" \
	"src/porcelain.c" \
	"src/hash_table.c" \
	"src/grid.c" \
	"src/logic.c" \
	"src/grid_traversal.c" \
	-o "bin/porcelain_test"
	./bin/porcelain_test

algorithms_test:
	$(CC) $(CFLAGS) "test/algorithms_test.c" \
	"src/algorithms.c" \
	"src/porcelain.c" \
	"src/hash_table.c" \
	"src/grid.c" \
	"src/logic.c" \
	"src/grid_traversal.c" \
	-o "bin/algorithms_test";
	./bin/algorithms_test
