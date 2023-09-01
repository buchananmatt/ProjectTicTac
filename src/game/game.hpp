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

class array;

class Console;
class Computer;
class Printer;

namespace bocan {

class Game {
public:

    static Game& Get() { return s_instance; }

    bool Start();
    void GameLoop();
    bool EndGame();

private:

    static Game s_instance;

    friend class Printer;

    bocan::Printer printer;

    int m_match;
    int m_x_wins;
    int m_o_wins;
    int m_player_turn; 

    std::array<int*> board = { 1, 2, 3, 
                               4, 5, 6, 
                               7, 8, 9 };

    enum event_list {
        START_GAME,
        PLAYER_O_TURN,
        PLAYER_X_TURN,
        PLAYER_O_MOVE,
        PLAYER_X_MOVE,
        PLAYER_O_WIN,
        PLAYER_X_WIN,
        END_GAME,
        ERROR
    } m_event;
    
private:

    Game() {}
    Game(const Game&) = delete;
    ~Game() {}

    void NewGame();
    void Player_X_Turn();
    void Player_O_Turn();
    bool MatchEnd();
};

} // NAMESPACE BOCAN