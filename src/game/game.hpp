//
// GAME.HPP [PROJECT TICTAC]
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

#ifndef GAME_HPP
#define GAME_HPP

#include <array>

#include "../printer/printer.hpp"

namespace bocan {

class Game {
public:

    static Game& Get() { return s_instance; }

    void Start();
    void GameLoop();
    bool EndGame();

private:

    static Game s_instance;

    friend class Printer;

    Printer& printer = Printer::Get();

    std::array<int, 9> board;

    bool m_first_run = true;

    int m_match_end;
    int m_player_turn;
    int m_match;
    int m_x_wins;
    int m_o_wins;
   
private:

    Game() {}
    Game(const Game&) = delete;
    ~Game() {}

    void Player_X_Turn();
    void Player_O_Turn();
    void Check_Match_Win();
};

} // NAMESPACE BOCAN

#endif // CALCULATOR_HPP