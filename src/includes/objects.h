#ifndef OBJECTS_H_
#define OBJECTS_H_
#include "defines.h"
typedef struct{
    int x; 
    int y;
} player_pos;

typedef struct {
    char bricks_filled[BOARD_Y][BOARD_X];
}board_t;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

#endif // OBJECTS_H_