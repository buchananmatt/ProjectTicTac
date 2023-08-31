//
// GAME.CPP [PROJECT TICTAC]
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

#include "../computer/computer.hpp"
#include "../console/console.hpp"
#include "../game/game.hpp"
#include "../printer/printer.hpp"

using bocan::Game;

// brief Singleton instance of the Game class object.
Game Game::s_instance;

bool Game::Start() {

    NewGame();
    console.ConsoleEvent(START_GAME);
    printer.RefreshScreen();
}

void Game::GameLoop() {


}

bool Game::EndGame() {


}

void Game::NewGame() {

    m_match = 0;
    m_x_wins = 0;
    m_o_wins = 0;
    m_player_turn = 0;
}