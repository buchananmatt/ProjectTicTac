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

//
//
//
bool Game::Start() {

    NewGame();
    console.ConsoleEvent(START_GAME);
    printer.RefreshScreen();

    return printer.GetPlayerInput();
}

//
//
//
void Game::GameLoop() {

    for(int i = 0; i < 5; i++) {

        // setup the match
        m_match = i + 1;
        bool player_x_final_match = false;

        // check to see who begins final match (5)
        if(m_match == 5 && m_x_wins < m_o_wins) 
            player_x_final_match = true;

        // match loop
        do {
            switch(m_match) {
                case 1:
                case 3:
                    Player_X_Turn();
                    Player_O_Turn();
                case 2:
                case 4:
                    Player_O_Turn();
                    Player_X_Turn();
                case 5:
                    if(player_x_final_match) {
                        Player_X_Turn();
                        Player_O_Turn();
                    } else {
                        Player_O_Turn();
                        Player_X_Turn();    
                    }
                default:
                    console.EventLog(ERROR);
            }
        } while(!MatchEnd());
    }
}

//
//
//
bool Game::EndGame() {


}

//
//
//
void Game::NewGame() {

    m_match = 0;
    m_x_wins = 0;
    m_o_wins = 0;
    m_player_turn = 0;

    for(auto& p : board) {
        p = nullptr;
    }
}

//
//
//
void Game::Player_X_Turn() {
    console.EventLog(PLAYER_X_TURN);
    char move = printer.GetPlayerInput();

}

//
//
//
void Game::Player_O_Turn() {
    console.EventLog(PLAYER_O_TURN);
    char move = computer.Move();

}

//
//
//
void Game::MatchEnd() {


}