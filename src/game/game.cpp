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

#include <array>

#include "../game/game.hpp"
#include "../game/gamestate.hpp"
#include "../printer/printer.hpp"

using bocan::Game;

// brief Singleton instance of the Game class object.
Game Game::s_instance;

//
//
//
bool Game::Start() {

    // setup the screen for the first game
    if(m_first_run) {
        printer.SetupScreen();
        m_first_run = false;
    }

    // reset game state
    m_player_turn = START_GAME;
    m_match = 0;
    m_x_wins = 0;
    m_o_wins = 0;

    // reset board state
    for(auto& i : board) {
        i = EMPTY;
    }

    // reset the screen
    printer.ResetScreen();
    printer.RefreshScreen();
    printer.SetConsoleOutput(START_GAME);

    // wait for start from the user
    return printer.GetConsoleInput();
}

//
//
//
void Game::GameLoop() {

    // game is setup for five matches
    for(int i = 0; i < 5; i++) {

        // setup the match
        m_match = i + 1;
        m_match_end = false;
        bool player_x_final_match = false;

        // check to see who begins final match
        if(m_match == 5 && m_x_wins < m_o_wins) 
            player_x_final_match = true;

        // match loop
        do {
            switch(m_match) {
                case 1:
                case 3:
                    Player_X_Turn();
                    if(m_match_end) break;
                    Player_O_Turn();
                    break;
                case 2:
                case 4:
                    Player_O_Turn();
                    if(m_match_end) break;
                    Player_X_Turn();
                    break;
                case 5:
                    if(player_x_final_match) {
                        Player_X_Turn();
                        if(m_match_end) break;
                        Player_O_Turn();
                    } else {
                        Player_O_Turn();
                        if(m_match_end) break;
                        Player_X_Turn();    
                    }
                    break;
                default:
                    printer.SetConsoleOutput(ERROR);
                    break;
            }
        } while(!m_match_end);
    
        // determine match winner
        for(auto i : board) {

            if( // check horizontal win
                (board.at(i) == board.at(i+1) && board.at(i) == board.at(i+2)) ||
                // check vertical win
                (board.at(i) == board.at(i+3) && board.at(i) == board.at(i+6)) ||
                // check right diagonal win
                (board.at(i) == board.at(i+4) && board.at(i) == board.at(i+8)) ||
                // check left diagonal win
                (board.at(i) == board.at(i+2) && board.at(i) == board.at(i+4)) ) {

                switch(i) {
                    case PLAYER_X_POS:
                        printer.SetConsoleOutput(PLAYER_X_MATCH_WIN);
                        m_x_wins++;
                        break;
                    case PLAYER_O_POS:
                        printer.SetConsoleOutput(PLAYER_O_MATCH_WIN);
                        m_o_wins++;
                        break;
                }
            } else {
                printer.SetConsoleOutput(MATCH_TIE);
                m_x_wins++;
                m_o_wins++;
            }
        }
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
void Game::Player_X_Turn() {

    m_player_turn = PLAYER_X_TURN;
    bool valid_move = true;

    do {
        printer.SetConsoleOutput(PLAYER_X_TURN);
        char c_move = printer.GetConsoleInput();
        int move = c_move - '0';

        if(board.at(move-1) != EMPTY) {
            printer.SetConsoleOutput(INVALID_MOVE);
        } else {
            board.at(move-1) = PLAYER_X_POS;
            printer.SetConsoleOutput(PLAYER_X_MOVE);
            valid_move = true;
        }
    } while(!valid_move);

    // check for any empty spaces left
    bool empty_space_flag = false;
    for(auto i : board) {
        if(i == EMPTY) empty_space_flag = true;
    }
    if(empty_space_flag == true)    m_match_end = false;
    else                            m_match_end = true;
}

//
//
//
void Game::Player_O_Turn() {

    m_player_turn = PLAYER_O_TURN;

    printer.SetConsoleOutput(PLAYER_O_TURN);
//    char move = computer.Move();

    // initial logic for opposing player
    bool move_flag = false;
    for(auto i : board) {
        if(i == EMPTY && move_flag == false) {
            board.at(i) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE);
            move_flag == true;
        } 
    }

    // check for any empty spaces left
    bool empty_space_flag = false;
    for(auto i : board) {
        if(i == EMPTY) empty_space_flag = true;
    }
    if(empty_space_flag == true)    m_match_end = false;
    else                            m_match_end = true;
}