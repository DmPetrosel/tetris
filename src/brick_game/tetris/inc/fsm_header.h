#ifndef FSM_HEADER_H_
#define FSM_HEADER_H_

#include "../../../gui/cli/frontend.h"
#include "defines.h"
#include "objects.h"
/**
 * @brief This function initializes the game.
 * It creates the game object and the user interface.
 * It also sets the initial state of the game.
 * @author owynwend
 *
 * @return Game_t*
 */
Game_t *game_init();
/**
 * @brief Inputs the user action.
 * It needs according specification.
 * @author owynwend
 * @param sig
 * @param hold
 */
void userInput(UserAction_t sig, int hold);
/**
 * @brief action function. For fsm table.
 * @author owynwend
 */
typedef void (*action)(Game_t *state);
/**
 * @brief Game loop. Basic atcions in main. Hear there is starts and ends when
 * flag of the end game is set.
 * @author owynwend
 */
void game_loop();

#endif  // FSM_HEADER_H_