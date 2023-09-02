//
// PRINTER.HPP [PROJECT TICTAC]
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

#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <deque>
#include <string>

#include <ncurses.h>

class deque;
class string;

namespace bocan {

class Printer {
public:
    
    static Printer& Get() { return s_instance; }

    void SetupScreen();
    void ResetScreen();
    void RefreshScreen();
    void ExitScreen();

    char GetConsoleInput();
    void SetConsoleOutput(int);
    void SetConsoleOutput(int, int);

private:

    static Printer s_instance;

    std::deque<std::string> m_console_queue;

    int m_max_console_size;

    WINDOW* win_title;
    WINDOW* win_board;
    WINDOW* win_turn;
    WINDOW* win_score_game;
    WINDOW* win_score_x;
    WINDOW* win_score_o;
    WINDOW* win_console;
    WINDOW* win_help;

    struct window_metrics {
        int y_origin;
        int x_origin;
        int y_height;
        int x_length;
    }
        m_title,
        m_board,
        m_turn,
        m_score_game,
        m_score_x,
        m_score_o,
        m_console,
        m_help;

private:

    Printer() {}
    Printer(const Printer&) = delete;
    ~Printer() {}

    void PrintTitle();
    void PrintScore();
    void PrintBoard(int);
    void PrintConsole();
    void PrintTurn();
    void PrintHelp();

};

} // NAMESPACE BOCAN

#endif // PRINTER_HPP