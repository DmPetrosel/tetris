#include "../inc/objects.h"

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
    game_field current_field;
    GameState_t current_state; 
    Brick_t current_brick;
    Brick_t next_gen_brick;
    Brick_t next_brick;
} Game_t;

typedef struct {
    signals signal;
    Game_t  state;
}params_t;

typedef struct {
    int matrix[4][4];
    int x, y;
    int allowed; // 1 True, 0 Not allowed
}Brick_t;

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


void appear(params_t *prms);
void varnish(params_t *prms);

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
int check_allowed(params_t *prms){
    prms->state.next_gen_brick.allowrd = 1;
    for(int y = prms->state.next_gen_brick.y, i = 0; y < BRICK_N+prms->state.next_gen_brick.y && prms->state.next_gen_brick.allowrd != 0; y++, i++){
        for(int x = prms->state.next_gen_brick.x, j = 0; x < BRICK_N + prms->state.next_gen_brick.x && prms->state.next_gen_brick.allowrd != 0; x++, j++){
            if(prms->state.current_field.field[y][x]&prms->state.next_gen_brick.matrix[i][j] == 1 ||
            y<0 || x < 0 || y+ BRICK_N > ROWS_FIELD || x + BRICK_N > COLS_FIELD){
                prms->state.next_gen_brick.allowrd = 0;
            }

        }
    }
    return prms->state.next_gen_brick.allowrd;
}

void spawn(params_t *prms){
prms->state.current_brick = prms->state.next_brick;
generate_figure(prms->state.next_brick);
int allowed = check_allowed(prms);
if(allowed){
    appear(prms);
}

}

void moved(params_t *prms){
    prms->state.next_gen_brick = prms->state.current_brick;
    prms->state.next_gen_brick.y+=1;
    if(check_allowed(prms)){
        varnish(prms);
        prms->state.current_brick = prms->state.next_gen_brick;
        appear(prms);
    }
}
void appear(params_t *prms){
    for(int y = prms->state.current_brick.y, i = 0; y < BRICK_N+prms->state.current_brick.y && prms->state.current_brick.allowrd != 0; y++, i++){
        for(int x = prms->state.current_brick.x, j = 0; x < BRICK_N + prms->state.current_brick.x && prms->state.current_brick.allowrd != 0; x++, j++){
            prms->state.current_field.field[y][x] = prms->state.current_brick.matrix[i][j];
        }
    }
}
void varnish(params_t *prms){
    for(int y = prms->state.current_brick.y, i = 0; y < BRICK_N+prms->state.current_brick.y && prms->state.current_brick.allowrd != 0; y++, i++){
        for(int x = prms->state.current_brick.x, j = 0; x < BRICK_N + prms->state.current_brick.x && prms->state.current_brick.allowrd != 0; x++, j++){
            if(prms->state.current_field.field[y][x] == prms->state.current_brick.matrix[i][j])
                prms->state.current_field.field[y][x] = 0;
        }
    }
}
typedef enum {
    STICK = 0,
}BrickName;

void generate_figure(Brick_t *brick){
    brick->x = COLS_FIELD/2-2;
    brick->y = 0;
    brick->allowed = 1;
    for(int i = 0; i < BRICK_N*BRICK_N; i++){
        brick->matrix[i/BRICK_N][i%BRICK_N] = 0;
    }
    time_t now;
    struct tm * timeinfo;
    time(&now);
    timeinfo = localtime(&now);
    int randomizer = (ranD(1000)*timeinfo->tm_min*timeinfo->tm_sec)%7;
    switch(randomizer){
        case 0:
            /*####*/
            brick->matrix[0][0] = 1;
            brick->matrix[0][1] = 1;
            brick->matrix[0][2] = 1;
            brick->matrix[0][3] = 1;
            break;
        case 1:
            /*##
            ___##*/
            brick->matrix[0][1] = 1;
            brick->matrix[0][1] = 1;
            brick->matrix[1][1] = 1;
            brick->matrix[1][2] = 1;
            break;
        case 2:
            /*#
            __###*/
            brick->matrix[0][1] = 1;
            brick->matrix[1][0] = 1;
            brick->matrix[1][1] = 1;
            brick->matrix[1][2] = 1;
            break;

        case 3:
            /*__#
            __###*/
            brick->matrix[0][2] = 1;
            brick->matrix[1][0] = 1;
            brick->matrix[1][1] = 1;
            brick->matrix[1][2] = 1;
            break;

        case 4:
            /*##
            __##*/
            brick->matrix[0][0] = 1;
            brick->matrix[0][1] = 1;
            brick->matrix[1][0] = 1;
            brick->matrix[1][1] = 1;
            break;
        case 5:
            /*_##
            __##_*/
            brick->matrix[0][1] = 1;
            brick->matrix[0][2] = 1;
            brick->matrix[1][0] = 1;
            brick->matrix[1][1] = 1;
            break;
        case 6:
            /*_#_
            __###*/
            brick->matrix[0][1] = 1;
            brick->matrix[1][0] = 1;
            brick->matrix[1][1] = 1;
            brick->matrix[1][2] = 1;
            break;
    }

} 