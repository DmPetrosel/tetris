#ifndef LOGIC_H_
#define LOGIC_H_

#include "../../../gui/cli/frontend.h"
#include "defines.h"
#include "objects.h"
int check_brick(int delta_y, int delta_x, int i, int j);
Brick_t rotate_brick();
void check_strike();
void shift_field_down(int end_y, int rows_quantity);
void clean_screan();
int check_allowed();

UserAction_t get_signal(int user_input);

void start();
void spawn();
void moved();
void move_up();
void move_left();
void move_right();
void collide();
void gameover();
void exitstate();
void check();
int can_be_moved(int delta_row, int delta_col);

void appear();
void varnish();

void generate_figure(Brick_t *brick);
void pause();

#endif  // LOGIC_H_