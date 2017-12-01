#ifndef AOC17_1_H
#define AOC17_1_H

#include <sys/time.h>

// Global time value used in timer functions
struct timeval timer_start;

char *solve(char*, int);
char *part_one(char*);
char *part_two(char*);

// Helper functions
char *read_input(void);
void start_timer(void);
double stop_timer(void);
void fatal(const char*);

#endif
