#ifndef SUDOKU_LIB
#define SUDOKU_LIB

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include<stdlib.h>
#include <time.h>

#define SIZE 9          // Max dimension size for a Sudoku board.
#define EMPTY short(0) // The number representing an empty space.


typedef short board_t[SIZE][SIZE];


void pretty_print( const board_t &b );
void loadingBoard(const board_t &b,  board_t &b_game);
bool is_valid( board_t b, board_t b_game, short row, short column );
void selection( board_t b, short row, short column );

#endif