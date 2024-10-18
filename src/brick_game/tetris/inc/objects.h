#ifndef OBJECTS_H
#define OBJECTS_H

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "defines.h"
/**
 * @brief Stucture gives by task.
 *
 */
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
/**
 * @brief FSM states of the game.
 *
 */
typedef enum {
  START,
  SPAWN,
  MOVING,
  PAUSE,
  COLLIDE,
  GAMEOVER,
} GameState_t;

/**
 * @brief Game field.
 *
 */
typedef struct {
  int field[ROWS_FIELD][COLS_FIELD];

} game_field;

/**
 * @brief Brick structure.
 *
 */
typedef struct {
  int matrix[4][4];
  int x, y;
  int allowed;  // 1 True, 0 Not allowed

} Brick_t;
/**
 * @brief GameInfo_t structure. Gives by task.
 *
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;
/**
 * @brief Main game structure.
 *
 */
typedef struct {
  game_field current_field;
  GameState_t current_state;
  Brick_t current_brick;
  Brick_t next_brick;
  GameInfo_t game_info;
  bool break_flag;
} Game_t;

#endif