/*!
 * This program verifies whether a given Sudoku board is valid or not.
 * @author Selan R. Santos
 * @date March 4th, 2020.
 */
#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::fill_n;
#include <vector>
using std::vector;
#include <iterator>
using std::back_inserter;
#include <sstream>
using std::ostringstream;

#define EMPTY short(0) // The number representing an empty space.
#define SIZE 9         // Max dimension size for a Sudoku board. 

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

/// Generates and return a string with a "raw" representation of a Sudoku board.
std::string to_string( const board_t &b )
{
    std::ostringstream oss; // The string stream that will receive the data.
    // Print the content of each line
    //for ( const short *row : b ) {
    for ( auto row : b ) {
        for ( auto col{0} ; col < SIZE ; ++col )
            oss << row [col] << " ";
        oss << std::endl;
    }
    return oss.str();
}

/// Check whether a vector of SIZE digitis corresponds to a valid Sudoku row/col/square.
bool is_valid_line( const std::vector<short> &line )
{
    // Keeps track of the occurrences of values in a row
    short count[9]{0,0,0,0,0,0,0,0,0};

    // Traverse the line and count digits.
    for ( short e : line )
    {
        // Failed if we got a number outside the acceptable range.
        if ( e < 1 or e > SIZE ) return false;
        // Count.
        count[ e-1 ]++; // Recall that digits go from 1 to 9.
    }
    // Check the result of counting: `true` only if all counts are not zero.
    return std::all_of( count, count+SIZE, [](short val){ return val!=0; } );
}

/// Check whether the Sudoku board `b` passed as argument is valid or not.
bool is_valid( board_t b )
{
    // Aux array that will store each individual row, col, square to be tested.
    std::vector< short > line{ SIZE };

    //[1]=== Verify the rows
    // Traverse each row and check if it's a valid row.
    for ( short row{0} ; row < SIZE ; ++row )
    {
        line.clear(); // we need to clear a line, otherwise we will accumulate several lines...
        // Copy current row to the aux array `line`.
        std::copy( &b[row][0], &b[row][SIZE], std::back_inserter( line ) );
        if ( not is_valid_line( line ) )
        {
            std::cout << ">>> row \"" << row << "\" is invalid!\n";
            return false;
        }
    }

    //[2]=== Verify the cols
    // Traverse each col and check if it's a valid row.
    for ( short col{0} ; col < SIZE ; ++col )
    {
        line.clear();
        // "Manually" copy current col to the aux array `line`.
        for ( short row{0} ; row < SIZE ; ++row )
            line.push_back( b[row][col] );

        if ( not is_valid_line( line ) )
        {
            std::cout << ">>> column \"" << col << "\" is invalid!\n";
            return false;
        }
    }

    // [3]=== Verify each of the 9 sudoku squares
    // (x,y) is the first coordinate of each square.
    for ( short y{0} ; y < SIZE ; y+=3 )
        for ( short x{0} ; x < SIZE ; x+=3 )
        {
            line.clear();
            // Traverse current square.
            for ( short r{0} ; r < 3 ; ++r )
                for ( short c{0} ; c < 3 ; ++c )
                    line.push_back( b[y+r][x+c] ); // offset by (r,c).

            if ( not is_valid_line( line ) )
            {
                std::cout << ">>> square (" << y/3 << "," << x/3 << ") is invalid!\n";
                return false;
            }
        }

    return true; // This is just a stub. Replace it as needed.
}


int main(void)
{
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
        },
        // board 4: problem
        {
            { 6, 2, 1, 9, 5, 7, 3, 4, 8 },
            { 2, 7, 4, 1, 9, 8, 6, 3, 5 },
            { 1, 8, 3, 4, 2, 9, 5, 6, 7 },
            { 8, 9, 7, 6, 1, 5, 4, 2, 3 },
            { 4, 6, 8, 5, 3, 2, 7, 9, 1 },
            { 5, 4, 6, 7, 8, 3, 9, 1, 2 },
            { 7, 3, 9, 2, 4, 1, 8, 5, 6 },
            { 9, 1, 5, 3, 7, 6, 2, 8, 4 },
            { 3, 5, 2, 8, 6, 4, 1, 7, 9 }
        },
        // board 5: problem
        {
            { 6, 2, 1, 9, 5, 7, 3, 4, 8 },
            { 2, 7, 4, 1, 9, 8, 6, 3, 5 },
            { 1, 8, 3, 4, 2, 9, 5, 6, 7 },
            { 8, 9, 7, 6, 1, 5, 4, 2, 3 },
            { 4, 6, 8, 5, 3, 2, 5, 9, 1 },
            { 5, 4, 6, 7, 8, 3, 9, 1, 2 },
            { 7, 3, 9, 2, 4, 1, 8, 5, 6 },
            { 9, 3, 5, 3, 7, 6, 2, 8, 4 },
            { 3, 5, 2, 8, 6, 4, 1, 7, 9 }
        },
        // board 6: Problem
        {
            { 6, 2, 1, 9, 5, 7, 3, 4, 8 },
            { 2, 7, 4, 1, 9, 8, 6, 3, 5 },
            { 1, 8, 3, 4, 2, 19, 5, 6, 7 },
            { 8, 9, 7, 6, 1, 5, 4, 2, 3 },
            { 4, 6, 8, 5, 3, 2, 7, 9, 1 },
            { 5, 4, 6, 7, 8, 3, 9, 1, 2 },
            { 7, -3, 9, 2, 4, 1, 8, 5, 6 },
            { 9, 1, 5, 3, 7, 6, 2, 8, 4 },
            { 3, 5, 2, 8, 6, 4, 1, 7, 9 }
        },
        // board 7: Problem
        {
            { 6, 2, 1, 9, 5, 7, 3, 4, 8 },
            { 2, 7, 4, 1, 9, 8, 6, 3, 5 },
            { 1, 8, 3, 4, 2, 9, 5, 6, 7 },
            { 8, 9, 7, 6, 1, 5, 4, 2, 3 },
            { 4, 6, 8, 5, 3, 2, 7, 9, 1 },
            { 5, 4, 6, 7, 8, 3, 9, 1, 2 },
            { 7, 3, 9, 2, 4, 1, 0, 5, 6 },
            { 9, 1, 5, 3, 7, 6, 2, 8, 4 },
            { 3, 5, 2, 8, 6, 4, 1, 7, 9 }
        },
        // board 8: Problem
        {
            { 6, 2, 1, 9, 5, 7, 3, 4, 8 },
            { 2, 7, 4, 1, 9, 8, 6, 3, 5 },
            { 1, 8, 3, 4, 2, 9, 5, 6, 7 },
            { 8, 9, 7, 3, 1, 5, 4, 2, 3 },
            { 4, 6, 8, 5, 3, 2, 7, 9, 1 },
            { 5, 4, 6, 7, 8, 6, 9, 1, 2 },
            { 7, 3, 9, 2, 4, 1, 8, 5, 6 },
            { 9, 1, 5, 3, 7, 6, 2, 8, 4 },
            { 3, 5, 2, 8, 6, 4, 1, 7, 9 }
        },
        // board 9: Problem
        {
            { 1, 6, 2, 8, 5, 4, 7, 9, 3 },
            { 5, 3, 4, 1, 2, 6, 9, 7, 8 },
            { 7, 8, 9, 6, 4, 5, 3, 2, 1 },
            { 4, 7, 5, 3, 1, 9, 2, 8, 6 },
            { 9, 1, 3, 5, 8, 7, 6, 4, 2 },
            { 6, 2, 8, 7, 9, 1, 4, 3, 5 },
            { 3, 5, 6, 4, 7, 2, 8, 1, 9 },
            { 2, 4, 1, 9, 3, 8, 5, 6, 7 },
            { 8, 9, 7, 2, 6, 3, 1, 5, 4 }
        },
        // board 10: Problem
        {
            { 5, 3, 4, 6, 7, 8, 9, 1, 2 },
            { 6, 7, 2, 1, 9, 5, 3, 4, 8 },
            { 1, 9, 8, 3, 4, 2, 5, 6, 7 },
            { 8, 9, 5, 7, 6, 1, 4, 2, 3 },
            { 4, 2, 6, 8, 5, 3, 7, 9, 1 },
            { 7, 1, 3, 9, 2, 4, 8, 5, 6 },
            { 9, 6, 1, 5, 3, 7, 2, 8, 4 },
            { 2, 8, 7, 4, 1, 9, 6, 3, 5 },
            { 3, 4, 5, 2, 8, 6, 1, 7, 9 }
        }
    };


    short n_boards{ sizeof(boards)/sizeof(board_t) }; // Number of boards...
    for ( short i{0}; i < n_boards ; ++i )
    {
        std::cout << "Board #" << (i+1) << ":\n";
        pretty_print( boards[i] );
        auto valid = is_valid( boards[i] );
        std::cout << "\nIs it valid? " << std::boolalpha << valid << std::endl;
        std::cout << "\n";

        std::clog << to_string(boards[i]) << std::endl;
    }

    return 0;
}
