#include <time.h>
#include "../inc/objects.h"
#include "../inc/frontend.h"

typedef void (*action)(Game_t *state);

Brick_t rotate_brick(Game_t *state);
void check_strike(Game_t *state);
void shift_field_down(Game_t *state, int end_y, int rows_quantity);
void clean_screan(Game_t *state);
void sigact(signals sig, Game_t *state, int* frame);

signals get_signal(int user_input);

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

int can_be_moved(Game_t *state, int delta_row, int delta_col);


void appear(Game_t *state);
void varnish(Game_t *state);

void generate_figure(Brick_t *brick);

action fsm_table[5][5] = {
    {NULL, NULL, NULL, NULL, start},
    {spawn, spawn, spawn, spawn, spawn},
    {move_up, moved, move_right, move_left, moved},
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
    Game_t state = {0}; // заинициализировать структуру
    int start_paprer[20][10] = 
    {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,1,1,0},
        {0,1,0,0,1,0,1,0,0,1},
        {0,1,0,0,0,0,1,0,0,1},
        {0,1,0,1,1,0,1,0,0,1},
        {0,1,0,0,1,0,1,0,0,1},
        {0,0,1,1,0,0,0,1,1,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        
        };
    for(int i = 0; i < ROWS_FIELD; i++){
        for(int j = 0; j < COLS_FIELD; j++){
            state.current_field.field[i][j] = start_paprer[i][j];
        }
    }
    state.current_state = START;
    int break_flag = TRUE;
    
    int frame = 0;
    while (break_flag) {   
        print_game_field(state);
        mvprintw(10,40, "score: %d", state.game_info.score);
        sigact(get_signal(GET_USER_INPUT), &state, &frame);
        timeout(1000);

    }
}

void sigact(signals sig, Game_t *state, int* frame)
{   

    action act = fsm_table[state->current_state][sig];

    mvprintw(10, 30, "%d %d %d", *frame, state->current_state, sig);
    ++(*frame);

    if (act){
        act(state);

    }
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
void clean_screan(Game_t *state){
for(int i = 0; i < ROWS_FIELD; i++){
        for(int j = 0; j < COLS_FIELD; j++){
            state->current_field.field[i][j] = 0;
        }
    }
}
void start(Game_t *state){

    generate_figure(&state->next_brick);
    clean_screan(state);
    state->current_state = SPAWN;

}

void gameover(){

    //prms->state.current_field.field = ;
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
    if(can_be_moved(state, 1, -1)){
        varnish(state);
        ++CUR_BRICK_Y;
        --CUR_BRICK_X;
        appear(state);
    }
    state->current_state = MOVING;
}
void move_right(Game_t *state){
    if(can_be_moved(state, 1, 1)){
        varnish(state);
        ++CUR_BRICK_X;
        ++CUR_BRICK_Y;
        appear(state);
    }
    state->current_state = MOVING;
}
int can_be_moved(Game_t *state, int delta_row, int delta_col){

    int res = 1;
    int fig = 1;
    int flag = 0;
    int x = CUR_BRICK_X + delta_col;
    int y = CUR_BRICK_Y + delta_row;
        for(int i = BRICK_N - 1; i >= 0 && res!=0 && fig; i--){
            for(int j = BRICK_N - 1; j >= 0 && res!=0; j--){
                if(state->current_brick.matrix[i][j]==1){
                    if(state->current_field.field[y+i][x+j]== 1|| y+i >= ROWS_FIELD || x + j <0 || x+j >= COLS_FIELD)
                        {
                           
                            res = 0;
                        }
                flag = 1;
                }
                if(flag && j == 0){
                    fig = 0;
                }
                

            // if((state->current_field.field[y][x] & state->current_brick.matrix[i][j] ) == 1 || (state->current_brick.matrix[i][j] == 1 && y > ROWS_FIELD)){
                
            // }else if(state->current_brick.matrix[i][j] == 1) fig = 0;

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