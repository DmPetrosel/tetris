#ifndef OBJECTS_H
#define OBJECTS_H

#include <ncurses.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include "defines.h"


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

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

#endif