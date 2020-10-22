#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>

#include<stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "../include/text_color.h"

#define SIZE 9

/*! \mainpage Sudoku
 *
 * \section intro_sec Introduction
 *
 * Sudoku (数独, sūdoku, digit-single) (/suːˈdoʊkuː/, /-ˈdɒk-/, /sə-/, originally called Number Place)[1] is a logic-based,[2][3] combinatorial[4] number-placement puzzle. In classic sudoku, the objective is to fill a 9×9 grid with digits so that each column, each row, and each of the nine 3×3 subgrids that compose the grid (also called "boxes", "blocks", or "regions") contain all of the digits from 1 to 9. The puzzle setter provides a partially completed grid, which for a well-posed puzzle has a single solution.
 *
 * \section Starting
 *
 * \subsection clone clone this project
 * $ git clone https://projetos.imd.ufrn.br/fernandoff/sudoku.git
 * 
 * \subsection Access
 * $ cd sudoku
 * 
 * \subsection compile to compile
 * $ mkdir build && cd build
 * $ cmake ../
 * $ make
 *
 * \subsection run run the project
 * $ ./sudoku 
 *
 * \subsection help run the help
 * $ ./sudoku --help
 *
 * Remember to create the build folder and compile into it   
 *
 * 
 */

///board matrix type  
typedef short board_t[SIZE][SIZE];
///digit array type
typedef short digits_t[SIZE];
///row type
typedef short row_t;
///columt type
typedef short column_t;
///comands type
typedef std::string commands_t;
/// message type
typedef std::string message_t;
///options type
typedef std::string option_t;
///file type
typedef std::string file_t;
///value type
typedef short value_t;
///check type
typedef short check_t;
///end game type
typedef bool end_game_t;
/**
 * @brief data struct that the vector will store
 * 
 */
struct Board
{
    ///board stored
    board_t b;
};
/// boards data base type
typedef std::vector<Board> boards_data_base_t;
///count type
typedef std::vector<Board>::size_type count_t;

/**
 * @brief Main data struct that control the game
 * 
 */
struct GameManager
{
    ///Game State Machine
    enum GameState {
        WELCOME = 0,
        START,
        PLAY,
        NEW_GAME,
        QUIT,
        HELP,
        READ_OPT,
        READ_CMD,
        U_LAST,
        ACTION,
        CHECK,
        END_GAME,
        QUIT_GAME,
    }///game state 
        game_state;

    
    ///control if is the end game or not
    end_game_t e{ false };
    
    ///board counter
    count_t i{0};

    ///"data base" that stores the all the boards reads in the file
    boards_data_base_t bd; 
    
    ///main board that will stores the user play
    board_t b; 
    
    ///board that will stores the last user play
    board_t b_backup;
    
    ///board that will be compared with the main board 
    board_t b_check;

    ///default file that will be read the boards
    file_t f {"../boards/input.txt"};

    ///stores the user row choice.
    row_t r;
    
    ///stores the user column choice.
    column_t c;
    
    ///stores the user value choice.
    value_t v;
    
    ///stores the user input command.  
    commands_t cmd;
    
    ///stores the user input option
    option_t o;
    
    ///stores the input new game decision
    std::string new_g;

    ///Game messsage that will be render for the user.
    message_t m;
    
    ///digits left of the user.
    digits_t d{ 0,0,0,0,0,0,0,0,0 };
    
    ///Checks left of the user.
    check_t chk { 3 };
    
    ///checks left backup
    check_t check_backup{ 3 };
    //==Public Methods
    /**
     * @brief Setup the game 
     * 
     */
    void initialize( );
    /**
     * @brief Render all the elements at he screen
     * 
     */
    void render();
    /**
     * @brief Update the game state
     * 
     */
    void update();
    /**
     *  @brief Read the values
     * 
     */
    void process_events();
    /**
     * @brief Quit the game
     *  
     */
    bool quit_game() { return game_state == GameState::QUIT; };

    /**
     * @brief Verify the digits that can be used
     * 
     */
    void handle_digits_left();

    /**
     * @brief handle the place value
     * 
     */
    void handle_place_value();
    /**
     * @brief checks if the value choosed is valid or not
     * 
     */
    void handle_check_place_value();
    /**
     * @brief check if the game is over
     * 
     */
    void handle_game_over();
    /**
     * @brief removes a number in the board
     * 
     */
    void handle_number_removal();
    /**
     * @brief loads the board
     * 
     */
    void handle_load_board();
    /**
     * @brief reads the file with the boards
     * 
     */
    bool handle_read_boards();
    /**
     * @brief starts a new game.
     * 
     */
    void handle_new_game();

    /**
     * @brief renders the board 
     * 
     */
    void render_board();
    /**
     * @brief renders the game message
     * 
     */
    void render_message();
    /**
     * @brief render the check lefts
     * 
     */
    void render_checks_left();
    /**
     * @brief renders the digits that the user can use
     * 
     */
    void render_digits_lefts();
    /**
     * @brief Rrnders the screens
     * 
     */
    void render_screen();
    /**
     * @brief renders the intro messages.
     * 
     */
    void render_game_intro();
    /**
     * @brief checks whether the square 
     * in question is valid or not and renders it, 
     * red for invalid and blue for valid
     * 
     * @param r square row that will be checked
     * @param c square column that will be checked
     */
    void render_check_place(row_t r, column_t c);


};

    /**
     * @brief Render the help when the user
     * call her by command line
     */
    void render_command_line_help();
    /**
     * @brief renders the command sintax
     * 
     */
    void render_game_commands_sintax();
    /**
     * @brief renders the game options
     * 
     */
    void render_game_options();
    
    /**
     * @brief rendes the game rules 
     * 
     */
    void render_game_help();



#endif // SUDOKU_H
