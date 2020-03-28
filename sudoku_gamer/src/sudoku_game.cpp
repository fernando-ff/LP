/* Versão interativa do Sudoku
 * Desafio proposto na disciplina LP1 na UFRN
 * Autor:https://github.com/fernando-ff
 * Finalizado em: ?
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
#include<stdlib.h>//rand,srand
#include <time.h>//time

#include "../include/sudoku_gamer_lib.h"

#define SIZE 9          // Max dimension size for a Sudoku board.
#define EMPTY short(0) // The number representing an empty space.

typedef short board_t[SIZE][SIZE];


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
            selection( board_game, row, column );
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
