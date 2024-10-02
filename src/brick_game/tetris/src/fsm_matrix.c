#include <time.h>
#include "../../../gui/cli/frontend.h"
#include "../inc/objects.h"

typedef void (*action)(Game_t *state);
int check_brick(Game_t *state, int delta_y, int delta_x, int i, int j);
Brick_t rotate_brick(Game_t *state);
void check_strike(Game_t *state);
void shift_field_down(Game_t *state, int end_y, int rows_quantity);
void clean_screan(Game_t *state);
void sigact(UserAction_t sig, Game_t *state, int* frame);

UserAction_t get_signal(int user_input);

void game_loop();

void start(Game_t *state);
void spawn(Game_t *state);
void moved(Game_t *state);
void move_up(Game_t *state);
void move_left(Game_t *state);
void move_right(Game_t *state);
void collide(Game_t *state);
void gameover();
void exitstate(Game_t *state);
void check(Game_t *state);
void game_over_func(Game_t *state);
// void pause (Game_t *state);
// void end_game(Game_t *state);

int can_be_moved(Game_t *state, int delta_row, int delta_col);

void appear(Game_t *state);
void varnish(Game_t *state);

void generate_figure(Brick_t *brick);

action fsm_table[5][8] = {
    {start, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},
    {NULL, /*pause, end_game*/NULL,NULL, move_left, move_right, move_up, moved, moved},
    {collide, collide, collide, collide, collide, collide, collide, collide},
    {gameover, gameover, gameover, gameover, gameover, gameover, gameover, gameover},
};
    // TODO после реализации pause и end_game удалить нулы и раскоментировать их ^ 


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
    // иногда фигура в фигуру
    Game_t state = {0}; // заинициализировать структуру
   
    print_start(&state);
    state.current_state = START;
    int break_flag = TRUE;
    
    int frame = 0;
    while (break_flag) {   
        print_game_field(state);
        sigact(get_signal(GET_USER_INPUT), &state, &frame);
        timeout(1000-state.game_info.speed);

    }
}

void sigact(UserAction_t sig, Game_t *state, int* frame)
{   
    action act = fsm_table[state->current_state][sig];

    mvprintw(10, 30, "%d %d %d", *frame, state->current_state, sig);
    ++(*frame);

    if (act){
        act(state);

    }
}

UserAction_t get_signal(int user_input)
{
    UserAction_t current_signal = Action;

    if (user_input == SPACE)
        current_signal = Up;
    else if (user_input == KEY_DOWN)
        current_signal = Down;
    else if (user_input == KEY_LEFT)
        current_signal = Left;
    else if (user_input == KEY_RIGHT)
        current_signal = Right;
    else if (user_input == ENTER_KEY)
        current_signal = Start;
    else if (user_input == ESCAPE)
        current_signal = Pause;
    else if (user_input == KEY_DC)
        current_signal = Terminate;
    else if (user_input == SPACE)
        current_signal = Action;

    return current_signal;
}
void clean_screan(Game_t *state){
for(int i = 0; i < ROWS_FIELD; i++){
        for(int j = 0; j < COLS_FIELD; j++){
            state->current_field.field[i][j] = 0;
        }
    }
}
void start(Game_t *state){
    FILE * high_score = fopen(HSFILE, "r");
    char str_hs[20];
    if(high_score){
        if((fgets(str_hs, 10, high_score))){
           state->game_info.high_score = atoi(str_hs);
        }else
            state->game_info.high_score = 0;
    fclose(high_score);
    }
    generate_figure(&state->next_brick);
    clean_screan(state);
    state->current_state = SPAWN;

}

void gameover(){

    return;
}
void shift_field_down(Game_t *state, int end_y, int rows_quantity){

    for(int y = end_y; y >= 0; y--){
        for(int x = 0; x < COLS_FIELD; x ++){
            if(y - rows_quantity > 0)
            state->current_field.field[y][x] = state->current_field.field[y - rows_quantity][x]; 
            else
            state->current_field.field[y][x] = 0;
        }
    }

}
void check_strike(Game_t *state){
    int count = 0;
    int end = 0;
    for(int y = 0; y < ROWS_FIELD; y++){
        int count_cells = 0;
        for(int x = 0; x < COLS_FIELD; x ++){
            count_cells += state->current_field.field[y][x];
        }
        if(count_cells == COLS_FIELD){
            end = y;
            count ++;
        }
    }
// 1 линия — 100 очков;
// 2 линии — 300 очков;
// 3 линии — 700 очков;
// 4 линии — 1500 очков.
    switch(count){
        case 1: state->game_info.score+=100;
            break;
        case 2: state->game_info.score+=300;
            break;
        case 3: state->game_info.score+=700;
            break;
        case 4: state->game_info.score+=1500;
            break;
    }
    if(end)
        shift_field_down(state, end, count);
    
    if(state->game_info.score/600 > state->game_info.level){
        state->game_info.level +=1;
        if(state->game_info.level == 10){
            state->current_state = GAMEOVER;
        }
        state->game_info.speed+=SPEED_STEP;
    }
    if(state->game_info.score > state->game_info.high_score){
        state->game_info.high_score = state->game_info.score;
        FILE *high_score = fopen(HSFILE, "w+");
        char str_hs[20];
        sprintf(str_hs, "%d", state->game_info.score);
        if(high_score){
            if(!fputs(str_hs, high_score)){
            // ERROR
            }
        fclose(high_score);
        }
    }
}
void collide(Game_t *state){

    if(CUR_BRICK_Y <= 0){
        state->current_state = GAMEOVER;
    }else{
        check_strike(state);
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

void spawn(Game_t *state){
    state->current_brick = state->next_brick;
    // NG_BRICK_Y = ++CUR_BRICK_Y;
    generate_figure(&state->next_brick);
    int allowed = check_allowed(state);
    if(allowed){
        appear(state);
        state->current_state = MOVING;
    } else{
        state->current_state = COLLIDE;
    }
}

// 0000
// 1000
// 1110
// 0000

Brick_t rotate_brick(Game_t *state){
    Brick_t previous = state->current_brick; 
    Brick_t temp;
        temp = state->current_brick;
        for(int i = 0; i < BRICK_N; i ++){
            for(int j = 0; j < BRICK_N; j++){
                temp.matrix[i][j] = state->current_brick.matrix[BRICK_N-j-1][i];
            }
        }
        state->current_brick = temp;
        return previous;
}
void move_up(Game_t *state){
    varnish(state);
    Brick_t previous = rotate_brick(state);
    if(!can_be_moved(state, 0, 0)){
        state->current_brick = previous;
    }   
    appear(state);
    state->current_state = MOVING;

}

void moved(Game_t *state){
    if(can_be_moved(state, 1, 0)){
        varnish(state);
        ++CUR_BRICK_Y;
        appear(state);
        state->current_state = MOVING;
    }else {
        state->current_state = COLLIDE;
    }
}
void move_left(Game_t *state){
    if(can_be_moved(state, 0, -1)){
        varnish(state);
        // ++CUR_BRICK_Y;
        --CUR_BRICK_X;
        appear(state);
    }
    state->current_state = MOVING;
}
void move_right(Game_t *state){
    if(can_be_moved(state, 0, 1)){
        varnish(state);
        ++CUR_BRICK_X;
        // ++CUR_BRICK_Y;
        appear(state);
    }
    state->current_state = MOVING;
}

int can_be_moved(Game_t *state, int delta_row, int delta_col){
int res = 1;
int y = CUR_BRICK_Y +delta_row; 
int x = CUR_BRICK_X + delta_col;
for(int i = 0; i < BRICK_N && res; i++){
    for(int j = 0; j < BRICK_N && res; j++){

        if ((x + j < 0 || x + j >= COLS_FIELD ||
            y + i >= ROWS_FIELD) && state->current_brick.matrix[i][j]) {
            res = 0;
        } else if ((state->current_field.field[y + i][x + j] &&state->current_brick.matrix[i][j] && (!check_brick(state, delta_row, delta_col, i, j)))) {
            res = 0;
        }
    }
}

return res;
}
int check_brick(Game_t *state, int delta_y, int delta_x, int i, int j){
    int res = 1;
    if(delta_y >= 0){
        if(i+delta_y >= BRICK_N || j+delta_x < 0 || j+delta_x >= BRICK_N){
            res = 0;    
        }
        else{
            res = state->current_brick.matrix[i+delta_y][j+delta_x];
        }
    }
    
    return res; 
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
    // for(int i = 0; i < BRICK_N*BRICK_N; i++){
    //     brick->matrix[BRICK_N/i][BRICK_N%i] = 0;
    // }
    for(int i = 0; i < BRICK_N; i++)
        for(int j = 0; j < BRICK_N; j++)
            brick->matrix[i][j] = 0;
    srand(time(NULL));
    int randomizer = rand()%7;
    switch(randomizer){
        case 0:
            /*####*/
            brick->matrix[1][0] = 1;
            brick->matrix[1][1] = 1;
            brick->matrix[1][2] = 1;
            brick->matrix[1][3] = 1;
            break;
        case 1:
            /*##
            ___##*/
            brick->matrix[1][0] = 1;
            brick->matrix[1][1] = 1;
            brick->matrix[2][1] = 1;
            brick->matrix[2][2] = 1;
            break;
        case 2:
            /*#
            __###*/
            brick->matrix[1][1] = 1;
            brick->matrix[2][0] = 1;
            brick->matrix[2][1] = 1;
            brick->matrix[2][2] = 1;
            break;

        case 3:
            /*__#
            __###*/
            brick->matrix[1][2] = 1;
            brick->matrix[2][0] = 1;
            brick->matrix[2][1] = 1;
            brick->matrix[2][2] = 1;
            break;

        case 4:
            /*##
            __##*/
            brick->matrix[1][1] = 1;
            brick->matrix[1][2] = 1;
            brick->matrix[2][1] = 1;
            brick->matrix[2][2] = 1;
            break;
        case 5:
            /*_##
            __##_*/
            brick->matrix[1][1] = 1;
            brick->matrix[1][2] = 1;
            brick->matrix[2][0] = 1;
            brick->matrix[2][1] = 1;
            break;
        case 6:
            /*_#_
            __###*/
            brick->matrix[1][1] = 1;
            brick->matrix[2][0] = 1;
            brick->matrix[2][1] = 1;
            brick->matrix[2][2] = 1;
            break;
    }

} 