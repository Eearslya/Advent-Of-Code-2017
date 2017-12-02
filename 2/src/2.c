#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "2.h"

unsigned int **spreadsheet;

int main(int argc, char **argv) {
    char *solution_one, *solution_two;
    double time_elapsed_one, time_elapsed_two;
	struct spreadsheet *input;

    input = read_input();

    start_timer();
    solution_one = part_one(input);
    time_elapsed_one = stop_timer();
    
    start_timer();
    solution_two = part_two(input);
    time_elapsed_two = stop_timer();

    printf("Solution One: %s (took %fms)\n", solution_one, time_elapsed_one);
    printf("Solution Two: %s (took %fms)\n", solution_two, time_elapsed_two);

	free_input(input);
    free(solution_one);
    free(solution_two);

    return 0;
}

char *part_one(struct spreadsheet *input) {
	char *ret;
	unsigned int answer, highest, i, j, lowest;

	answer = 0;
	for (i = 0; i < input->rows; i++) {
		highest = 0;
		lowest = 99999;
		for (j = 0; j < input->cols; j++) {
			if (input->data[i][j] > highest) {
				highest = input->data[i][j];
			}
			if (input->data[i][j] < lowest) {
				lowest = input->data[i][j];
			}
		}
		answer += (highest - lowest);
	}

	ret = malloc(16);
	snprintf(ret, 16, "%u", answer);
	return ret;
}

char *part_two(struct spreadsheet *input) {
	char *ret;
	unsigned int answer, i, j, k, value;

	answer = 0;
	for (i = 0; i < input->rows; i++) {
		value = 0;
		for (j = 0; j < input->cols; j++) {
			for (k = 0; k < input->cols; k++) {
				if (j == k) {
					continue;
				}
				if ((input->data[i][j] % input->data[i][k]) == 0) {
					value = input->data[i][j] / input->data[i][k];
					break;
				}
			}
			if (value > 0) {
				break;
			}
		}
		answer += value;
	}

	ret = malloc(16);
	snprintf(ret, 16, "%u", answer);
	return ret;
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

struct spreadsheet *read_input() {
    char *line, *token;
    FILE *input_file;
	int row, cell;
    size_t line_len;
	struct spreadsheet *spreadsheet;

    input_file = fopen("input", "r");
    if (input_file == NULL) {
		fatal("Please put your puzzle input in a file called \"input\" (case-sensitive) in the same folder as the program.\n");
    }

	row = 0;
	line = NULL;
	spreadsheet = malloc(sizeof(struct spreadsheet));
	spreadsheet->data = malloc(0);
	while (getline(&line, &line_len, input_file) >= 0) {
		cell = 0;
		spreadsheet->data = realloc(spreadsheet->data, sizeof(unsigned int*) * (row + 1));
		spreadsheet->data[row] = malloc(0);
		token = strtok(line, " \t");
		while (token != NULL) {
			spreadsheet->data[row] = realloc(spreadsheet->data[row], sizeof(unsigned int) * (cell + 1));
			spreadsheet->data[row][cell] = atoi(token);
			cell++;
			token = strtok(NULL, " \t");
		}
		row++;
	}
	free(line);
	spreadsheet->rows = row;
	spreadsheet->cols = cell;
	
    fclose(input_file);

    return spreadsheet;
}

void free_input(struct spreadsheet *input) {
	int i;
	for (i = 0; i < input->rows; i++) {
		free(input->data[i]);
	}
	free(input->data);
    free(input);
}

void fatal(const char *msg) {
    printf("%s\n", msg);
    exit(1);
}
