#include "frontend.h"
#include "../../brick_game/tetris/inc/objects.h"
#include "../../brick_game/tetris/inc/defines.h"



void print_game_field(Game_t game) {
    for (int i = 0; i < ROWS_FIELD; i++) {
      for (int j = 0; j < COLS_FIELD; j++) {
        if (game.current_field.field[i][j] == 0) mvprintw(i + 1, j * 2 + 2, "..");
        if (game.current_field.field[i][j] == 1) mvprintw(i + 1, j * 2 + 2, "[]");
      }
    }
    mvprintw(11,(2*COLS_FIELD+5), "score: %d", game.game_info.score);
    mvprintw(12,(2* COLS_FIELD+5), "high score: %d", game.game_info.high_score);
    mvprintw(13,(2* COLS_FIELD+5), "level: %d", game.game_info.level);
    print_next(&game);
}

void print_start (Game_t *game) {
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
            game->current_field.field[i][j] = start_paprer[i][j];
        }
    }
}


void print_pause (Game_t *game) {
   int pause_paprer[20][10] = 
    {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,1,0,0},
        {0,0,1,0,0,0,0,1,0,0},
        {0,0,1,0,0,0,0,1,0,0},
        {0,0,1,0,0,0,0,1,0,0},
        {0,0,1,0,0,0,0,1,0,0},
        {0,0,1,0,0,0,0,1,0,0},
        {0,0,1,0,0,0,0,1,0,0},
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
            game->current_field.field[i][j] = pause_paprer[i][j];
        }
    }
}
void print_next(Game_t *game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->next_brick.matrix[i][j] == 0) mvprintw(i + 15, j * 2 + 27, "  ");
      if (game->next_brick.matrix[i][j] == 1) mvprintw(i + 15, j * 2 + 27, "[]");
    }
  }
}
