#ifndef AOC17_5_H
#define AOC17_5_H

#include <sys/time.h>

// Global time value used in timer functions
struct timeval timer_start;

struct input {
	unsigned int length;
	int *data;
};

char *solve(struct input*, int);
char *part_one(struct input*);
char *part_two(struct input*);

// Helper functions
struct input *read_input(void);
void start_timer(void);
double stop_timer(void);
void fatal(const char*);

#endif
