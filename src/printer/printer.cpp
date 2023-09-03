//
// PRINTER.CPP [PROJECT TICTAC]
// C++ VERSION GNU++14
// macOS 11.7.9
// DUAL-CORE INTEL CORE i5 @ 2.8 GHZ
//
// GITHUB REPOSITORY https://github.com/buchananmatt/ProjectTicTac.git
//
// COPYRIGHT [2023] [MATTHEW T. BUCHANAN] [BOCAN SOFTWARE]
//
// LICENSED UNDER THE APACHE LICENSE, VERSION 2.0 (THE "LICENSE");
// YOU MAY NOT USE THIS FILE EXCEPT IN COMPLIANCE WITH THE LICENSE.
// YOU MAY OBTAIN A COPY OF THE LICENSE AT 
//
// http://www.apacher.org/licenses.LICENSE-2.0
//
// UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING, SOFTWARE
// DISTRIBUTED UNDER THE LICENSE IS DISTRIBUTED ON AN "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
// SEE THE LICENSE FOR THE SPECIFIC LANGUAGE GOVERNING PERMISSIONS AND
// LIMITATIONS UNDER THE LICENSE.

#include <deque>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

#include <ncurses.h>

#include "../game/game.hpp"
#include "../game/gamestate.hpp"
#include "../printer/printer.hpp"

using bocan::tictac::Printer;

// brief Singleton instance of the printer class object.
Printer Printer::s_instance;

// brief Performs initial setup of window output.
// param None.
// return None.
void Printer::SetupScreen() {

    m_title.y_origin = 2;
    m_title.x_origin = 10;
    m_title.y_height = 7;
    m_title.x_length = 40;

    m_board.y_origin = 10;
    m_board.x_origin = 10;
    m_board.y_height = 20;
    m_board.x_length = 40;

    m_turn.y_origin = 31;
    m_turn.x_origin = 10;
    m_turn.y_height = 5;
    m_turn.x_length = 40;

    m_score_game.y_origin = 2;
    m_score_game.x_origin = 52;
    m_score_game.y_height = 7;
    m_score_game.x_length = 20;

    m_score_x.y_origin = 2;
    m_score_x.x_origin = 74;
    m_score_x.y_height = 7;
    m_score_x.x_length = 20;

    m_score_o.y_origin = 2;
    m_score_o.x_origin = 96;
    m_score_o.y_height = 7;
    m_score_o.x_length = 20;

    m_console.y_origin = 10;
    m_console.x_origin = 52;
    m_console.y_height = 26;
    m_console.x_length = 64;

    m_help.y_origin = 37;
    m_help.x_origin = 10;
    m_help.y_height = 18;
    m_help.x_length = 106;

    m_max_console_size = m_console.y_height - 5;

    initscr();                                          //curses.h
    cbreak();                                           //curses.h
    noecho();                                           //curses.h
    keypad(stdscr, true);                               //curses.h

    win_title = newwin(m_title.y_height, m_title.x_length, m_title.y_origin, m_title.x_origin);                             //curses.h
    win_board = newwin(m_board.y_height, m_board.x_length, m_board.y_origin, m_board.x_origin);                             //curses.h
    win_turn = newwin(m_turn.y_height, m_turn.x_length, m_turn.y_origin, m_turn.x_origin);                                  //curses.h
    win_score_game = newwin(m_score_game.y_height, m_score_game.x_length, m_score_game.y_origin, m_score_game.x_origin);    //curses.h
    win_score_x = newwin(m_score_x.y_height, m_score_x.x_length, m_score_x.y_origin, m_score_x.x_origin);                   //curses.h
    win_score_o = newwin(m_score_o.y_height, m_score_o.x_length, m_score_o.y_origin, m_score_o.x_origin);                   //curses.h
    win_console = newwin(m_console.y_height, m_console.x_length, m_console.y_origin, m_console.x_origin);                   //curses.h
    win_help = newwin(m_help.y_height, m_help.x_length, m_help.y_origin, m_help.x_origin);                                  //curses.h

    wborder(win_board, 0, 0, 0, 0, 0, 0, 0, 0);         //curses.h
    wborder(win_title, 0, 0, 0, 0, 0, 0, 0, 0);         //curses.h
    wborder(win_turn, 0, 0, 0, 0, 0, 0, 0, 0);          //curses.h
    wborder(win_score_game, 0, 0, 0, 0, 0, 0, 0, 0);    //curses.h
    wborder(win_score_x, 0, 0, 0, 0, 0, 0, 0, 0);       //curses.h
    wborder(win_score_o, 0, 0, 0, 0, 0, 0, 0, 0);       //curses.h
    wborder(win_console, 0, 0, 0, 0, 0, 0, 0, 0);       //curses.h
    wborder(win_help, 0, 0, 0, 0, 0, 0, 0, 0);          //curses.h
}

// brief Resets the screen to start game state.
// param None.
// return None.
void Printer::ResetScreen() {

    // clear the console queue
    m_console_queue.clear();
}

// brief Reprints all windows on the screen.
// param None.
// return None.
void Printer::RefreshScreen() {

    PrintTitle();
    PrintScore();
    PrintBoard(GAME_BOARD);
    PrintConsole();
    PrintTurn();
    PrintHelp();
}

// brief Tears down and deallocates window memory.
// param None.
// return None.
void Printer::ExitScreen() {

    delwin(win_board);                                  //curses.h
    delwin(win_title);                                  //curses.h
    delwin(win_turn);                                   //curses.h
    delwin(win_score_game);                             //curses.h
    delwin(win_score_x);                                //curses.h
    delwin(win_score_o);                                //curses.h
    delwin(win_console);                                //curses.h
    delwin(win_help);                                   //curses.h
    endwin();                                           //curses.h
}

// brief Receives the user input through the console interface.
// param None.
// return Character representing user input.
char Printer::GetConsoleInput() {

    wmove(win_console, 24, 1);                          //curses.h
    static_cast<void> ( waddch(win_console, '>') );     //curses.h
    int input = wgetch(win_console);                    //curses.h

    return static_cast<char> (input);
}

// brief Pushes console message related to the game event state to the console queue.
// brief Pops elements from queue to ensure queue is correct size for output.
// param[in] Integer representing event state enumerator.
// return None.
void Printer::SetConsoleOutput(int event) {
    std::ostringstream output;
    switch(event) {
        case START_GAME:
            output << ">PRESS ANY KEY TO START THE GAME.";
            m_console_queue.push_back(output.str());
            break;
        case PLAYER_O_TURN:
            PrintTurn();
            output << ">WAITING FOR PLAYER 'O'...";
            m_console_queue.push_back(output.str());
            break;
        case PLAYER_X_TURN:
            PrintTurn();
            output << ">WAITING FOR PLAYER 'X'...";
            m_console_queue.push_back(output.str());
            break;
        case PLAYER_O_MATCH_WIN:
            output << ">PLAYER 'O' WINS MATCH " << bocan::tictac::Game::Get().m_match << ".";
            m_console_queue.push_back(output.str());
            break;
        case PLAYER_X_MATCH_WIN:
            output << ">PLAYER 'X' WINS MATCH " << bocan::tictac::Game::Get().m_match << ".";
            m_console_queue.push_back(output.str());
            break;
        case MATCH_TIE:
            output << ">MATCH " << bocan::tictac::Game::Get().m_match << " IS A TIE!";
            m_console_queue.push_back(output.str());
            break;
        case PLAYER_O_GAME_WIN:
            output << ">PLAYER 'O' WINS THE GAME!";
            m_console_queue.push_back(output.str());
            break;
        case PLAYER_X_GAME_WIN:
            output << ">PLAYER 'X' WINS THE GAME!";
            m_console_queue.push_back(output.str());
            break;
        case GAME_TIE:
            output << ">THE GAME IS A TIE!";
            m_console_queue.push_back(output.str());
            break;
        case END_GAME:
            output << ">DO YOU WANT TO PLAY AGAIN? (Y/N).";
            m_console_queue.push_back(output.str());
            break;
        case PLAYER_QUIT:
            output << ">PLAYER 'X' QUIT THE GAME.";
            m_console_queue.push_back(output.str());
            break;
        case INVALID_MOVE:
            output << ">INVALID MOVE. TRY AGAIN.";
            m_console_queue.push_back(output.str());
            break;
        case INVALID_INPUT:
            output << ">INVALID INPUT.";
            m_console_queue.push_back(output.str());
            break;
        case GAME_EXIT:
            output << ">EXITING GAME...";
            m_console_queue.push_back(output.str());
            break;
        case ERROR:
            output << ">CRITICAL RUNTIME ERROR...";
            m_console_queue.push_back(output.str());
            break;
    }
    while(m_console_queue.size() > m_max_console_size) {
        m_console_queue.pop_front();
    }
    PrintConsole();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// brief Pushes console message related to the game event state to the console queue.
// brief Ensures console queue is correct size and prints the console window.
// param[in] Integer representing event state enumerator.
// param[in] Integer representing the position that was just played.
// return None.
void Printer::SetConsoleOutput(int event, int pos) {
    std::ostringstream output;
    switch(event) {
        case PLAYER_O_MOVE:
            output << ">PLAYER 'O' MOVES TO POSITION " << pos << ".";
            m_console_queue.push_back(output.str());
            break;
        case PLAYER_X_MOVE:
            output << ">PLAYER 'X' MOVES TO POSITION " << pos << ".";
            m_console_queue.push_back(output.str());
            break;
    }
    while(m_console_queue.size() > m_max_console_size) {
        m_console_queue.pop_front();
    }
    PrintConsole();
    PrintBoard(GAME_BOARD);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// brief Prints the title window.
// param None.
// return None.
void Printer::PrintTitle() {

    wmove(win_title, 3, 12);                                        //curses.h
    static_cast<void> ( waddstr(win_title, "PROJECT TIC TAC") );    //curses.h
    wrefresh(win_title);                                            //curses.h
}

// brief Prints the game index and player score windows.
// param None.
// return None.
void Printer::PrintScore() {

    wmove(win_score_game, 2, 8);                                    //curses.h
    static_cast<void> ( waddstr(win_score_game, "GAME") );          //curses.h

    wmove(win_score_game, 4, 7);                                    //curses.h
    char c_match = bocan::tictac::Game::Get().m_match + '0';                //curses.h
    static_cast<void> ( waddch(win_score_game, c_match) );          //curses.h
    static_cast<void> ( waddstr(win_score_game, " // 5") );         //curses.h

    wmove(win_score_x, 2, 6);                                       //curses.h
    static_cast<void> ( waddstr(win_score_x, "'X' WINS") );         //curses.h

    wmove(win_score_x, 4, 9);                                       //curses.h
    char c_x_wins = bocan::tictac::Game::Get().m_x_wins + '0';              //curses.h
    static_cast<void> ( waddch(win_score_x, c_x_wins) );            //curses.h

    wmove(win_score_o, 2, 6);                                       //curses.h
    static_cast<void> ( waddstr(win_score_o, "'O' WINS") );         //curses.h

    wmove(win_score_o, 4, 9);                                       //curses.h
    char c_o_wins = bocan::tictac::Game::Get().m_o_wins + '0';              //curses.h
    static_cast<void> ( waddch(win_score_o, c_o_wins) );            //curses.h

    wrefresh(win_score_game);                                       //curses.h
    wrefresh(win_score_x);                                          //curses.h
    wrefresh(win_score_o);                                          //curses.h
}           

// brief Prints the tic-tac-toe board in both the board window and help window.
// param[in] Integer representing board type enumerator.
// return None.
void Printer::PrintBoard(int board_type) { 

    WINDOW* win;                                                    //curses.h
    int row_start;

    if(board_type == GAME_BOARD) {  
        win = win_board;
        row_start = 2;
    } else {
        win = win_help;
        row_start = 1;
    }

    int column_start = 7;

    wmove(win, row_start+1, column_start);                          //curses.h

    // print board row borders
    for(int j = 0; j < 25; j++) {
    
        waddch(win, '#');                                           //curses.h
    }


    wmove(win, row_start+2, column_start);                          //curses.h

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');                                       //curses.h
        } else {

            waddch(win, ' ');                                       //curses.h
        }
    }

    wmove(win, row_start+3, column_start);                          //curses.h

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');                                       //curses.h
        } else if(board_type == GAME_BOARD && k == 4) {
            switch(bocan::tictac::Game::Get().board.at(0)) {
                case EMPTY:
                    waddch(win, ' ');                               //curses.h
                    break;
                case PLAYER_X_POS:
                    waddch(win, 'X');                               //curses.h
                    break;
                case PLAYER_O_POS:
                    waddch(win, 'O');                               //curses.h
                    break;
            }
        } else if(board_type == GAME_BOARD && k == 12) {
            switch(bocan::tictac::Game::Get().board.at(1)) {
                case EMPTY:
                    waddch(win, ' ');                               //curses.h
                    break;
                case PLAYER_X_POS:
                    waddch(win, 'X');                               //curses.h
                    break;
                case PLAYER_O_POS:
                    waddch(win, 'O');                               //curses.h
                    break;
            }
        } else if(board_type == GAME_BOARD && k == 20) {
            switch(bocan::tictac::Game::Get().board.at(2)) {
                case EMPTY:
                    waddch(win, ' ');                               //curses.h
                    break;
                case PLAYER_X_POS:
                    waddch(win, 'X');                               //curses.h
                    break;
                case PLAYER_O_POS:
                    waddch(win, 'O');                               //curses.h
                    break;
            }
        } else if(board_type == HELP_BOARD && k == 4) {

            waddch(win, '1');                                       //curses.h
        } else if(board_type == HELP_BOARD && k == 12) {

            waddch(win, '2');                                       //curses.h
        } else if(board_type == HELP_BOARD && k == 20) {

            waddch(win, '3');                                       //curses.h
        } else {

            waddch(win, ' ');                                       //curses.h
        }
    }

    wmove(win, row_start+4, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');                                       //curses.h
        } else {

            waddch(win, ' ');                                       //curses.h
        }
    }

    wmove(win, row_start+5, column_start);

    // print board row borders
    for(int j = 0; j < 25; j++) {
    
        waddch(win, '#');                                           //curses.h
    }

    wmove(win, row_start+6, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');                                       //curses.h
        } else {

            waddch(win, ' ');                                       //curses.h
        }
    }

    wmove(win, row_start+7, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');                                       //curses.h
        } else if(board_type == GAME_BOARD && k == 4) {
            switch(bocan::tictac::Game::Get().board.at(3)) {
                case EMPTY:
                    waddch(win, ' ');                               //curses.h
                    break;
                case PLAYER_X_POS:
                    waddch(win, 'X');                               //curses.h
                    break;
                case PLAYER_O_POS:
                    waddch(win, 'O');                               //curses.h
                    break;
            }
        } else if(board_type == GAME_BOARD && k == 12) {
            switch(bocan::tictac::Game::Get().board.at(4)) {
                case EMPTY:
                    waddch(win, ' ');                               //curses.h
                    break;
                case PLAYER_X_POS:
                    waddch(win, 'X');                               //curses.h
                    break;
                case PLAYER_O_POS:
                    waddch(win, 'O');                               //curses.h
                    break;
            }
        } else if(board_type == GAME_BOARD && k == 20) {
            switch(bocan::tictac::Game::Get().board.at(5)) {
                case EMPTY:
                    waddch(win, ' ');                               //curses.h
                    break;
                case PLAYER_X_POS:
                    waddch(win, 'X');                               //curses.h
                    break;
                case PLAYER_O_POS:
                    waddch(win, 'O');                               //curses.h
                    break;
            }
        } else if(board_type == HELP_BOARD && k == 4) {

            waddch(win, '4');                                       //curses.h
        } else if(board_type == HELP_BOARD && k == 12) {

            waddch(win, '5');                                       //curses.h
        } else if(board_type == HELP_BOARD && k == 20) {

            waddch(win, '6');                                       //curses.h
        } else {

            waddch(win, ' ');                                       //curses.h
        }
    }

    wmove(win, row_start+8, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');                                       //curses.h
        } else {

            waddch(win, ' ');                                       //curses.h
        }
    }

    wmove(win, row_start+9, column_start);

    // print board row borders
    for(int j = 0; j < 25; j++) {
    
        waddch(win, '#');                                           //curses.h
    }

    wmove(win, row_start+10, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');                                       //curses.h
        } else {

            waddch(win, ' ');                                       //curses.h
        }
    }

    wmove(win, row_start+11, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');                                       //curses.h
        } else if(board_type == GAME_BOARD && k == 4) {
            switch(bocan::tictac::Game::Get().board.at(6)) {
                case EMPTY:
                    waddch(win, ' ');                               //curses.h
                    break;
                case PLAYER_X_POS:
                    waddch(win, 'X');                               //curses.h
                    break;
                case PLAYER_O_POS:
                    waddch(win, 'O');                               //curses.h
                    break;
            }
        } else if(board_type == GAME_BOARD && k == 12) {
            switch(bocan::tictac::Game::Get().board.at(7)) {
                case EMPTY:
                    waddch(win, ' ');                               //curses.h
                    break;
                case PLAYER_X_POS:
                    waddch(win, 'X');                               //curses.h
                    break;
                case PLAYER_O_POS:
                    waddch(win, 'O');                               //curses.h
                    break;
            }
        } else if(board_type == GAME_BOARD && k == 20) {
            switch(bocan::tictac::Game::Get().board.at(8)) {
                case EMPTY:
                    waddch(win, ' ');                               //curses.h
                    break;
                case PLAYER_X_POS:
                    waddch(win, 'X');                               //curses.h
                    break;  
                case PLAYER_O_POS:
                    waddch(win, 'O');                               //curses.h
                    break;
            }
        } else if(board_type == HELP_BOARD && k == 4) {

            waddch(win, '7');                                       //curses.h
        } else if(board_type == HELP_BOARD && k == 12) {

            waddch(win, '8');                                       //curses.h
        } else if (board_type == HELP_BOARD && k == 20) {

            waddch(win, '9');                                       //curses.h
        } else {

            waddch(win, ' ');                                       //curses.h
        }
    }

    wmove(win, row_start+12, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');                                       //curses.h
        } else {

            waddch(win, ' ');                                       //curses.h
        }
    }

    wmove(win, row_start+13, column_start);

    // print board row borders
    for(int j = 0; j < 25; j++) {
    
        waddch(win, '#');                                           //curses.h
    }

    wrefresh(win);                                                  //curses.h
}

// brief Prints the console queue to the console window.
// param None.
// return None.
void Printer::PrintConsole() {

    werase(win_console);                                                                        //curses.h
    wborder(win_console, 0, 0, 0, 0, 0, 0, 0, 0);                                               //curses.h

    wmove(win_console, 1, 1);                                                                   //curses.h
    static_cast<void> ( waddstr(win_console, ">[2023] [MATTHEW BUCHANAN] [BOCAN SOFTWARE]") );  //curses.h

    int i = 2;

    for(auto s : m_console_queue) {
        wmove(win_console, i, 1);                                                               //curses.h
        static_cast<void> ( waddstr(win_console, s.c_str()) );                                  //curses.h
        i++;
    }
    wrefresh(win_console);                                                                      //curses.h
}

// brief Prints the player turn window.
// param None.
// return None.
void Printer::PrintTurn() {

    wmove(win_turn, 2, 5);                                                                      //curses.h

    switch(bocan::tictac::Game::Get().m_player_turn) {
        case START_GAME:
            static_cast<void> ( waddstr(win_turn, " ") );                                       //curses.h
            break;
        case PLAYER_X_TURN:
            static_cast<void> ( waddstr(win_turn, "*** PLAYER 'X' TURN (YOU) ***") );           //curses.h
            break;
        case PLAYER_O_TURN:
            static_cast<void> ( waddstr(win_turn, "*** PLAYER 'O' TURN (CPU) ***") );           //curses.h
            break;
        default:
            static_cast<void> ( waddstr(win_turn, "***  ERROR  ERROR  ERROR  ***") );           //curses.h
    }

    wrefresh(win_turn);                                                                         //curses.h
}

// brief Prints the help window.
// param None.
// return None.
void Printer::PrintHelp() {

    PrintBoard(HELP_BOARD);

    wmove(win_help, 2, 37);                                                                                             //curses.h
    static_cast<void> ( waddstr(win_help, "ABOUT THE GAME:") );                                                         //curses.h

    wmove(win_help, 4, 37);                                                                                             //curses.h
    static_cast<void> ( waddstr(win_help, "THE GAME IS TIC-TAC-TOE. FIRST TO GET THREE IN A ROW WINS THE MATCH.") );    //curses.h

    wmove(win_help, 6, 37);                                                                                             //curses.h
    static_cast<void> ( waddstr(win_help, "BEST THREE OUT OF FIVE MATCHES WINS THE GAME.") );                           //curses.h

    wmove(win_help, 8, 37);                                                                                             //curses.h
    static_cast<void> ( waddstr(win_help, "THE FIRST TURN TO MOVE WILL ALTERNATE EVERY MATCH.") );                      //curses.h

    wmove(win_help, 10, 37);                                                                                            //curses.h
    static_cast<void> ( waddstr(win_help, "PLAYER 'X' STARTS THE FIRST MATCH.") );                                      //curses.h

    wmove(win_help, 12, 37);                                                                                            //curses.h
    static_cast<void> ( waddstr(win_help, "TO MOVE, ENTER THE CORRESPONDING CELL NUMBER IN THE CONSOLE.") );            //curses.h

    wmove(win_help, 14, 37);                                                                                            //curses.h
    static_cast<void> ( waddstr(win_help, "TO QUIT THE GAME AT ANYTIME, PRESS 'Q'.") );                                 //curses.h

    wrefresh(win_help);                                                                                                 //curses.h
}