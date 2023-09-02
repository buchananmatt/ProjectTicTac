//
// GAMESTATE.HPP [PROJECT TICTAC]
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

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

namespace bocan {

   enum event_state {
        START_GAME = 0,
        PLAYER_O_TURN,
        PLAYER_X_TURN,
        PLAYER_O_MOVE,
        PLAYER_X_MOVE,
        PLAYER_O_MATCH_WIN,
        PLAYER_X_MATCH_WIN,
        MATCH_TIE,
        PLAYER_O_GAME_WIN,
        PLAYER_X_GAME_WIN,
        END_GAME,
        INVALID_MOVE,
        ERROR
    };

    enum board_state {
        EMPTY = 0,
        PLAYER_X_POS,
        PLAYER_O_POS
    };

    enum board_type {
        HELP_BOARD = 1,
        GAME_BOARD = 2
    };

} // NAMESPACE BOCAN

#endif // GAMESTATE_HPP