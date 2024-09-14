#ifndef FSM_H_
#define FSM_H_

#include "defines.h"
#include "objects.h"

typedef enum{
    START = 0,
    SPAWN,
    MOVING,
    ROTATE_PAUSE,
    REACH,
    ATTACH,
    GAMEOVER,
    EXIT_STATE
} brick_state;

// typedef enum{
//     ROTATE = 0,
//     MOVE_LEFT,
//     MOVE_RIGHT,
//     PAUSE_BTN,
//     ENTER_BTN,
//     NOSIG
// }signals;

typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;



void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

// signals get_signal(int user_input);
// void sigact(signals sig, brick_state * state, game_stats_t * stats, board_t *field, player_pos *brick_pos);

#endif // FSM_H_