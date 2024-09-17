#include "frontend.h"
#include "../inc/objects.h"
#include "../inc/defines.h"


bool print_game_field(Game_t game) {
  bool error = EXIT_SUCCESS;
  if (game.current_field.field != NULL) {
    for (int i = 0; i < ROWS_FIELD; i++) {
      for (int j = 0; j < COLS_FIELD; j++) {
        if (game.current_field.field[i][j] == 0) mvprintw(i + 1, j * 2 + 2, "_");
        if (game.current_field.field[i][j] == 1) mvprintw(i + 1, j * 2 + 2, "[]");
      }
    }
  } else
    error = EXIT_FAILURE;
  return error;
}