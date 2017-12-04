#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "3.h"

int main(int argc, char **argv) {
	char *solution_one, *solution_two;
	double time_elapsed_one, time_elapsed_two;
	int input;

	input = read_input();

	start_timer();
	solution_one = part_one(input);
	time_elapsed_one = stop_timer();
	
	start_timer();
	solution_two = part_two(input);
	time_elapsed_two = stop_timer();

	printf("Solution One: %s (took %fms)\n", solution_one, time_elapsed_one);
	printf("Solution Two: %s (took %fms)\n", solution_two, time_elapsed_two);

	free(solution_one);
	free(solution_two);

	return 0;
}

// Parts 1 and 2 are similar enough to use the same function for both parts.
char *solve(int input, int part) {
	char *ret;
	unsigned char direction;
	unsigned int answer, i, left_to_go, **memory, n, need_to_go, square, tmp_square, value;
	int origin_x, origin_y, x, y;
	x = WIDTH / 2;
	y = HEIGHT / 2;
	origin_x = x;
	origin_y = y;
	direction = RIGHT;
	value = 1;
	need_to_go = 1;
	left_to_go = 1;

	if (part == 1) {
		// Skip to the closest perfect square less than our input number
		n = 0;
		for (value = 1; 1 == 1; value += 2) {
			tmp_square = value * value;
			if (tmp_square > input) {
				break;
			}
			n++;
			square = tmp_square;
		}
		n--;
		x = origin_x + n;
		y = origin_y + n;
		need_to_go = value - 2;
		left_to_go = 1;
		value = square;
	}
	else {
		memory = malloc(sizeof(unsigned int*) * HEIGHT);
		for (i = 0; i < HEIGHT; i++) {
			memory[i] = calloc(1, sizeof(unsigned int) * WIDTH);
		}
	}

	while (value < ((HEIGHT * WIDTH) + 1)) {
		if (part == 1 && value == input) {
			answer = abs(x - origin_x) + abs(y - origin_y);
			break;
		}
		if (part == 2) {
			if (x == origin_x && y == origin_y) {
				value = 1;
			}
			else {
				value = 0;
				value += memory_val(memory, y - 1, x - 1);
				value += memory_val(memory, y - 1, x);
				value += memory_val(memory, y - 1, x + 1);
				value += memory_val(memory, y,     x - 1);
				value += memory_val(memory, y,     x + 1);
				value += memory_val(memory, y + 1, x - 1);
				value += memory_val(memory, y + 1, x);
				value += memory_val(memory, y + 1, x + 1);
				if (value > input) {
					answer = value;
					break;
				}
			}
			memory[y][x] = value;
		}

		if (part == 1) {
			value++;
		}

		switch(direction) {
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case LEFT:
			x--;
			break;
		case DOWN:
			y++;
			break;
		}

		left_to_go--;

		if (left_to_go == 0) {
			switch(direction) {
			case RIGHT:
				direction = UP;
				break;
			case UP:
				direction = LEFT;
				need_to_go++;
				break;
			case LEFT:
				direction = DOWN;
				break;
			case DOWN:
				direction = RIGHT;
				need_to_go++;
				break;
			}
			left_to_go = need_to_go;
		}
	}

	if (part == 2) {
		for (i = 0; i < HEIGHT; i++) {
			free(memory[i]);
		}
		free(memory);
	}

	ret = malloc(32);
	snprintf(ret, 32, "%d", answer);
	
	return ret;
}

char *part_one(int input) {
	return solve(input, 1);
}

char *part_two(int input) {
	return solve(input, 2);
}

unsigned int memory_val(unsigned int **memory, int y, int x) {
	// Bounds-checking the memory array
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT) {
		return 0;
	}
	return memory[y][x];
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

int read_input() {
	FILE *input_file;
	int input;

	input_file = fopen("input", "r");
	if (input_file == NULL) {
		fatal("Please put your puzzle input in a file called \"input\" (case-sensitive) in the same folder as the program.\n");
	}

	fscanf(input_file, "%d", &input);
	fclose(input_file);
	return input;
}

void fatal(const char *msg) {
	printf("%s\n", msg);
	exit(1);
}
