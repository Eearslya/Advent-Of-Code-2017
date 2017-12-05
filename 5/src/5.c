#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "5.h"

int main(int argc, char **argv) {
	char *solution_one, *solution_two;
	double time_elapsed_one, time_elapsed_two;
	struct input *input;

	input = read_input();

	start_timer();
	solution_one = part_one(input);
	time_elapsed_one = stop_timer();
	
	start_timer();
	solution_two = part_two(input);
	time_elapsed_two = stop_timer();

	printf("Solution One: %s (took %fms)\n", solution_one, time_elapsed_one);
	printf("Solution Two: %s (took %fms)\n", solution_two, time_elapsed_two);

	free(input->data);
	free(input);
	free(solution_one);
	free(solution_two);

	return 0;
}

// Parts 1 and 2 are similar enough to use the same function for both parts.
char *solve(struct input *input, int part) {
	char *answer;
	int jump, new_position, position, steps;
	struct input *jumps;

	// We're going to modify the input data, so we'll need our own copy
	jumps = malloc(sizeof(struct input));
	jumps->length = input->length;
	jumps->data = malloc(sizeof(int) * input->length);
	memcpy(jumps->data, input->data, sizeof(int) * input->length);

	position = 0;
	steps = 0;
	while (position >= 0 && position < jumps->length) {
		steps++;
		if (part == 2 && jumps->data[position] >= 3) {
			position += jumps->data[position]--;
		}
		else {
			position += jumps->data[position]++;
		}
	}

	free(jumps->data);
	free(jumps);

	answer = malloc(16);
	snprintf(answer, 16, "%d", steps);
	
	return answer;
}

char *part_one(struct input *input) {
	return solve(input, 1);
}

char *part_two(struct input *input) {
	return solve(input, 2);
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

struct input *read_input() {
	char *line;
	struct input *input;
	FILE *input_file;
	size_t line_len;

	input_file = fopen("input", "r");
	if (input_file == NULL) {
		fatal("Please put your puzzle input in a file called \"input\" (case-sensitive) in the same folder as the program.\n");
	}

	line = NULL;
	input = malloc(sizeof(struct input));
	input->length = 0;
	input->data = malloc(0);
	while (getline(&line, &line_len, input_file) >= 0) {
		input->data = realloc(input->data, sizeof(int) * (input->length + 1));
		sscanf(line, "%d", &input->data[input->length]);
		input->length++;
	}
	free(line);
	
	return input;
}

void fatal(const char *msg) {
	printf("%s\n", msg);
	exit(1);
}
