#define _GNU_SOURCE
#define __STDC_WANT_LIB_EXT2__ 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "4.h"

int main(int argc, char **argv) {
	char *solution_one, *solution_two;
	double time_elapsed_one, time_elapsed_two;
	int i, j;
	struct puzzle_input *input;

	input = read_input();

	start_timer();
	solution_one = part_one(input);
	time_elapsed_one = stop_timer();
	
	start_timer();
	solution_two = part_two(input);
	time_elapsed_two = stop_timer();

	printf("Solution One: %s (took %fms)\n", solution_one, time_elapsed_one);
	printf("Solution Two: %s (took %fms)\n", solution_two, time_elapsed_two);

	for (i = 0; i < input->passphrase_count; i++) {
		for (j = 0; j < input->passphrases[i]->word_count; j++) {
			free(input->passphrases[i]->words[j]);
			free(input->passphrases[i]->alpha_words[j]);
		}
		free(input->passphrases[i]->words);
		free(input->passphrases[i]->alpha_words);
		free(input->passphrases[i]);
	}
	free(input->passphrases);
	free(input);
	free(solution_one);
	free(solution_two);

	return 0;
}

// Parts 1 and 2 are similar enough to use the same function for both parts.
char *solve(struct puzzle_input *input, int part) {
	char *ret;
	int answer, i, j, k, valid;

	answer = 0;
	for (i = 0; i < input->passphrase_count; i++) {
		valid = 1;
		for (j = 0; j < input->passphrases[i]->word_count; j++) {
			for (k = 0; k < input->passphrases[i]->word_count; k++) {
				if (j == k) {
					continue;
				}
				if (strcmp(input->passphrases[i]->words[j], input->passphrases[i]->words[k]) == 0 || (part == 2 && strcmp(input->passphrases[i]->alpha_words[j], input->passphrases[i]->alpha_words[k]) == 0)) {
					valid = 0;
					break;
				}
			}
			if (!valid) {
				break;
			}
		}
		if (valid) {
			answer++;
		}
	}

	ret = malloc(16);
	snprintf(ret, 16, "%d", answer);
	return ret;
}

char *part_one(struct puzzle_input *input) {
	return solve(input, 1);
}

char *part_two(struct puzzle_input *input) {
	return solve(input, 2);
}

char *strcopy(char *a) {
	char *ret;
	ret = malloc(sizeof(char) * (strlen(a) + 1));
	strcpy(ret, a);
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

struct puzzle_input *read_input() {
	char *line, *word, *word_alpha;
	FILE *input_file;
	int i, j, pos, word_length;
	size_t line_len;
	struct passphrase *pass;
	struct puzzle_input *input;

	input_file = fopen("input", "r");
	if (input_file == NULL) {
		fatal("Please put your puzzle input in a file called \"input\" (case-sensitive) in the same folder as the program.\n");
	}

	input = malloc(sizeof(struct puzzle_input));
	input->passphrase_count = 0;
	input->passphrases = malloc(0);
	line = NULL;
	while (getline(&line, &line_len, input_file) >= 0) {
		line_len = strlen(line);
		for (i = line_len - 1; i >= 0; i--) {
			if (line[i] == '\r' || line[i] == '\n' || line[i] == ' ') {
				line[i] = 0;
			}
			else {
				break;
			}
		}
		pass = malloc(sizeof(struct passphrase));
		pass->word_count = 0;
		pass->words = malloc(0);
		pass->alpha_words = malloc(0);
		word = strtok(line, " ");
		while (word != NULL) {
			pass->words = realloc(pass->words, sizeof(char*) * (pass->word_count + 1));
			pass->alpha_words = realloc(pass->alpha_words, sizeof(char*) * (pass->word_count + 1));
			word_length = strlen(word);
			pass->words[pass->word_count] = strcopy(word);
			word_alpha = calloc(1, sizeof(char) * (word_length + 1));
			pos = 0;
			for (i = 0; i < 26; i++) {
				for (j = 0; j < word_length; j++) {
					if (word[j] == ('a' + i)) {
						word_alpha[pos++] = word[j];
					}
				}
			}
			pass->alpha_words[pass->word_count] = strcopy(word_alpha);
			pass->word_count++;
			free(word_alpha);
			word = strtok(NULL, " ");
		}
		input->passphrases = realloc(input->passphrases, sizeof(struct passphrase*) * (input->passphrase_count + 1));
		input->passphrases[input->passphrase_count++] = pass;
	}
	free(line);
	
	return input;
}

void fatal(const char *msg) {
	printf("%s\n", msg);
	exit(1);
}
