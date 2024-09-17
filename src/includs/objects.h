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
    int score;
    int level;
    int speed;
    int won;
} game_stats_t;

#endif // OBJECTS_H_