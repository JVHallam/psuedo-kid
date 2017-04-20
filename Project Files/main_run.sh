#!/bin/bash

make;

for file in doc/puzzles/*.puzzle
do
	./bin/main $file;
done

