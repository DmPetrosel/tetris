#include <time.h>
#include "../inc/objects.h"
#include "../inc/frontend.h"

typedef void (*action)(Game_t *state);


void sigact(signals sig, Game_t *state, int* frame);

signals get_signal(int user_input);

void game_loop();

void start(Game_t *state);
void spawn(Game_t *state);
void moved(Game_t *state);
void collide(Game_t *state);
void gameover();
void exitstate(Game_t *state);
void check(Game_t *state);
void game_over_func(Game_t *state);


void appear(Game_t *state);
void varnish(Game_t *state);

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
    game_loop();
    endwin();

    return SUCCESS;
}

void game_loop()
{
    Game_t state; // заинициализировать структуру
    
    for(int i = 0; i < ROWS_FIELD; i++){
        for(int j = 0; j < COLS_FIELD; j++){
            state.current_field.field[i][j] = 0;
        }
    }
    state.current_state = START;
    int break_flag = TRUE;
    
    int frame = 0;
    while (break_flag) {   
        print_game_field(state);
        timeout(1000);
        sigact(get_signal(GET_USER_INPUT), &state, &frame);
    }
}

void sigact(signals sig, Game_t *state, int* frame)
{   

    action act = fsm_table[state->current_state][sig];

    mvprintw(10, 30, "%d %d %d", *frame, state->current_state, sig);
    ++(*frame);

    if (act)
        act(state);
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

void start(Game_t *state){

    generate_figure(&state->next_brick);
    state->current_state = SPAWN;

}

void gameover(){

    //prms->state.current_field.field = ;
    return;

}

void collide(Game_t *state){

    if(CUR_BRICK_Y <= 0){
        state->current_state = GAMEOVER;
    }else{
        state->current_state = SPAWN;
    }
}
int check_allowed(Game_t *state){
    ALLOWED = 0;
            if (CUR_BRICK_Y >= 0 && CUR_BRICK_Y < ROWS_FIELD - 1){    
                ALLOWED = 1;
            }
    return ALLOWED;
}
int check_collide(Game_t *state){
    ALLOWED = 1;
    for(int y = NG_BRICK_Y, i = 0; y < BRICK_N && ALLOWED; y++, i++){
        for(int x = NG_BRICK_X, j = 0; x < BRICK_N && ALLOWED; x++, j++){
            if (x < 0 || y + BRICK_N >= ROWS_FIELD || x + BRICK_N > COLS_FIELD){    
                ALLOWED = 0;
                state->current_state = COLLIDE;
            }
            if((state->current_field.field[y][x] & state->next_gen_brick.matrix[i][j]) == 1 && NG_BRICK_Y - CUR_BRICK_Y == 1) {
                state->current_state = COLLIDE;
            }
        }
    }
    return ALLOWED;
}

void spawn(Game_t *state){
    state->current_brick = state->next_brick;
    generate_figure(&state->next_brick);
    int allowed = check_allowed(state);
    if(allowed){
        appear(state);
        state->current_state = MOVING;
    } else{
        state->current_state = COLLIDE;
    }
}

void moved(Game_t *state){
    state->next_gen_brick = state->current_brick;
    ++NG_BRICK_Y;
    if(check_allowed(state)){
        varnish(state);
        state->current_brick = state->next_gen_brick;
        appear(state);
        state->current_state = MOVING;
    }else {
        state->current_state = COLLIDE;
    }
}
void appear(Game_t *state){
    for(int y = CUR_BRICK_Y, i = 0; y < BRICK_N + CUR_BRICK_Y; y++, i++){
        for(int x = CUR_BRICK_X, j = 0; x < BRICK_N + CUR_BRICK_X; x++, j++){
            if(state->current_brick.matrix[i][j] != 0){
                state->current_field.field[y][x] = state->current_brick.matrix[i][j];
            }
        }
    }
}
void varnish(Game_t *state){
    for(int y = CUR_BRICK_Y, i = 0; y < BRICK_N + CUR_BRICK_Y && ALLOWED; y++, i++){
        for(int x = CUR_BRICK_X, j = 0; x < BRICK_N + CUR_BRICK_X && ALLOWED; x++, j++){
            if(state->current_field.field[y][x] == state->current_brick.matrix[i][j])
                state->current_field.field[y][x] = 0;
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
    // time_t now;
    // struct tm * timeinfo;
    // time(&now);
    // timeinfo = localtime(&now);
    // int randomizer = (rand()*timeinfo->tm_min*timeinfo->tm_sec)%7;
    int randomizer = 0;
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