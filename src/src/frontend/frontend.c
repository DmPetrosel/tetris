#include "frontend.h"


void print_game_field(GameInfo_t game) {
  bool error = EXIT_SUCCESS;
  if (game.field != NULL) {
    for (int i = 0; i < BOARD_N; i++) {
      for (int j = 0; j < BOARD_M; j++) {
        if (game.field[i][j] == 0) MVPRINTW(i + 1, j * 2 + 2, "  ");
        if (game.field[i][j] == 1) MVPRINTW(i + 1, j * 2 + 2, "[]");
      }
    }
  } else
    error = EXIT_FAILURE;
  return error;
}