#ifndef LOGIC_H_
#define LOGIC_H_

#include "../../../gui/cli/frontend.h"
#include "defines.h"
#include "objects.h"
/**
 * @brief Check brick future position in field. We look delta_y and delta_x, and
 * check if brick can be moved.
 * @author owynwend
 * @param delta_y
 * @param delta_x
 * @param i
 * @param j
 * @return int
 */
int check_brick(int delta_y, int delta_x, int i, int j);
/**
 * @brief Rotate brick. We rotate brick by 90 degrees to the right.
 * @author owynwend
 * @return Brick_t
 */
Brick_t rotate_brick();
/**
 * @brief Check if field is full.
 * @author owynwend
 *
 */
void check_strike();
/**
 * @brief When field full and strike we shift field down with end_y to
 * row_quantity.
 * @author  owynwend
 * @param end_y
 * @param rows_quantity
 */
void shift_field_down(int end_y, int rows_quantity);
/**
 * @brief Clean screen.
 * @author owynwend
 *
 */
void clean_screan();
/**
 * @brief One func use this check.
 * @author owynwend
 * @return int
 */
int check_allowed();
/**
 * @brief Get the signal object
 * @author owynwend
 * @param user_input
 * @return UserAction_t
 */
UserAction_t get_signal(int user_input);
/**
 * @brief Here game starts.
 * @author owynwend
 *
 */
void start();
/**
 * @brief Figure appear on the screen.
 * @author owynwend
 */
void spawn();
/**
 * @brief Figure move down automatically.
 * @author owynwend
 *
 */
void moved();
/**
 * @brief Rotate figure.
 * @author  owynwend
 */
void move_up();
/**
 * @brief Move figure left.
 * @author owynwend
 */
void move_left();
/**
 * @brief Move figure right.
 * @author owynwend
 *
 */
void move_right();
/**
 * @brief Collide figure when brick touch anothe by bottom and also if spawn put
 * brick on filled field.
 * @author owynwend
 */
void collide();
/**
 * @brief End game. Exit state.
 * @author owynwend
 */
void gameover();
/**
 * @brief Check if it possible to move figure.
 * @author owynwend
 * @param delta_row
 * @param delta_col
 * @return int
 */
int can_be_moved(int delta_row, int delta_col);

/**
 * @brief Copy figure to the field.
 * @author owynwend
 *
 */
void appear();
/**
 * @brief Clean field of figure.
 *
 */
void varnish();
/**
 * @brief Generate random figure one of seven.
 * @author  owynwend
 *
 * @param brick
 */
void generate_figure(Brick_t *brick);
/**
 * @brief Pause state of game.
 * @author owynwend
 *
 */
void pause();

#endif  // LOGIC_H_