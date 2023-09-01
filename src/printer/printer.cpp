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

#include <queue>
#include <string>

#include <ncurses.h>

#include "../game/game.hpp"
#include "../game/gamestate.hpp"
#include "../printer/printer.hpp"

using bocan::Printer;

// brief Singleton instance of the printer class object.
Printer Printer::s_instance;

// brief
// brief
// brief
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

    m_max_console_size = m_console.y_height - 2;

    initscr();
    cbreak(); 
    noecho();
    keypad(stdscr, true);

    win_title = newwin(m_title.y_height, m_title.x_length, m_title.y_origin, m_title.x_origin);
    win_board = newwin(m_board.y_height, m_board.x_length, m_board.y_origin, m_board.x_origin);
    win_turn = newwin(m_turn.y_height, m_turn.x_length, m_turn.y_origin, m_turn.x_origin);
    win_score_game = newwin(m_score_game.y_height, m_score_game.x_length, m_score_game.y_origin, m_score_game.x_origin);
    win_score_x = newwin(m_score_x.y_height, m_score_x.x_length, m_score_x.y_origin, m_score_x.x_origin);
    win_score_o = newwin(m_score_o.y_height, m_score_o.x_length, m_score_o.y_origin, m_score_o.x_origin);
    win_console = newwin(m_console.y_height, m_console.x_length, m_console.y_origin, m_console.x_origin);
    win_help = newwin(m_help.y_height, m_help.x_length, m_help.y_origin, m_help.x_origin);

    wborder(win_board, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_title, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_turn, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_score_game, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_score_x, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_score_o, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_console, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_help, 0, 0, 0, 0, 0, 0, 0, 0);
}

//
//
//
void Printer::ResetScreen() {


}

//
//
//
void Printer::RefreshScreen() {

    PrintTitle();
    PrintScore();
    PrintBoard(GAME_BOARD);
    PrintConsole();
    PrintTurn();
    PrintHelp();
}

//
//
//
char Printer::GetConsoleInput() {

    wmove(win_console, 24, 1);
    static_cast<void> ( waddch(win_console, '>') );
    int input = wgetch(win_console);

    return static_cast<char> (input);
}

void Printer::SetConsoleOutput(int event) {
    switch(event) {
        case START_GAME:

        case PLAYER_O_TURN:
        
        case PLAYER_X_TURN:
        
        case PLAYER_O_MOVE:
        
        case PLAYER_X_MOVE:
        
        case PLAYER_O_MATCH_WIN:
        
        case PLAYER_X_MATCH_WIN:
        
        case MATCH_TIE:
        
        case PLAYER_O_GAME_WIN:
        
        case PLAYER_X_GAME_WIN:
        
        case END_GAME:
        
        case INVALID_MOVE:

        case ERROR:

    }
}

//
//
//
void Printer::PrintTitle() {

    wmove(win_title, 3, 12);
    static_cast<void> ( waddstr(win_title, "PROJECT TIC TAC") );
    wrefresh(win_title);
}

//
//
//
void Printer::PrintScore() {

    wrefresh(win_score_game);
    wrefresh(win_score_x);
    wrefresh(win_score_o);
}

//
//
//
void Printer::PrintBoard(int board_type) {

    WINDOW* win;
    int row_start;

    if(GAME_BOARD) {  
        win = win_board;
        row_start = 2;
    } else {
        win = win_help;
        row_start = 1;
    }

    int column_start = 7;

    wmove(win, row_start+1, column_start);

    // print board row borders
    for(int j = 0; j < 25; j++) {
    
        waddch(win_board, '#'); 
    }


    wmove(win, row_start+2, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');
        } else {

            waddch(win, ' ');
        }
    }

    wmove(win, row_start+3, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');
        } else if(GAME_BOARD && (k == 5 || k == 13 || k == 21)) {

            waddch(win, ' ');
        } else if(HELP_BOARD && k == 4) {

            waddch(win, '1');
        } else if(HELP_BOARD && k == 12) {

            waddch(win, '2');
        } else if(HELP_BOARD && k == 20) {

            waddch(win, '3');
        } else {

            waddch(win, ' ');
        }
    }

    wmove(win, row_start+4, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');
        } else {

            waddch(win, ' ');
        }
    }

    wmove(win, row_start+5, column_start);

    // print board row borders
    for(int j = 0; j < 25; j++) {
    
        waddch(win, '#'); 
    }

    wmove(win, row_start+6, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');
        } else {

            waddch(win, ' ');
        }
    }

    wmove(win, row_start+7, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');
        } else if(GAME_BOARD && (k == 5 || k == 13 || k == 21)) {

            waddch(win, ' ');
        } else if(HELP_BOARD && k == 4) {

            waddch(win, '4');
        } else if(HELP_BOARD && k == 12) {

            waddch(win, '5');
        } else if(HELP_BOARD && k == 20) {

            waddch(win, '6');
        } else {

            waddch(win, ' ');
        }
    }

    wmove(win, row_start+8, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');
        } else {

            waddch(win, ' ');
        }
    }

    wmove(win, row_start+9, column_start);

    // print board row borders
    for(int j = 0; j < 25; j++) {
    
        waddch(win, '#'); 
    }

    wmove(win, row_start+10, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');
        } else {

            waddch(win, ' ');
        }
    }

    wmove(win, row_start+11, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');
        } else if(GAME_BOARD && (k == 5 || k == 13 || k == 21)) {

            waddch(win, ' ');
        } else if(HELP_BOARD && k == 4) {

            waddch(win, '7');
        } else if(HELP_BOARD && k == 12) {

            waddch(win, '8');
        } else if (HELP_BOARD && k == 20) {

            waddch(win, '9');
        } else {

            waddch(win, ' ');
        }
    }

    wmove(win, row_start+12, column_start);

    // print board column borders
    for(int k = 0; k < 25; k++) {

        if(k == 0 || k == 8 || k == 16 || k == 24) {

            waddch(win, '#');
        } else {

            waddch(win, ' ');
        }
    }

    wmove(win, row_start+13, column_start);

    // print board row borders
    for(int j = 0; j < 25; j++) {
    
        waddch(win, '#'); 
    }

    wrefresh(win_board);
}

//
//
//
void Printer::PrintConsole() {

    wrefresh(win_console);
}

//
//
//
void Printer::PrintTurn() {

    wmove(win_turn, 2, 5);

    switch(bocan::Game::Get().m_player_turn) {
        case PLAYER_X_TURN:
            static_cast<void> ( waddstr(win_turn, "*** PLAYER 'X' TURN (YOU) ***") );
            break;
        case PLAYER_O_TURN:
            static_cast<void> ( waddstr(win_turn, "*** PLAYER 'O' TURN (CPU) ***") );
            break;
        default:
            static_cast<void> ( waddstr(win_turn, "***  ERROR  ERROR  ERROR  ***") );
    }

    wrefresh(win_turn);
}

//
//
//
void Printer::PrintHelp() {

    PrintBoard(HELP_BOARD);

    wmove(win_help, 2, 37);
    static_cast<void> ( waddstr(win_help, "THE GAME IS TIC-TAC-TOE. FIRST TO GET THREE IN A ROW WINS THE MATCH.") );

    wmove(win_help, 4, 37);
    static_cast<void> ( waddstr(win_help, "BEST 3 OUT OF FIVE MATCHES WINS THE GAME.") );

    wmove(win_help, 6, 37);
    static_cast<void> ( waddstr(win_help, "PLAYER 'X' WILL TAKE THE FIRST MOVE OF THE FIRST MATCH.") );

    wmove(win_help, 8, 37);
    static_cast<void> ( waddstr(win_help, "THE FIRST PLAYER TO MOVE WILL ALTERNATE EVERY MATCH.") );

    wmove(win_help, 10, 37);
    static_cast<void> ( waddstr(win_help, "THE LOSING PLAYER WILL MOVE FIRST ON THE FIFTH MATCH.") );

    wmove(win_help, 12, 37);
    static_cast<void> ( waddstr(win_help, "TO MOVE, ENTER THE CELL NUMBER IN THE CONSOLE AND PRESS 'ENTER'.") );

    wrefresh(win_help);
}