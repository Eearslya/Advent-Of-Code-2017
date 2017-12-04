# Advent Of Code 2017
https://adventofcode.com/2017

My solutions to the problems in 2017's Advent Of Code.
All solutions are written in C, specifically the C99 standard.

All of these programs have been compiled and tested on Debian Linux. I have not tested them on any other platform, and cannot guarantee compatibility.

## Requirements
* `gcc` or other C compiler compatible with the C99 standard.

## Building
Each day has its own folder with source files and a Makefile.
To create the `solution` program, simply use `make` within that day's folder.

## Usage
Each program will expect an `input` file within the same directory as the `solution` binary.
This file should contain that day's puzzle input, without any modifications or additions.

Simply run the `solution` binary and it will output the puzzle answer for both parts of that day.
