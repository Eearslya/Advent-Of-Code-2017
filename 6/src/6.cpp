#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <sys/time.h>
#include "6.h"

int main(void) {
	std::string input, solution_one, solution_two;
	double time_elapsed_one, time_elapsed_two;

	input = read_input();

	start_timer();
	solution_one = part_one(input);
	time_elapsed_one = stop_timer();
	
	start_timer();
	solution_two = part_two(input);
	time_elapsed_two = stop_timer();

	std::cout << "Solution One: " << solution_one;
	std::cout << " (took " << time_elapsed_one << "ms)" << std::endl;
	std::cout << "Solution Two: " << solution_two;
	std::cout << " (took " << time_elapsed_two << "ms)" << std::endl;

	return 0;
}

// Parts 1 and 2 are similar enough to use the same function for both parts.
std::string solve(std::string input, int part) {
	MemoryBank memory;
	int bankValue;
	std::stringstream ssInput(input);
	std::set<std::list<unsigned int>> pastMemory;
	std::list<unsigned int> duplicateBank;
	while (ssInput >> bankValue) {
		memory.banks.push_back(bankValue);
	}
	memory.cycle();
	int cycles{1};
	// Attempt to insert the current bank state into the set,
	// which will fail if it is not unique.
	while (pastMemory.insert(memory.banks).second) {
		memory.cycle();
		cycles++;
	}
	if (part == 2) {
		// For part 2, carry on until we reach the duplicate state again.
		duplicateBank = memory.banks;
		memory.cycle();
		cycles = 1;
		while (memory.banks != duplicateBank) {
			memory.cycle();
			cycles++;
		}
	}
	return std::to_string(cycles);
}

std::string part_one(std::string input) {
	return solve(input, 1);
}

std::string part_two(std::string input) {
	return solve(input, 2);
}

void MemoryBank::cycle(void) {
	std::list<unsigned int>::iterator max{banks.begin()};
	// Find the largest value memory bank
	for (auto it = banks.begin(); it != banks.end(); it++) {
		if (*it > *max) {
			max = it;
		}
	}
	auto it = max;
	unsigned int toDistribute = *it;
	*it = 0;
	// Redistribute it amongst the other memory banks
	while (toDistribute > 0) {
		it++;
		// Loop around if we reach the end of the list
		if (it == banks.end()) {
			it = banks.begin();
		}
		(*it)++;
		toDistribute--;
	}
}

// Helper functions

void start_timer() {
	gettimeofday(&timer_start, NULL);
}

double stop_timer() {
	double milliseconds;
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	milliseconds = (current_time.tv_sec - timer_start.tv_sec) * 1000.0;
	milliseconds += (current_time.tv_usec - timer_start.tv_usec) / 1000.0;
	return milliseconds;
}

std::string read_input() {
	std::ifstream inputFile;
	std::string input;
	inputFile.open("input");
	getline(inputFile, input);
	inputFile.close();
	return input;
}
/*
    char *input;
	FILE *input_file;
	int i;
	long input_len;
	size_t read_bytes;

	input_file = fopen("input", "r");
	if (input_file == NULL) {
		fatal("Please put your puzzle input in a file called \"input\" (case-sensitive) in the same folder as the program.\n");
	}
	
	// Find the file's length by seeking to the end...
	fseek(input_file, 0, SEEK_END);
	// ...and seeing where we end up.
	input_len = ftell(input_file);
	rewind(input_file);
	
	input = (char*) malloc(sizeof(char) * input_len);
	if (input == NULL) {
		fatal("Out of memory!");
	}
	
	read_bytes = fread(input, sizeof(char), input_len, input_file);
	if (read_bytes != input_len) {
		fatal("Error reading input file!");
	}
	
	fclose(input_file);
	
	// Strip trailing newlines, carriage returns, and spaces from the input.
	for (i = (input_len - 1); i >= 0; i--) {
		if (input[i] == '\r' || input[i] == '\n' || input[i] == ' ') {
			input[i] = 0;
		}
		else {
			break;
		}
	}
	
	return input;
}
*/

void fatal(const char *msg) {
	printf("%s\n", msg);
	exit(1);
}
