#!/bin/bash
#Global Variables:
test_list=( "grid_test" "traversal_test" "logic_test" "porcelain_test");
declare -i failed_tests_total=0;
console_output_file="console_output.txt";
failed_tests_file="failed_tests.txt";

#Functions
function failed_test {
	echo " > $1" >> $failed_tests_file;
	((failed_tests_total++));
}

function run_test {
	make $1 &>> $console_output_file;
	if [ $? != 0 ]
	then
		failed_test $1;
	fi
}

#Main:

#Set up the 2 output files:
if [ -e $console_output_file ]
then
	rm $console_output_file;
fi

if [ -e $failed_tests_file ]
then 
	rm $failed_tests_file;
fi
touch $failed_tests_file;

#Run tests:
#for test in "${test_list[@]}"
#do
#	run_test $test;
#done
if [ -e test_list.txt ]
then
	while read current_test
	do
		run_test $current_test;
	done < test_list.txt;
else
	echo "test_list.txt wasn't found. Please provide it containing the list of tests to be run.";
	exit;
fi

#If any failed
if [ $failed_tests_total != 0 ]
then
	echo "Number of failed tests = $failed_tests_total";
	echo "Tests that failed:";
	cat failed_tests.txt;
else
	echo "All tests completed without errors!";
fi
