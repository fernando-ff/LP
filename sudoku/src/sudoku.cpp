#include "../include/sudoku.h"

/*********************
 * Handle FUnctions
**********************/

void GameManager::handle_digits_left()
{
    digits_t d_backup {0,0,0,0,0,0,0,0,0};
    std::copy(std::begin(d_backup), std::end(d_backup), std::begin(this->d)); //reseting the digits left 
    
    for ( row_t r{0}; r < 9; r++)
    {
        for (column_t c{0}; c < 9; c++)
        { 
           if(this->b[r][c] > 0) //checking if the plance in question is ocuped  
           {
                this->d[ (this->b[r][c])-1 ] ++;//if he's, so we will mark the value
            }
        }
    }
}

void GameManager::handle_check_place_value()
{
    row_t row;
    column_t column;


    for ( column=0; column < SIZE; column++)
    {
        if( this->b[this->r][column] == this->v and column != this->c)
        {
            this->m = "Hey, this is not a valid to make. BUT it's up to you to keep it or not.";
            return;
        }
    }
      

    for ( row=0; row < SIZE; row++)
    {
        if(b[row][this->c] == this->v && this->r != row)
        {
            this->m =  "Hey, this is not a valid to make. BUT it's up to you to keep it or not.";
            return;
        }
    }
            
    if(this->r < 3 )
        row = 0 ;
    else if(this->r < 6)
        row = 3;
    else if(this->r < 9)
        row = 6; 
    if(this->c < 3)
        column = 0;
    else if(this->c < 6)
        column = 3;
    else if(this->c < 9)
        column = 6;

    row_t r_parameter = row + 3;
    column_t c_parameter = column + 3;
    for ( ; row < r_parameter; row++)
    {
        for ( ; column < c_parameter ; column++)
        {
            if(this->b[row][column] == this->v and this->r != row and this->c != column)
            {
                this->m =  "Hey, this is not a valid to make. BUT it's up to you to keep it or not.";
                return;
            }
        }
    }
    if(this->m != "Hey, this is not a valid to make. BUT it's up to you to keep it or not." )
        this->m =  "";    
}

void GameManager::handle_game_over()
{
    for (row_t r = 0; r < SIZE; r++)
    {
        for (column_t c = 0; c < SIZE; c++)
        {

            if(this->b[r][c] < 0)
            {
                return;
            }
                
        }
    }
    game_state = GameManager::END_GAME;
    
}

void GameManager::handle_place_value()
{
    this->b[this->r][this->c] = this->v;
    GameManager::handle_check_place_value();
    GameManager::handle_game_over();

}

void GameManager::handle_number_removal()
{
    this->b[this->r][this->c] = this->v*-1;
}

void GameManager::handle_load_board()
{
    if(game_state == GameManager::WELCOME or game_state == GameManager::NEW_GAME)
    {
        for (row_t r = 0; r < SIZE; r++)
        {
            for (column_t c = 0; c < SIZE; c++)
            {
                this->b[r][c] = this->bd.at(this->i).b[r][c];
                this->b_backup[r][c] = this->bd.at(this->i).b[r][c];
                this->b_check[r][c] = this->bd.at(this->i).b[r][c];            
            }
            
        }  
    }
    // else if(game_state == GameManager::NEW_GAME)
    // {
    //     for (row_t r{0}; r < SIZE; r++)
    //     {
    //         for (column_t c{0}; c < SIZE; c++)
    //         {
    //             this->b[r][c] = this->bd.at(this->i).b[r][c];
    //             this->b_backup[r][c] = this->bd.at(this->i).b[r][c];
    //             this->b_check[r][c] = this->bd.at(this->i).b[r][c];
    //         }
            
    //     }
        
    // }
    else if(game_state == GameManager::READ_CMD and this->cmd[0] == 'p')
    {
        for (row_t r{0}; r < SIZE; r++)
        {
            for (column_t c{0}; c < SIZE; c++)
            {
                this->b_backup[r][c] = this->b[r][c];
            }
            
        }
        
    }
    else if(game_state == GameManager::READ_CMD and this->cmd[0] == 'r')
    {
        for (row_t r{0}; r < SIZE; r++)
        {
            for (column_t c{0}; c < SIZE; c++)
            {
                this->b_backup[r][c] = this->b[r][c];
            }
            
        }       
    }
    else if(game_state == GameManager::PLAY)
    {
        for (row_t r = 0; r < SIZE; r++)
        {
            for (column_t c = 0; c < SIZE; c++)
            {
                this->b_backup[r][c] = this->b[r][c];
            }
            
        }
        
    }
    else if(game_state == GameManager::U_LAST)
    {
        for (row_t r {0}; r < SIZE; r++)
        {
            for (column_t c{0}; c < SIZE; c++)
            {
                this->b[r][c] = this->b_backup[r][c];
            }
            
        }   
    }  
}

bool GameManager::handle_read_boards()
{
    std::ifstream read;
    read.open(this->f);

    int x;
    row_t r { 0 };
    column_t c { 0 };
    Board aux_board;
    if(read.is_open())
    {
        while(read >> x)
        {
            if(r == 9)
            {
                this->bd.push_back(aux_board);
                r = 0;
                c = 0;
            }
            aux_board.b[r][c] = x;
            c++;

            if(c == 9) 
            {
                r++;
                c = 0;
            }

        }
    }
    else
    {
        std::cout << "Enter with a valid file!" << std::endl;
        return false;
    }  
    read.close();
    return true;
}

void GameManager::handle_new_game()
{
    for (row_t r = 0; r < SIZE; r++)
    {
        for (column_t c = 0; c < SIZE; c++)
        {
            if(this->b[r][c] != this->b_check[r][c])
            {
                this->m = "Are you sure you want leave this game?";
                return;
            }
        }
        
    }
    
}


/*********************
 * Render Functions
 ********************/

void GameManager::render_check_place(row_t r, column_t c)
{
    row_t row;
    column_t column;


    for ( column=0; column < SIZE; column++)
    {
        if( this->b[r][column] == this->b[r][c] and column != c)
        {
            std::cout << Color::tcolor(
                    std::to_string(this->b[r][c]),
                    Color::RED
                ) << " ";
            return;
        }
    }
      

    for (  row=0; row < SIZE; row++)
    {
        if(this->b[row][c] == this->b[r][c] and r != row)
        {
            std::cout << Color::tcolor(
                    std::to_string(this->b[r][c]),
                    Color::RED
                ) << " ";
            return;
        }
    }
            
    if(r < 3 )
        row = 0 ;
    else if(r < 6)
        row = 3;
    else if(r < 9)
        row = 6; 
    if(c < 3)
        column = 0;
    else if(c < 6)
        column = 3;
    else if(c < 9)
        column = 6;

    row_t r_parameter = row + 3;
    column_t c_parameter = column + 3;
    for ( ; row < r_parameter; row++)
    {
        for ( ; column < c_parameter ; column++)
        {
            if(this->b[row][column] == this->b[r][c] and r != row and c != column)
            {
                std::cout << Color::tcolor(
                    std::to_string(this->b[r][c]),
                    Color::RED
                ) << " ";
                return;
            }
        }
    }
    std::cout << Color::tcolor(
        std::to_string(this->b[r][c]),
        Color::BLUE
    ) << " ";

}

void GameManager::render_board()
{
    if(
        game_state == GameManager::NEW_GAME or 
        game_state == GameManager::START or 
        game_state == GameManager::HELP or
        game_state == GameManager::QUIT
        )
    {
        std::cout << Color::tcolor(
            "\n|--------[ MAIN SCREEN ]--------|\n", 
            Color::BLUE) << 
        std::endl;  
        std::cout << "      1 2 3   4 5 6   7 8 9  \n";
        std::cout << "    +-------+-------+-------+\n";
        
        for ( short r{0} ; r < SIZE ; ++r )
        {
            std::cout << "  " << (r+1) << " | "; 
            for ( short c{0} ; c < SIZE ; ++c ) 
            {
                if ( this->b[r][c] <= 0 or this->b[r][c] > 10)
                    std::cout << "  ";
                else
                    std::cout << this->b[r][c] << " ";
                if ( (c+1) % 3 == 0 )  
                    std::cout << "|" << " ";
            }
            if ( r==2 or r==5 )
                std::cout << "\n    |-------+-------+-------|"; 
            std::cout << "\n";
        }
        std::cout << "    +-------+-------+-------+\n";
    }
   
    else if(game_state == GameManager::ACTION)
    {
        std::cout << Color::tcolor(
          "\n|--------[ ACTION MODE ]--------|\n",
          Color::BLUE) << 
        std::endl; 

        // std::cout <<" ";
        // for(short i {0}; i < 10; i++)
        // {
        //     if(i % 3 == 0)
        //     {
        //         std::cout << "  ";
        //     }
        //     std::cout << "  " ;
        // }
        // std::cout << "\n";
        std::cout << "   ";
        for (short i {0}; i < 9; i++)
        {
            if(i % 3 == 0)
            {
                std::cout << "  ";
            }
            std::cout <<" "<< i+1 ;
        }
        std::cout<<"\n";
        std::cout << "    +-------+-------+-------+\n";

        for ( short r{0} ; r < SIZE ; ++r )
        {
            std::cout << "  " << (r+1) << " | "; 
            for ( short c{0} ; c < SIZE ; ++c )
            {
                if ( this->b[r][c] <  0)
                    std::cout << "  ";              
                else if(this->b_check[r][c] < 0)
                    GameManager::render_check_place(r,c);
                else     
                    std::cout << b[r][c] << " ";
                if ( (c+1) % 3 == 0 )
                    std::cout << "| ";      
            }
            if ( r==2 or r==5 )           
                std::cout << "\n    |-------+-------+-------|";
            std::cout << "\n";
        }
        std::cout << "    +-------+-------+-------+\n";
    }

    else if(game_state == GameManager::PLAY )
    {
        std::string color;
        if(this->m == "Hey, this is not a valid to make. BUT it's up to you to keep it or not.")
            color = "RED";
        else if(this->m =="")
            color = "BLUE";
        
        std::cout << Color::tcolor (
            "\n|--------[ ACTION MODE ]--------|\n",
            Color::BLUE)  << 
        std::endl; 

        std::cout <<"    ";
        for(short i {0}; i < 9; i++)
        {
            if(i % 3 == 0)
                std::cout << "  ";
            if(i == this->c)
                std::cout << Color::tcolor("v", Color::RED);
            else
                std::cout <<"  ";
        }
        std::cout << "\n";

        std::cout << "   ";
        for (short i {0}; i < 9; i++){
            if(i % 3 == 0)
                std::cout << "  ";
            std::cout <<" "<< i+1 ;
        }
        std::cout<<"\n";

        std::cout << "    +-------+-------+-------+\n";
        for ( short r{0} ; r < SIZE ; ++r )
        {
            if (this->r == r)
               std::cout << Color::tcolor("> ", Color::RED) << (r+1) << " | ";
            else 
                std::cout << "  " << (r+1) << " | "; 

            for ( short c{0} ; c < SIZE ; ++c )
            {
                if ( this->b[r][c] <=  0)
                    std::cout << "  ";
                else if(this->b_check[r][c] < 0)
                    GameManager::render_check_place(r,c);
                else
                    std::cout << this->b[r][c] << " ";
                if ( (c+1) % 3 == 0 )
                    std::cout << "| ";
            }
            if ( r==2 or r==5 )
                std::cout << "\n    |-------+-------+-------|"; 
            std::cout << "\n";
        }
        std::cout << "    +-------+-------+-------+\n";
    }
    
    else if(game_state == GameManager::CHECK)
    {
        std::cout << "\n|--------[ ACTION SCREEN ]--------|\n" << std::endl; 

        std::cout << "   ";
        for (short i {0}; i < 9; i++){
            if(i % 3 == 0)
                std::cout << "  ";
            std::cout <<" "<< i+1 ;
        }
        std::cout<<"\n";

        std::cout << "    +-------+-------+-------+\n";
        for ( short r{0} ; r < SIZE ; ++r )
        {
                std::cout << "  " << (r+1) << " | "; 
            for ( short c{0} ; c < SIZE ; ++c )
            {
                if ( this->b_check[r][c] <  0 && (this->b_check[r][c]*-1) == this->b[r][c])
                {
                    std::cout << Color::tcolor(std::to_string(this->b[r][c]), Color::GREEN) << " ";
                }
                else if(this->b_check[r][c] < 0 and b[r][c] > 0 and (this->b_check[r][c]*-1) != this->b[r][c])
                {
                    std::cout << Color::tcolor(std::to_string(this->b[r][c]), Color::RED) << " ";
                }
                else if(this->b_check[r][c] > 0)
                {
                    std::cout << this->b[r][c] << " ";
                }
                else
                {
                    std::cout << "  ";
                }
                if ( (c+1) % 3 == 0 )
                    std::cout << "| ";
            }
            if ( r==2 or r==5 )
                std::cout << "\n    |-------+-------+-------|"; 
            std::cout << "\n";
        }
        std::cout << "    +-------+-------+-------+\n";        
    }
    
    else if(game_state == GameManager::END_GAME)
    {
        this->m="Congratulations. you solved the puzzle! Press enter to continue.";
        std::cout << Color::tcolor("\n|--------[ ACTION SCREEN ]--------|\n", Color::BLUE) << std::endl; 

        std::cout << "  ";
        for (short i {0}; i < 9; i++){
            if(i % 3 == 0)
                std::cout << "  ";
            std::cout <<" "<< i+1 ;
        }
        std::cout<<"\n";

        std::cout << "   +-------+-------+-------+\n";
        for ( short r{0} ; r < SIZE ; ++r )
        {
                std::cout << " " << (r+1) << " | "; 
            for ( short c{0} ; c < SIZE ; ++c )
            {
                if ( this->b_check[r][c] <  0 && (this->b_check[r][c]*-1) == this->b[r][c])
                    std::cout << Color::tcolor(std::to_string(this->b[r][c]), Color::BLUE) << " ";
                else if(this->b_check[r][c] < 0 and b[r][c] > 0 and (this->b_check[r][c]*-1) != this->b[r][c])
                {
                    std::cout << Color::tcolor(std::to_string(this->b[r][c]), Color::RED) << " ";
                    this->m = "All the places are ocuped. But you don't solve the puzzle.";
                }
                else if(this->b_check[r][c] > 0)
                    std::cout << this->b[r][c] << " ";
                else
                    std::cout << "  ";
                if ( (c+1) % 3 == 0 )
                    std::cout << "| ";
            }
            if ( r==2 or r==5 )
                std::cout << "\n   |-------+-------+-------|"; 
            std::cout << "\n";
        }
        std::cout << "   +-------+-------+-------+\n";             
    }

}

void GameManager::render_game_intro()
{
    std::string initial_input;
    std::cout << 
        Color::tcolor(">>> Opening input file [",Color::GREEN) <<
        Color::tcolor(this->f, Color::GREEN) <<
        Color::tcolor("]", Color::GREEN) <<
    std::endl;
    std::cout << 
        Color::tcolor(">>> Processing data, please wait.",Color::GREEN) <<
    std::endl;
    std::cout <<
        Color::tcolor(">>> Finished reading input data file.\n",Color::GREEN) << 
    std::endl;

    std::cout << "========================================================" << std::endl;
    std::cout << "  Welcome to a terminal version of Sudoku, v1.0" << std::endl;
    std::cout << "  Copyright (C) 2020, Selan Rodrigues" << std::endl;
    std::cout << "========================================================\n" << std::endl;
    std::cout <<
        Color::tcolor("Press enter to start.",Color::BLINK) << 
    std::endl;
    std::getline(std::cin, initial_input);   
}

void render_command_line_help()
{
    std::cout << "Usage: sudoku [<options>] [<input_puzzle_file>]" << std::endl;
    std::cout << "  Game options:" << std::endl;
    std::cout <<"     --ncheck <num> Number of checks per game. Default = 3." << std::endl;
    std::cout <<"     --help         Print this help text." << std::endl;
}

void render_game_commands_sintax()
{
    std::cout << Color::tcolor("\nCommands syntax:", Color::GREEN) << std::endl;
    std::cout << 
        Color::tcolor("  'enter'(without typing anything)   --> go back to previous menu.",
        Color::GREEN) 
    << std::endl;
    std::cout <<
        Color::tcolor("  'p' <row> <col> <number> + 'enter' --> place <number> on board at location (<row>, <col>).",
        Color::GREEN) 
    << std::endl;
    std::cout << 
        Color::tcolor(
        "  'r' <row> <col> + 'enter'          --> remove number on board at location (<row>,<col>).",
        Color::GREEN) 
    << std::endl;
    std::cout << 
        Color::tcolor("  'c' + 'enter'                      --> check wich moves made are correct.",
        Color::GREEN) 
    << std::endl;
    std::cout <<
        Color::tcolor("  'u' + 'enter'                      --> undo last play.",
        Color::GREEN)
    << std::endl;
    std::cout <<
        Color::tcolor("   <row>, <col>, <number> must be in tange [1,9].\n",
        Color::GREEN)
    << std::endl;
    std::cout << Color::tcolor("Enter command > ", Color::YELLOW);
}

void render_game_options()
{
    std::cout << "1-Play 2-New Game 3-Quit  4-Help \n";
    std::cout << "Select option[1,4] > ";
}

void render_game_help()
{
        std::cout <<Color::tcolor( 
            "\n\n----------------------------------------------------------------------------",
            Color::GREEN) << 
        std::endl;
        
        std::cout <<Color::tcolor(
            "  The goal of Sudoku is to fill a 9x9 grid with numbers so that each row,",
            Color::GREEN) << 
        std::endl;
        std::cout << Color::tcolor (
            "  column and 3x3 section (nonet) contain all of digits between 1 an 9.\n",
            Color::GREEN)<< 
        std::endl;
        std::cout <<  Color::tcolor(
            "  The Sudoku rules are:",
            Color::GREEN)<< 
        std::endl;
        std::cout <<Color::tcolor(
            "  1. Each row, column, and nonet can contain each number (typically 1 to 9)",
            Color::GREEN)<< 
        std::endl;
        std::cout <<Color::tcolor(
            "     exactly once.",
            Color::GREEN)<< 
        std::endl;
        std::cout <<Color::tcolor(
            "  2. The sum of all numbers in any nonet, row, or column must be equal to 45.",
            Color::GREEN) << 
        std::endl;
        std::cout <<Color::tcolor(
            "----------------------------------------------------------------------------\n",
            Color::GREEN )<< 
        std::endl;
        std::cout << "Press enter to go back." << std::endl;    
}

void GameManager::render_message()
{   

    std::cout << 
        Color::tcolor
            (
                "MSG: [",
                Color::YELLOW
            ) << 
        Color::tcolor(this->m, Color::YELLOW, Color::REVERSE) <<
        Color::tcolor("]", Color::YELLOW)
    << std::endl;
}

void GameManager::render_checks_left()
{
    std::cout << 
        Color::tcolor("Checks left: [ ", Color::YELLOW) <<
        Color::tcolor(std::to_string(this->chk), Color::YELLOW) <<
        Color::tcolor(" ]", Color::YELLOW) 
    << std::endl;
}

void GameManager::render_digits_lefts()
{
    GameManager::handle_digits_left();
    std::cout << Color::tcolor("Digits left: [ ", Color::YELLOW);
    for(short i{0}; i < 9;i++){
        if(this->d[i] >= 9)
        {
            std::cout << "  ";
        }
        else
        {
            std::cout <<  Color::tcolor(std::to_string(i+1), Color::YELLOW) << " ";
        }
    }
    std::cout << Color::tcolor("]", Color::YELLOW)<< std::endl;    
}

void GameManager::render_screen()
{
    GameManager::render_board();
    GameManager::render_message();
   
    if(game_state == GameManager::CHECK or game_state == GameManager::ACTION or game_state == GameManager::PLAY)
    {
        GameManager::render_checks_left();
        GameManager::render_digits_lefts();
        render_game_commands_sintax();
    }
    else if(game_state == GameManager::START)
    {
        render_game_options();
    }
    else if(game_state == GameManager::HELP)
    {
        render_game_help();
    }
    else if(game_state == GameManager::NEW_GAME)
    {
        std::cout << "\nEnter choice[y/N] > ";
    }
    else if(game_state == GameManager::END_GAME)
    {
        GameManager::render_checks_left();
        GameManager::render_digits_lefts();
    }
}   


/***********************
 *  Main functions
 **********************/

void GameManager::initialize()
{
    game_state = GameManager::WELCOME;
    if(!handle_read_boards())
    {
        game_state = GameManager::QUIT;
        this->m= "Enter with a valid file!";
        return;
    }
    handle_load_board();
    this->i++;
    game_state = GameState::START;
    
}

void GameManager::render(){
    if(game_state == GameManager::READ_CMD or game_state == GameManager::READ_OPT)
        return;
    GameManager::render_screen();
}

void GameManager::process_events()
{
    if(game_state == GameManager::READ_OPT)
    {
        std::cin.clear();  
        // std::cin.ignore();
        std::getline(std::cin, this->o);  
    }
    else if(this->m != "" and game_state == GameManager::NEW_GAME)
    {
        std::cin.clear();
        // std::cin.ignore();
        std::getline(std::cin,this->new_g);            
    }
    else if(game_state == GameManager::READ_CMD)
    { 
        std::cin.clear(); 
        // std::cin.ignore();
        std::getline(std::cin, this->cmd);
    }
    
}

void GameManager::update()
{
    if(game_state == GameManager::START)
    {   
        this->m = "";
        game_state = GameManager::READ_OPT;
    }
    else if(game_state == GameManager::ACTION)
    {
        game_state =  GameManager::READ_CMD;
    }
    else if(game_state == GameManager::PLAY)
    {
        game_state =  GameManager::READ_CMD;
    }
    else if(game_state == GameManager::HELP)
    {
        game_state = GameManager::READ_OPT;    
    }
    else if(game_state == GameManager::READ_OPT)
    {
        if(this->o == "1")
        {
            game_state = GameManager::ACTION;
        }
        else if(this->o == "2")
        {
            GameManager::handle_new_game();
            game_state = GameManager::NEW_GAME;
        }
        else if(this->o == "3")
        {
            this->m = "Quiting game. Thank you for playing. See you next time.";
            game_state = GameManager::QUIT;
        }
        else if(this->o == "4")
        {
            game_state = GameManager::HELP;
        }
        else
        {
            game_state = GameManager::START;
        }
    }
    else if(game_state == GameManager::READ_CMD)
    {
        if(this->cmd[0] == 'p' or this->cmd[0] == 'r')
        {
            game_state = GameManager::PLAY;
            this->r = (this->cmd[2] - '0')-1;
            this->c = (this->cmd[4] - '0')-1;
            if(this->cmd[0] == 'p')
            {
                this->v = this->cmd[6] - '0';
                handle_load_board();
                GameManager::handle_place_value();

            }
            else if(this->cmd[0] == 'r')
            {
                handle_load_board();
                GameManager::handle_number_removal();
            }
            
        }
        else if(this->cmd[0] == 'c')
        {
            if(this->chk > 0)
            {
                this->m = "Checking done.";
                this->chk -= 1;
                game_state = GameManager::CHECK;

            }
            else
            {
                this->m = "You can't do this anymore.";
                game_state = GameManager::ACTION;
            }
        }
        else if(this->cmd[0] == 'u')
        {
            handle_load_board();
            this->m = "Undoing a PLACE action.";
            game_state = GameManager::U_LAST;            
        }
        else
        {
            this->m = "";
            GameManager::handle_load_board();
            game_state = GameManager::START;
        }
    }
    else if(game_state == GameManager::NEW_GAME)
    {
        if(this->m != "" and this->new_g == "y")
        {
            this->i++;
            if(this->i == this->bd.size())
                this->i = 0;
            handle_load_board();
            this->chk = this->check_backup;
            this->m = "New puzzle. Good Luck";
        }
        else if(this->new_g == "N")
        {
            this->m = "New Game command canceled.";
        }
        else
        {
            this->i++;

            if(this->i == this->bd.size())
                this->i = 0;
            handle_load_board();
            this->chk = this->check_backup;
            this->m = "";
        }
        game_state = GameState::START;
    }
    else if(game_state == GameManager::U_LAST)
    {
        handle_load_board();
        game_state = GameManager::ACTION;
    }
    else if(game_state == GameManager::CHECK)
    {
       game_state = GameManager::READ_CMD;
        this->m = "";
    }
    else if(game_state == GameManager::END_GAME)
    {
        game_state = GameManager::READ_CMD;
    }
    
}



