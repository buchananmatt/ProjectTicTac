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


namespace bocan {

class Printer {
public:
    
    Printer();
    ~Printer();

    void RefreshScreen();

    void RefreshBoard();
    void RefreshConsole();
    void RefreshScore();

    char GetConsoleInput();
    void ConsoleOutput(int);

private:

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

    enum board_type {
        HELP_BOARD,
        GAME_BOARD
    } m_board_type;

    std::queue<std::string> m_console_lines;

    int m_max_queue_size;

private:

    void PrintTitle();
    void PrintScore();
    void PrintBoard(int);
    void PrintConsole();
    void PrintTurn();
    void PrintHelp();

};

} // NAMESPACE BOCAN