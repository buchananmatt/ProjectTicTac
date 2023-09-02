//
// MAIN.CPP [PROJECT TICTAC]
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


#include <curses.h>

void PrintBoard(WINDOW*, bool);

int main(int argc, char** argv) {

    initscr();                          // curses.h
    cbreak();                           // curses.h
    noecho();                           // curses.h
    keypad(stdscr, true);               // curses.h
//    start_color();

    WINDOW* win_title = newwin(7, 40, 2, 10);

    WINDOW* win_board = newwin(20, 40, 10, 10);

    WINDOW* win_turn = newwin(5, 40, 31, 10);

    WINDOW* win_score_game = newwin(7, 20, 2, 52);

    WINDOW* win_score_x = newwin(7, 20, 2, 74);

    WINDOW* win_score_o = newwin(7, 20, 2, 96);

    WINDOW* win_console = newwin(26, 64, 10, 52);

    WINDOW* win_help = newwin(18, 106, 37, 10);

    wborder(win_board, 0, 0, 0, 0, 0, 0, 0, 0);

    wborder(win_title, 0, 0, 0, 0, 0, 0, 0, 0);

    wborder(win_turn, 0, 0, 0, 0, 0, 0, 0, 0);

    wborder(win_score_game, 0, 0, 0, 0, 0, 0, 0, 0);

    wborder(win_score_x, 0, 0, 0, 0, 0, 0, 0, 0);

    wborder(win_score_o, 0, 0, 0, 0, 0, 0, 0, 0);

    wborder(win_console, 0, 0, 0, 0, 0, 0, 0, 0);

    wborder(win_help, 0, 0, 0, 0, 0, 0, 0, 0);

    PrintBoard(win_board, true);

    wmove(win_title, 3, 12);
    int x = waddstr(win_title, "PROJECT TIC TAC");

    wmove(win_turn, 2, 5);
    int y = waddstr(win_turn, "*** PLAYER 'X' TURN (YOU) ***");

    wmove(win_score_game, 2, 8);
    int z = waddstr(win_score_game, "GAME");

    wmove(win_score_game, 4, 7);
    int a = waddstr(win_score_game, "1 // 5");

    wmove(win_score_x, 2, 6);
    int b = waddstr(win_score_x, "'X' WINS");

    wmove(win_score_x, 4, 9);
    int c = waddstr(win_score_x, "2");

    wmove(win_score_o, 2, 6);
    int d = waddstr(win_score_o, "'Y' WINS");

    wmove(win_score_o, 4, 9);
    int e = waddstr(win_score_o, "1");

    PrintBoard(win_help, false);

//    wmove(win_help, 1, 37);
//    int j = waddstr(win_help, "[2023] [MATTHEW BUCHANAN] [BOCAN SOFTWARE]");

    wmove(win_help, 2, 37);
    int k = waddstr(win_help, "THE GAME IS TIC-TAC-TOE. FIRST TO GET THREE IN A ROW WINS THE MATCH.");

    wmove(win_help, 4, 37);
    int m = waddstr(win_help, "BEST 3 OUT OF FIVE MATCHES WINS THE GAME.");

    wmove(win_help, 6, 37);
    int n = waddstr(win_help, "PLAYER 'X' WILL TAKE THE FIRST MOVE OF THE FIRST MATCH.");

    wmove(win_help, 8, 37);
    a = waddstr(win_help, "THE FIRST PLAYER TO MOVE WILL ALTERNATE EVERY MATCH.");

    wmove(win_help, 10, 37);
    a = waddstr(win_help, "THE LOSING PLAYER WILL MOVE FIRST ON THE FIFTH MATCH.");

    wmove(win_help, 12, 37);
    int o = waddstr(win_help, "TO MOVE, ENTER THE CELL NUMBER IN THE CONSOLE AND PRESS 'ENTER'.");

//    wmove(win_help, 13, 37); 
//    a = waddstr(win_help, "LOCATION IN THE CONSOLE AND PRESS 'ENTER'.");

    wmove(win_help, 14, 37);
    a = waddstr(win_help, "[2023] [MATTHEW BUCHANAN] [BOCAN SOFTWARE]");

    wmove(win_console, 1, 1);
    int f = waddstr(win_console, "^[31>PLAYER 'X' TURN");

    wrefresh(win_board);
    wrefresh(win_title);
    wrefresh(win_turn);
    wrefresh(win_score_game);
    wrefresh(win_score_x);
    wrefresh(win_score_o);
    wrefresh(win_console);
    wrefresh(win_help);

    wmove(win_console, 24, 1);
    int g = waddch(win_console, '>');
    int h = wgetch(win_console);

    wmove(win_console, 2, 1);
    static_cast<void> ( waddch(win_console, static_cast<char> (h)) );

    static_cast<void> ( wgetch(win_console) );

    endwin();
/*                       *       *       *
                              1111111111222222
                     1234567890123456789012345                  

                 1   #########################
                 2   #       #       #       #
             *   3   #   1   #   2   #   3   #
                 4   #       #       #       #
                 5   #########################
                 6   #       #       #       #
             *   7   #   4   #   5   #   6   #
                 8   #       #       #       #
                 9   #########################
                10   #       #       #       #
             *  11   #   7   #   8   #   9   #
                12   #       #       #       #
                13   #########################
*/

	return 0;
}

void PrintBoard(WINDOW* win, bool game_flag) {
    
    int row_start;

    if(game_flag)   row_start = 2;
    else            row_start = 1;
    int column_start = 7;

    wmove(win, row_start+1, column_start);

    // print board row borders
    for(int j = 0; j < 25; j++) {
    
        waddch(win, '#'); 
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
        } else if(game_flag && (k == 5 || k == 13 || k == 21)) {

            waddch(win, ' ');
        } else if(!game_flag && k == 4) {

            waddch(win, '1');
        } else if(!game_flag && k == 12) {

            waddch(win, '2');
        } else if (!game_flag && k == 20) {

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
        } else if(game_flag && (k == 5 || k == 13 || k == 21)) {

            waddch(win, ' ');
        } else if(!game_flag && k == 4) {

            waddch(win, '4');
        } else if(!game_flag && k == 12) {

            waddch(win, '5');
        } else if (!game_flag && k == 20) {

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
        } else if(game_flag && (k == 5 || k == 13 || k == 21)) {

            waddch(win, ' ');
        } else if(!game_flag && k == 4) {

            waddch(win, '7');
        } else if(!game_flag && k == 12) {

            waddch(win, '8');
        } else if (!game_flag && k == 20) {

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
}