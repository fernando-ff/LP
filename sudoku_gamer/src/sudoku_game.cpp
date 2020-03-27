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
	for (short r{0}; r < SIZE; ++r)//copy b to b_game
	{
		for (short c = 0; c < SIZE; ++c){
          b_game[r][c] = b[r][c];
        }
	}
    srand(time(NULL));
	int i,j;
    for (short k{0}; k < SIZE; ++k)
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
int main(void){
	board_t boards[ ]
    {
        // board 1: OK
        {
            { 1, 3, 4, 6, 7, 8, 5, 9, 2 },
            { 6, 7, 2, 1, 9, 5, 3, 4, 8 },
            { 5, 9, 8, 3, 4, 2, 1, 6, 7 },
            { 8, 5, 9, 7, 6, 1, 4, 2, 3 },
            { 4, 2, 6, 8, 5, 3, 9, 7, 1 },
            { 7, 1, 3, 4, 2, 9, 8, 5, 6 },
            { 9, 6, 1, 5, 3, 7, 2, 8, 4 },
            { 2, 8, 7, 9, 1, 4, 6, 3, 5 },
            { 3, 4, 5, 2, 8, 6, 7, 1, 9 }
        },
        // board 2: OK
        {
            { 1, 6, 2, 8, 5, 7, 4, 9, 3 },
            { 5, 3, 4, 1, 2, 9, 6, 7, 8 },
            { 7, 8, 9, 6, 4, 3, 5, 2, 1 },
            { 4, 7, 5, 3, 1, 2, 9, 8, 6 },
            { 9, 1, 3, 5, 8, 6, 7, 4, 2 },
            { 6, 2, 8, 7, 9, 4, 1, 3, 5 },
            { 3, 5, 6, 4, 7, 8, 2, 1, 9 },
            { 2, 4, 1, 9, 3, 5, 8, 6, 7 },
            { 8, 9, 7, 2, 6, 1, 3, 5, 4 }
        },
        // board 3: OK
        {
            { 5, 3, 4, 6, 7, 8, 9, 1, 2 },
            { 6, 7, 2, 1, 9, 5, 3, 4, 8 },
            { 1, 9, 8, 3, 4, 2, 5, 6, 7 },
            { 8, 5, 9, 7, 6, 1, 4, 2, 3 },
            { 4, 2, 6, 8, 5, 3, 7, 9, 1 },
            { 7, 1, 3, 9, 2, 4, 8, 5, 6 },
            { 9, 6, 1, 5, 3, 7, 2, 8, 4 },
            { 2, 8, 7, 4, 1, 9, 6, 3, 5 },
            { 3, 4, 5, 2, 8, 6, 1, 7, 9 }
        }
        
    };

    cout << "\n=======! SUDOKU GAME !======\n";
    
    srand(time( NULL ));
    auto i = rand() % 3;
    
    board_t board_game;
    loadingBoard( boards[i], board_game);
    
    short controller{1};
    while(controller != 0){
        pretty_print( board_game );

    	std::cout <<"\n===========================\n";
		std::cout << "        < OPTIONS >      \n"
	    	 << "      0-Exit    1-Play   \n"
	    	 << "       >YOUR CHOSE:";
	    std::cin >> controller;

	    if (controller == 1)
	    {
            short row,column; 
	     	std::cout << ">Selection the row:";
	     	std::cin >> row;
	     	std::cout << ">Selection the collumn:";
	     	std::cin >> column;

	     	if(board_game[row][column] == EMPTY){//
	     		short value;
                std::cout << ">Selection the value:";
	     		std::cin >> value;
                board_game[row][column] = value;
                while( is_valid( boards[i],board_game, row, column ) == false){
                    std::cout << "Invalid!\nInsert a new value:";
                    std::cin >> value;
                    board_game[row][column] = value;
                }
	     	}
	     	else std::cout << "\n>That is not possible!\n";
	    }

	}

	std::cout <<"\n=======! END GAME !========\n";
	return 0;
}
