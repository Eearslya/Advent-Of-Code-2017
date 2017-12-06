#ifndef AOC17_6_H
#define AOC17_6_H

#include <list>
#include <string>
#include <sys/time.h>

// Global time value used in timer functions
struct timeval timer_start;

std::string solve(std::string, int);
std::string part_one(std::string);
std::string part_two(std::string);

// Helper functions
std::string read_input(void);
void start_timer(void);
double stop_timer(void);
void fatal(const char*);

class MemoryBank {
	public:
	void cycle(void);
	std::list<unsigned int> banks;
};

#endif
