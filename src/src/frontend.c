#include "frontend.h"
#include "../inc/objects.h"
#include "../inc/defines.h"


void print_game_field(Game_t game) {
    for (int i = 0; i < ROWS_FIELD; i++) {
      for (int j = 0; j < COLS_FIELD; j++) {
        if (game.current_field.field[i][j] == 0) mvprintw(i + 1, j * 2 + 2, "__");
        if (game.current_field.field[i][j] == 1) mvprintw(i + 1, j * 2 + 2, "[]");
      }
    }
}