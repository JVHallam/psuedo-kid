#!/bin/bash

new_module=$1;

if [ $1 ]
then
	new_module=$1;
	header_file="include/$1.h"
	source_file="src/$1.c";
	test_file="test/$1_test.c";
	output_executable="bin/$1_test";

	if [ -f $header_file ] || [ -f $source_file ] || [ -f test_file ];
	then
		echo "A module by the name of $new_module already exists.";
	else
		#Create the header file:
		upper="${new_module^^}_H_";
		echo "#ifndef $upper" >> $header_file;
		echo "#define $upper" >> $header_file;
		echo "" >> $header_file;
		echo "#endif" >> $header_file;

		#Create the source file:
		echo '#include "../'$header_file'"' >> $source_file;

		#create the test file:
		echo '#include "../'$header_file'"' >> $test_file;

		#add the test to the makefile
		echo "" >> makefile;
		echo "$1_test:" >> makefile;
		echo '	$(CC) $(CFLAGS) "'$test_file'" "'$source_file'" -o "'$output_executable'"' >> makefile;
		echo "	./$output_executable" >> makefile;

		#Need to add that test to the run_tests.sh script
		echo "$1_test" >> test_list.txt

		#Open in sublime so that i know that we've made the files
		subl $header_file $source_file $test_file;
	fi
else
	echo "No args given for the new module";
fi
