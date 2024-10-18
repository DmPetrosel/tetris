#include <time.h>

#include "../../../gui/cli/frontend.h"
#include "../inc/fsm_header.h"
#include "../inc/logic.h"
#include "../inc/objects.h"

Game_t* game_init() {
  static Game_t* state = NULL;
  if (state == NULL) state = malloc(sizeof(Game_t));
  if (state == NULL) {
    printf("Error: malloc failed\n");
    exit(1);
  }
  return state;
}

action fsm_table[6][8] = {
    {start, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},
    {NULL, pause, gameover, move_left, move_right, move_up, moved, moved},
    {NULL, pause, NULL, NULL, NULL, NULL, NULL, NULL},
    {collide, collide, collide, collide, collide, collide, collide, collide},
    {gameover, gameover, gameover, gameover, gameover, gameover, gameover,
     gameover},
};

void userInput(UserAction_t sig, int hold) {
  Game_t* state = game_init();
  action act = fsm_table[state->current_state][sig];

  if (act && !hold) {
    act(state);
  }
}