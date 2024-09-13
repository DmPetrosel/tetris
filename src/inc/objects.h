#ifndef OBJECTS_H
#define OBJECTS_H

#include <ncurses.h>
#include <locale.h>
#include <time.h>
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