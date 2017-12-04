#ifndef AOC17_4_H
#define AOC17_4_H

#include <sys/time.h>

// Global time value used in timer functions
struct timeval timer_start;

struct passphrase {
	int word_count;
	char **words;
	char **alpha_words;
};

struct puzzle_input {
	int passphrase_count;
	struct passphrase **passphrases;
};

char *solve(struct puzzle_input*, int);
char *part_one(struct puzzle_input*);
char *part_two(struct puzzle_input*);
char *strcopy(char*);

// Helper functions
struct puzzle_input *read_input(void);
void start_timer(void);
double stop_timer(void);
void fatal(const char*);

#endif
