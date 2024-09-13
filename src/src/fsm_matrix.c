#include "objects.h"

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

typedef enum
{
    MOVE_UP,
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    NOSIG
} signals;

typedef enum {
    START,
    SPAWN,
    MOVING,
    GAMEOVER,
} GameState_t;

typedef struct {
    game_field curren_field;
    GameState_t current_state; 
} Game_t;

typedef struct {
    signals signal;
    Game_t state;
}params_t;

typedef struct {
    char field[ROWS_FIELD][COLS_FIELD];
}game_field;

typedef void (*action)(params_t *prms);

void sigact(signals sig, Game_t *state);

signals get_signal(int user_input);

void spawn(params_t *prms);
void moved(params_t *prms);
void collide(params_t *prms);
void gameover(params_t *prms);
void exitstate(params_t *prms);
void check(params_t *prms);


void generate_figure();

action fsm_table[4][5] = {
    {NULL, NULL, NULL, NULL, spawn},
    {spawn, spawn, spawn, spawn, spawn},
    {moved, moved, moved, moved, moved},
    {gameover, gameover, gameover, gameover, gameover},
};

int main(void)
{
    WIN_INIT(50);
    setlocale(LC_ALL, "");
    print_overlay();
    game_loop();
    endwin();

    return SUCCESS;
}

void game_loop()
{
    game_field field = {0};
    GameState_t state = START;
    signals signal = NOSIG;
    int break_flag = TRUE;
    

    while (break_flag) {   
        sigact(get_signal(signal), state);
        if (state == MOVING || state == START)
            signal = GET_USER_INPUT;
    }
}

void sigact(signals sig, Game_t *state)
{
    action act = NULL;
    params_t params;
    
    params.signal = sig;
    params.state = *state;
    

    act = fsm_table[params.state.current_state][params.signal];

    if (act)
        act(&params);
}

signals get_signal(int user_input)
{
    signals current_signal = NOSIG;

    if (user_input == KEY_UP)
        current_signal = MOVE_UP;
    else if (user_input == KEY_DOWN)
        current_signal = MOVE_DOWN;
    else if (user_input == KEY_LEFT)
        current_signal = MOVE_LEFT;
    else if (user_input == KEY_RIGHT)
        current_signal = MOVE_RIGHT;

    return current_signal;
}

void spawn(params_t *prms){





}

void generate_figure(){


} 