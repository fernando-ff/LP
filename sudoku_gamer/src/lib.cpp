#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::fill_n;
#include <vector>
using std::vector;
#include <iterator>
using std::back_inserter;
#include<stdlib.h>//rand,srand
#include <time.h>//time

#include "../include/sudoku.h"

#define SIZE 9          // Max dimension size for a Sudoku board.
#define EMPTY short(0) // The number representing an empty space.


// This is just an alias to make the code more "clean".
typedef short board_t[SIZE][SIZE];

/// Prints out a pretty-print version of the Sudoku board.
void pretty_print( const board_t &b )
{
    // First row requires a different line separation.
    std::cout << "    0 1 2   3 4 5   6 7 8  \n";
    std::cout << "  +-------+-------+-------+\n";
    // pretty_print each row.
    for ( short r{0} ; r < SIZE ; ++r )
    {
        // pretty_print a line separation before rows 0, 3, 6.
        // Traverse all number on this row.
        std::cout << r << " | "; // At the beginning of each row pretty_print a `|`.
        for ( short c{0} ; c < SIZE ; ++c )
        {
            // Pretty printing: if value is zero, pretty_print a blank space.
            if ( b[r][c] == EMPTY ) std::cout << "  ";
            else std::cout << b[r][c] << " ";
            // Add a separation space every 3 numbers.
            if ( (c+1) % 3 == 0 )  std::cout << "| ";
        }
        // Internal separation of internal "squares"
        if ( r==2 or r==5 )
            std::cout << "\n  |-------+-------+-------|"; // Internal line separation.
        std::cout << "\n";
    }
    // Last row requires a different line separation.
    std::cout << "  +-------+-------+-------+\n";
}
void loadingBoard(const board_t &b,  board_t &b_game){
    int i,j;
    srand(time(NULL));

	for (short r{0}; r < SIZE; ++r)//copy b to b_game
	{
		for (short c = 0; c < SIZE; ++c){
          b_game[r][c] = b[r][c];
        }
	}
	
    for (short k{0}; k < SIZE*5; ++k)
	{
		i = rand() % 9;
        j = rand() % 9;
		b_game[j][i] = EMPTY;
	}

}

/// Check whether the Sudoku board `b` passed as argument is valid or not.
bool is_valid( board_t b, board_t b_game, short row, short column )
{
    if (b_game[row][column] == b[row][column])  return true;
    else{
        b_game[row][column] = EMPTY;
        return false;
    }
    
    return true; // This is just a stub. Replace it as needed.
}
void selection(board_t b, short row, short column){
    // First row requires a different line separation.
    if (column == 0)    std::cout << "    v 1 2   3 4 5   6 7 8  \n";
    if (column == 1)    std::cout << "    0 v 2   3 4 5   6 7 8  \n";
    if (column == 2)    std::cout << "    0 1 v   3 4 5   6 7 8  \n";
    if (column == 3)    std::cout << "    0 1 2   v 4 5   6 7 8  \n";
    if (column == 4)    std::cout << "    0 1 2   3 v 5   6 7 8  \n";
    if (column == 5)    std::cout << "    0 1 2   3 4 v   6 7 8  \n";
    if (column == 6)    std::cout << "    0 1 2   3 4 5   v 7 8  \n";
    if (column == 7)    std::cout << "    0 1 2   3 4 5   6 v 8  \n";
    if (column == 8)    std::cout << "    0 1 2   3 4 5   6 7 v  \n";

    std::cout << "  +-------+-------+-------+\n";
    // pretty_print each row.
    for ( short r{0} ; r < SIZE ; ++r )
    {
        // pretty_print a line separation before rows 0, 3, 6.
        // Traverse all number on this row.
        if (row == r)   std::cout << "> | ";
        else    std::cout << r << " | "; // At the beginning of each row pretty_print a `|`.
        for ( short c{0} ; c < SIZE ; ++c )
        {
            // Pretty printing: if value is zero, pretty_print a blank space.
            if ( b[r][c] == EMPTY ) std::cout << "  ";
            else std::cout << b[r][c] << " ";
            // Add a separation space every 3 numbers.
            if ( (c+1) % 3 == 0 )  std::cout << "| ";
        }
        // Internal separation of internal "squares"
        if ( r==2 or r==5 )
            std::cout << "\n  |-------+-------+-------|"; // Internal line separation.
        std::cout << "\n";
    }
    // Last row requires a different line separation.
    std::cout << "  +-------+-------+-------+\n";
}
void show( board_t b, board_t b_game, short row, short column ){
	b_game[row][column] = b[row][column];
}