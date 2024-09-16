#ifndef OBJECTS_H
#define OBJECTS_H

#include <ncurses.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>

#define ROWS_FIELD 20
#define COLS_FIELD 10

#define GET_USER_INPUT getch()

#define WIN_INIT(time) {\
                             initscr();\
                             noecho();\
                             curs_set(0);\
                             keypad(stdscr, TRUE);\
                             timeout(time);\
                        }

#define ROWS_FIELD 20
#define COLS_FIELD 10

#define BRICK_N 4

#define NG_BRICK_Y prms->state.next_gen_brick.y
#define NG_BRICK_X prms->state.next_gen_brick.x

#define CUR_BRICK_Y prms->state.current_brick.y
#define CUR_BRICK_X prms->state.current_brick.x

#define ALLOWED prms->state.next_gen_brick.allowed

#define SUCCESS   0
#define ERROR     1

#define ESCAPE 27
#define ENTER_KEY 10

typedef struct {
    int x;
    int y;
} figure_pos;

typedef struct {
    char field[ROWS_FIELD][COLS_FIELD];
} board_t;



#endif