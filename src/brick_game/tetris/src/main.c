#include <time.h>

#include "../../../gui/cli/frontend.h"
#include "../inc/fsm_header.h"
#include "../inc/logic.h"
#include "../inc/objects.h"

int main(void) {
  WIN_INIT(50);
  setlocale(LC_ALL, "");
  game_loop();
  endwin();

  return SUCCESS;
}

void game_loop() {
  // иногда фигура в фигуру
  Game_t* state = game_init();  // заинициализировать структуру

  print_start(state);
  state->current_state = START;
  state->break_flag = TRUE;
  state->game_info.speed = SPEED_START;  // установить скорость в максимальную

  while (state->break_flag) {
    if (state->game_info.pause) {
      print_pause(state);
      print_game_field(*state);
    } else {
      print_game_field(*state);
    }
    userInput(get_signal(GET_USER_INPUT), 0);
    timeout(state->game_info.speed);
  }
  free(state);
  state = NULL;
}