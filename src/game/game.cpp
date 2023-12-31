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

#include "../Game/Game.hpp"
#include "../Game/GameState.hpp"
#include "../Printer/Printer.hpp"

using bocan::TicTac::Game;

// brief Singleton instance of the Game class object.
Game Game::s_instance;

// brief Initial setup of member variables and printer to start game state.
// brief Waits for user input.
// param None.
// return None.
void Game::Start() {

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
    for(auto cell : board) {
        cell = EMPTY;
    }

    // reset the screen
    printer.ResetScreen();
    printer.RefreshScreen();
    printer.SetConsoleOutput(START_GAME);

    // wait for start from the user
    static_cast <void> ( printer.GetConsoleInput() );
}

// brief Main Loop of the game. Game has five cycles representing matches.
// brief User can exit the game at any point during the loop.
// param None.
// return None.
void Game::GameLoop() {

    // game is setup for five matches
    for(int i = 0; i < 5; i++) {

        // setup the match
        m_match = i + 1;
        m_match_end = START_GAME;
        bool player_x_final_match = false;

        // clear the board
        for(int i = 0; i < board.size(); i++) {
            board.at(i) = EMPTY;
        }

        // update the screen
        printer.RefreshScreen();

        // check for early game winner and break from for loop
        if(m_x_wins > 2 || m_o_wins > 2) {
            break;
        }

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

        // break from for loop if player quit
        if(m_match_end == PLAYER_QUIT) break;
    }
}

// brief End Game sequence. Sets member variables and printer to end game state.
// brief User can choose to exit (return true) or play again (return false).
// param None.
// return Boolean True to exit the program or Boolean False to play again.
bool Game::EndGame() {

    if(m_match_end == PLAYER_QUIT) {
        printer.SetConsoleOutput(PLAYER_QUIT);
        printer.SetConsoleOutput(GAME_EXIT);
        printer.ExitScreen();
        return true;
    }
    char input;
    bool game_over = false;
    bool error = false;

    if(m_x_wins > m_o_wins) {
        printer.SetConsoleOutput(PLAYER_X_GAME_WIN);
        
    } else if (m_x_wins == m_o_wins) {
        printer.SetConsoleOutput(GAME_TIE);

    } else {
        printer.SetConsoleOutput(PLAYER_O_GAME_WIN);
    }

    // check for user exit or play again
    do {
        error = false;
        printer.SetConsoleOutput(END_GAME);
        input = printer.GetConsoleInput();
        switch(input) {
            case 'y':
            case 'Y':
                game_over = false;
                break;
            case 'n':
            case 'N':
                game_over = true;
                printer.SetConsoleOutput(GAME_EXIT);
                printer.ExitScreen();
                break;
            default:
                printer.SetConsoleOutput(INVALID_INPUT);
                error = true;
                break;
        }
    } while (error);
    return game_over;
}

// brief Sequence for the user's turn. Provides error checking and checks for a match win.
// param None.
// return None.
void Game::Player_X_Turn() {

    m_player_turn = PLAYER_X_TURN;
    bool valid_move = true;

    do {
        printer.SetConsoleOutput(PLAYER_X_TURN);
        char c_move = printer.GetConsoleInput();
        int move = c_move - '0';
        // error check user input
        switch(c_move) {
            case 'q':
            case 'Q':
                m_match_end = PLAYER_QUIT;
                valid_move = true;
                break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':

                // check if board position is occupied
                if(board.at(move-1) != EMPTY) {
                    printer.SetConsoleOutput(INVALID_MOVE);
                    valid_move = false;

                } else {
                    board.at(move-1) = PLAYER_X_POS;
                    printer.SetConsoleOutput(PLAYER_X_MOVE, move);
                    valid_move = true;
                }
                break;

            default:
                printer.SetConsoleOutput(INVALID_MOVE);
                valid_move = false;
                break;
        }

    } while(!valid_move);
    Check_Match_Win();
}

// Sequence for the opposing player's turn. Uses an algorithm to make a strategic move.
// param None.
// return None.
void Game::Player_O_Turn() {

    m_player_turn = PLAYER_O_TURN;

    printer.SetConsoleOutput(PLAYER_O_TURN);

    bool move_flag = false;

    // opposing player scans for horizontal advantage
    for(int i = 0; i < board.size(); i+=3) {
        if(move_flag) break;
        if( board.at(i+0) == board.at(i+1) && board.at(i+0) == PLAYER_O_POS && board.at(i+2) == EMPTY) {
            board.at(i+2) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE, i+3);
            move_flag = true;
        } else
        if( board.at(i+1) == board.at(i+2) && board.at(i+1) == PLAYER_O_POS && board.at(i+0) == EMPTY) {
            board.at(i+0) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE, i+1);
            move_flag = true;
        } else
        if( board.at(i+0) == board.at(i+2) && board.at(i+0) == PLAYER_O_POS && board.at(i+1) == EMPTY) {
            board.at(i+1) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE, i+2);
            move_flag = true;
        }
    }

    // opposing player scans for vertical advantage
    for(int i = 0; i < 3; i++) {
        if(move_flag) break;
        if( board.at(i+0) == board.at(i+3) && board.at(i+0) == PLAYER_O_POS && board.at(i+6) == EMPTY) {
            board.at(i+6) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE,i+7);
            move_flag = true;
        } else
        if( board.at(i+3) == board.at(i+6) && board.at(i+3) == PLAYER_O_POS && board.at(i+0) == EMPTY) {
            board.at(i+0) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE, i+1);
            move_flag = true;
        } else
        if( board.at(i+0) == board.at(i+6) && board.at(i+0) == PLAYER_O_POS && board.at(i+3) == EMPTY) {
            board.at(i+3) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE, i+4);
            move_flag = true;
        }
    }

    // opposing player scans for right diagonal advantage
    if(!move_flag && board.at(0) == board.at(4) && board.at(0) == PLAYER_O_POS && board.at(8) == EMPTY) {
        board.at(8) = PLAYER_O_POS;
        printer.SetConsoleOutput(PLAYER_O_MOVE, 9);
        move_flag = true;
    } else
    if(!move_flag && board.at(4) == board.at(8) && board.at(4) == PLAYER_O_POS && board.at(0) == EMPTY) {
        board.at(0) = PLAYER_O_POS;
        printer.SetConsoleOutput(PLAYER_O_MOVE, 1);
        move_flag = true;
    } else
    if(!move_flag && board.at(0) == board.at(8) && board.at(0) == PLAYER_O_POS && board.at(4) == EMPTY) {
        board.at(4) = PLAYER_O_POS;
        printer.SetConsoleOutput(PLAYER_O_MOVE, 5);
        move_flag = true;
    }

    // opposing player scans for left diagonal advantage
    if(!move_flag && board.at(2) == board.at(4) && board.at(2) == PLAYER_O_POS && board.at(6) == EMPTY) {
        board.at(6) = PLAYER_O_POS;
        printer.SetConsoleOutput(PLAYER_O_MOVE, 7);
        move_flag = true;
    } else
    if(!move_flag && board.at(4) == board.at(6) && board.at(4) == PLAYER_O_POS && board.at(2) == EMPTY) {
        board.at(2) = PLAYER_O_POS;
        printer.SetConsoleOutput(PLAYER_O_MOVE, 8);
        move_flag = true;
    } else
    if(!move_flag && board.at(2) == board.at(6) && board.at(2) == PLAYER_O_POS && board.at(4) == EMPTY) {
        board.at(4) = PLAYER_O_POS;
        printer.SetConsoleOutput(PLAYER_O_MOVE, 5);
        move_flag = true;
    }

    // opposing player scans for horizontal disadvantage
    for(int i = 0; i < board.size(); i+=3) {
        if(move_flag) break;
        if( board.at(i+0) == board.at(i+1) && board.at(i+0) == PLAYER_X_POS && board.at(i+2) == EMPTY) {
            board.at(i+2) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE, i+3);
            move_flag = true;
        } else
        if( board.at(i+1) == board.at(i+2) && board.at(i+1) == PLAYER_X_POS && board.at(i+0) == EMPTY) {
            board.at(i+0) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE, i+1);
            move_flag = true;
        } else
        if( board.at(i+0) == board.at(i+2) && board.at(i+0) == PLAYER_X_POS && board.at(i+1) == EMPTY) {
            board.at(i+1) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE, i+2);
            move_flag = true;
        }
    }

    // opposing player scans for vertical disadvantage
    for(int i = 0; i < 3; i++) {
        if(move_flag) break;
        if( board.at(i+0) == board.at(i+3) && board.at(i+0) == PLAYER_X_POS && board.at(i+6) == EMPTY) {
            board.at(i+6) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE,i+7);
            move_flag = true;
        } else
        if( board.at(i+3) == board.at(i+6) && board.at(i+3) == PLAYER_X_POS && board.at(i+0) == EMPTY) {
            board.at(i+0) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE, i+1);
            move_flag = true;
        } else
        if( board.at(i+0) == board.at(i+6) && board.at(i+0) == PLAYER_X_POS && board.at(i+3) == EMPTY) {
            board.at(i+3) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE, i+4);
            move_flag = true;
        }
    }

    // opposing player scans for right diagonal disadvantage
    if(!move_flag && board.at(0) == board.at(4) && board.at(0) == PLAYER_X_POS && board.at(8) == EMPTY) {
        board.at(8) = PLAYER_O_POS;
        printer.SetConsoleOutput(PLAYER_O_MOVE, 9);
        move_flag = true;
    } else
    if(!move_flag && board.at(4) == board.at(8) && board.at(4) == PLAYER_X_POS && board.at(0) == EMPTY) {
        board.at(0) = PLAYER_O_POS;
        printer.SetConsoleOutput(PLAYER_O_MOVE, 1);
        move_flag = true;
    } else
    if(!move_flag && board.at(0) == board.at(8) && board.at(0) == PLAYER_X_POS && board.at(4) == EMPTY) {
        board.at(4) = PLAYER_O_POS;
        printer.SetConsoleOutput(PLAYER_O_MOVE, 5);
        move_flag = true;
    }

    // opposing player scans for left diagonal disadvantage
    if(!move_flag && board.at(2) == board.at(4) && board.at(2) == PLAYER_X_POS && board.at(6) == EMPTY) {
        board.at(6) = PLAYER_O_POS;
        printer.SetConsoleOutput(PLAYER_O_MOVE, 7);
        move_flag = true;
    } else
    if(!move_flag && board.at(4) == board.at(6) && board.at(4) == PLAYER_X_POS && board.at(2) == EMPTY) {
        board.at(2) = PLAYER_O_POS;
        printer.SetConsoleOutput(PLAYER_O_MOVE, 8);
        move_flag = true;
    } else
    if(!move_flag && board.at(2) == board.at(6) && board.at(2) == PLAYER_X_POS && board.at(4) == EMPTY) {
        board.at(4) = PLAYER_O_POS;
        printer.SetConsoleOutput(PLAYER_O_MOVE, 5);
        move_flag = true;
    }

    // opposing player checks if middle cell is open
    if(!move_flag && board.at(4) == EMPTY) {
        board.at(4) = PLAYER_O_POS;
        printer.SetConsoleOutput(PLAYER_O_MOVE, 5);
        move_flag = true;
    }

    // opposing player checks for more empty spaces
    for(int i = 0; i < board.size(); i++) {
        if(board.at(i) == EMPTY && move_flag == false) {
            board.at(i) = PLAYER_O_POS;
            printer.SetConsoleOutput(PLAYER_O_MOVE, i+1);
            move_flag = true;
        } 
    }

    Check_Match_Win();
}

// brief Sequence to examine the board and determine if there is a winner.
// param None.
// return None.
void Game::Check_Match_Win() {

    // check if player quit the game
    if(m_match_end == PLAYER_QUIT) 
        return;
    
    // check for any empty spaces left
    bool empty_space_flag = false;
    for(auto cell : board) {
        if(cell == EMPTY) empty_space_flag = true;
    }

    // determine match winner
    if( // check for horizontal wins
        (board.at(0) == board.at(1) && board.at(0) == board.at(2) && board.at(0) != EMPTY) ||
        (board.at(3) == board.at(4) && board.at(3) == board.at(5) && board.at(3) != EMPTY) ||
        (board.at(6) == board.at(7) && board.at(6) == board.at(8) && board.at(6) != EMPTY) ||
        // check for vertical wins
        (board.at(0) == board.at(3) && board.at(0) == board.at(6) && board.at(0) != EMPTY) ||
        (board.at(1) == board.at(4) && board.at(1) == board.at(7) && board.at(1) != EMPTY) ||
        (board.at(2) == board.at(5) && board.at(2) == board.at(8) && board.at(2) != EMPTY) ||
        // check for right diagonal win
        (board.at(0) == board.at(4) && board.at(0) == board.at(8) && board.at(0) != EMPTY) ||
        // check for left diagonal win
        (board.at(2) == board.at(4) && board.at(2) == board.at(6) && board.at(2) != EMPTY) ) {

        switch(m_player_turn) {
            case PLAYER_X_TURN:
                printer.SetConsoleOutput(PLAYER_X_MATCH_WIN);
                m_x_wins++;
                m_match_end = PLAYER_X_MATCH_WIN;
                break;

            case PLAYER_O_TURN:
                printer.SetConsoleOutput(PLAYER_O_MATCH_WIN);
                m_o_wins++;
                m_match_end = PLAYER_O_MATCH_WIN;
        }
    } else if(!empty_space_flag) {
        printer.SetConsoleOutput(MATCH_TIE);
        m_match_end = MATCH_TIE;
    } 
}
