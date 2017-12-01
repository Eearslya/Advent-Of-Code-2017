#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "1.h"

int main(int argc, char **argv) {
    char *input, *solution_one, *solution_two;
    double time_elapsed_one, time_elapsed_two;

    input = read_input();

    start_timer();
    solution_one = part_one(input);
    time_elapsed_one = stop_timer();
    
    start_timer();
    solution_two = part_two(input);
    time_elapsed_two = stop_timer();

    printf("Solution One: %s (took %fms)\n", solution_one, time_elapsed_one);
    printf("Solution Two: %s (took %fms)\n", solution_two, time_elapsed_two);

    free(input);
    free(solution_one);
    free(solution_two);

    return 0;
}

// Parts 1 and 2 are similar enough to use the same function for both parts.
char *solve(char *input, int part) {
    int answer, i, jump, pos;
    char *answer_buf;
    size_t input_length;

    answer = 0;
    input_length = strlen(input);

    if (part == 1) {
	jump = 1;
    }
    else {
	jump = (int) input_length / 2;
    }

    for (i = 0; i < input_length; i++) {
	pos = i + jump;
	if (pos > input_length) {
	    pos -= input_length;
	}
	if (input[i] == input[pos]) {
	    answer += input[i] - '0';
	}
    }

    answer_buf = malloc(sizeof(char) * 16);
    snprintf(answer_buf, 15, "%d", answer);

    return answer_buf;
}

char *part_one(char *input) {
    return solve(input, 1);
}

char *part_two(char *input) {
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

char *read_input() {
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

void fatal(const char *msg) {
    printf("%s\n", msg);
    exit(1);
}
