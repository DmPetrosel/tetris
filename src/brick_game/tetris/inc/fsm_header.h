#ifndef FSM_HEADER_H_
#define FSM_HEADER_H_

#include "../../../gui/cli/frontend.h"
#include "defines.h"
#include "objects.h"
Game_t *game_init();
void userInput(UserAction_t sig, int hold);
typedef void (*action)(Game_t *state);
void game_loop();

#endif  // FSM_HEADER_H_