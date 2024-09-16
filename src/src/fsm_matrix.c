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
    COLLIDE,
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

void start(params_t *prms);
void spawn(params_t *prms);
void moved(params_t *prms);
void collide(params_t *prms);
void gameover(params_t *prms);
void exitstate(params_t *prms);
void check(params_t *prms);
void game_over_func(params_t *prms);


void appear(params_t *prms);
void varnish(params_t *prms);

void generate_figure(Brick_t *brick);

action fsm_table[5][5] = {
    {NULL, NULL, NULL, NULL, start},
    {spawn, spawn, spawn, spawn, spawn},
    {moved, moved, moved, moved, moved},
    {collide, collide, collide, collide, collide},
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
    Game_t state; // заинициализировать структуру
    state.current_state = START;
    signals signal = NOSIG;
    int break_flag = TRUE;
    

    while (break_flag) {   
        sigact(get_signal(signal), state.current_state);
        signal = GET_USER_INPUT;
    }
}

void sigact(signals sig, Game_t *state)
{
    action act = NULL;
    params_t params;
    
    params.signal = sig;
    params.state.current_state = state;
    

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

void start(params_t *prms){

    generate_figure(prms->state.next_brick);
    prms->state.current_state = SPAWN;

}

void gameover(params_t *prms){

    //prms->state.current_field.field = ;


}

void collide(params_t *prms){

    if(CUR_BRICK_Y <= 0){
        prms->state.current_state = GAMEOVER;
    }
}

int check_allowed(params_t *prms){
    ALLOWED = 1;
    for(int y = NG_BRICK_Y, i = 0; y < BRICK_N + NG_BRICK_Y && ALLOWED; y++, i++){
        for(int x = NG_BRICK_X, j = 0; x < BRICK_N + NG_BRICK_X && ALLOWED; x++, j++){
            if(prms->state.current_field.field[y][x] & prms->state.next_gen_brick.matrix[i][j] == 1 && NG_BRICK_Y - CUR_BRICK_Y == 1) {
                prms->state.current_state = COLLIDE;
            } else if (y < 0 || x < 0 || y + BRICK_N > ROWS_FIELD || x + BRICK_N > COLS_FIELD){    
                ALLOWED = 0;
            }
        }
    }
    return ALLOWED;
}

void spawn(params_t *prms){
    prms->state.current_brick = prms->state.next_brick;
    generate_figure(prms->state.next_brick);
    int allowed = check_allowed(prms);
    if(allowed){
        appear(prms);
        prms->state.current_state = MOVING;
    } else{
        prms->state.current_state = COLLIDE;
    }
}

void moved(params_t *prms){
    prms->state.next_gen_brick = prms->state.current_brick;
    ++NG_BRICK_Y;
    if(check_allowed(prms)){
        varnish(prms);
        prms->state.current_brick = prms->state.next_gen_brick;
        appear(prms);
        prms->state.current_state = MOVING;
    }else {
        prms->state.current_state = COLLIDE;
    }
}
void appear(params_t *prms){
    for(int y = CUR_BRICK_Y, i = 0; y < BRICK_N + CUR_BRICK_Y && ALLOWED; y++, i++){
        for(int x = CUR_BRICK_X, j = 0; x < BRICK_N + CUR_BRICK_X && ALLOWED; x++, j++){
            prms->state.current_field.field[y][x] = prms->state.current_brick.matrix[i][j];
        }
    }
}
void varnish(params_t *prms){
    for(int y = CUR_BRICK_Y, i = 0; y < BRICK_N + CUR_BRICK_Y && ALLOWED; y++, i++){
        for(int x = CUR_BRICK_X, j = 0; x < BRICK_N + CUR_BRICK_X && ALLOWED; x++, j++){
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
    int randomizer = (rand()*timeinfo->tm_min*timeinfo->tm_sec)%7;
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