#ifndef AOC17_3_H
#define AOC17_3_H

#include <sys/time.h>

#define WIDTH 1023
#define HEIGHT 1023

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

// Global time value used in timer functions
struct timeval timer_start;

char *solve(int, int);
char *part_one(int);
char *part_two(int);
unsigned int memory_val(unsigned int**, int, int);

// Helper functions
int read_input(void);
void start_timer(void);
double stop_timer(void);
void fatal(const char*);

#endif
