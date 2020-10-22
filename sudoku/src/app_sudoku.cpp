#include <iostream>

#include "../include/sudoku.h"

int main(int argc, char const *argv[])
{
    GameManager sudoku;

    if(strcmp(argv[1], "--help") == 0) 
    {
        render_command_line_help();
        return 0;
     
    }
    else if(strcmp(argv[1], "--ncheck") == 0)
    {
        sudoku.chk = std::stoi(argv[2]);
        sudoku.check_backup = std::stoi(argv[2]);
        if(argc > 3)
        {
            sudoku.f = argv[3];
        }
    }
    else if(argc > 1)
    {
        sudoku.f = argv[1];
    }
    sudoku.render_game_intro();


    sudoku.initialize();


    while (not sudoku.quit_game())
    {
        sudoku.render();
        sudoku.process_events();
        sudoku.update(); 
    }
    sudoku.render();
    return 0;
}
