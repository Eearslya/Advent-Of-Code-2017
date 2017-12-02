#ifndef AOC17_2_H
#define AOC17_2_H

#include <sys/time.h>

struct spreadsheet {
	unsigned short rows;
	unsigned short cols;
	unsigned int **data;
};

// Global time value used in timer functions
struct timeval timer_start;

char *part_one(struct spreadsheet*);
char *part_two(struct spreadsheet*);

// Helper functions
struct spreadsheet *read_input(void);
void free_input(struct spreadsheet*);
void start_timer(void);
double stop_timer(void);
void fatal(const char*);

#endif
