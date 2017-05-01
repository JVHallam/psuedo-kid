#!/bin/bash
gcc file_parser_test.c "../src/grid.c" -o my_test;
./my_test "resources/01.puzzle"
