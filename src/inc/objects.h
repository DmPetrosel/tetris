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

typedef enum {
    START,
    SPAWN,
    MOVING,
    COLLIDE,
    GAMEOVER,
} GameState_t;


typedef struct {

    char field[ROWS_FIELD][COLS_FIELD];

}game_field;

typedef struct {

    int matrix[4][4];
    int x, y;
    int allowed; // 1 True, 0 Not allowed
    
}Brick_t;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;


typedef struct {
    game_field current_field;
    GameState_t current_state; 
    Brick_t current_brick;
    Brick_t next_brick;
    GameInfo_t game_info;
} Game_t;




#endif