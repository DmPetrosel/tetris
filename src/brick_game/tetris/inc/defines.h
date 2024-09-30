#ifndef DEFINES_H
#define DEFINES_H

#define ROWS_FIELD 20
#define COLS_FIELD 10

#define GET_USER_INPUT getch()


#define WIN_INIT(time) {\
                             initscr();\
                             noecho();\
                             curs_set(0);\
                             keypad(stdscr, TRUE);\
                        }


#define BRICK_N 4

#define NG_BRICK_Y state->next_gen_brick.y
#define NG_BRICK_X state->next_gen_brick.x

#define CUR_BRICK_Y state->current_brick.y
#define CUR_BRICK_X state->current_brick.x

#define ALLOWED state->current_brick.allowed
#define HSFILE "high_score.txt"

#define SPEED_STEP 70;

#define SUCCESS   0
#define ERROR     1

#define ESCAPE 27
#define ENTER_KEY 10

#endif