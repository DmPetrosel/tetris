#include "s21_tests.h"
#include <stdio.h>
START_TEST(s21_t_start_1) {
  Game_t *state = game_init();
  start();
  ck_assert_ptr_nonnull(&state->next_brick);
  ck_assert_int_eq(state->current_state, 1);
}
START_TEST(s21_t_pause_1) {
  Game_t *state = game_init();
  pause();
  ck_assert_int_eq(state->current_state, 3);
}

START_TEST(s21_t_clean_screen_1) {
  Game_t *state = game_init();
  clean_screan();
  ck_assert_int_eq(state->current_field.field[0][0], 0);
  ck_assert_int_eq(state->current_field.field[0][1], 0);
  ck_assert_int_eq(state->current_field.field[0][2], 0);
  ck_assert_int_eq(state->current_field.field[0][3], 0);

}
START_TEST(s21_t_gameover_1) {
  Game_t *state = game_init();
  gameover();
  ck_assert_int_eq(state->break_flag, 0);

}
START_TEST(s21_t_shift_field_down_and_check_strike_1) {
  Game_t *state = game_init();
clean_screan();
  for (int i = ROWS_FIELD - 4; i < ROWS_FIELD; i++) {
    for (int j = 0; j < COLS_FIELD; j++) {
      state->current_field.field[i][j] = 1;
    }
  }
  check_strike();
  ck_assert_int_eq(state->game_info.score, 1500);
  ck_assert_int_ne(state->game_info.high_score, 0);

  ck_assert_int_eq(state->current_field.field[ROWS_FIELD - 1][0], 0);
  ck_assert_int_eq(state->current_field.field[ROWS_FIELD - 1][1], 0);

}
START_TEST(s21_t_collide_and_spawn) {
  Game_t *state = game_init();
  clean_screan();
  start();
  spawn();
  for (int i = ROWS_FIELD - 4 - 1; i < ROWS_FIELD; i++) {
    for (int j = 0; j < COLS_FIELD; j++) {
      state->current_field.field[i][j] = 1;
    }
  }
  collide();
  ck_assert_int_eq(state->current_state, 5);

}
START_TEST(s21_t_roteate_brick) {
  Game_t *state = game_init();
    clean_screan();
  for (int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
    if(j== 0)
        state->current_brick.matrix[i][j] = 1;
    else
        state->current_brick.matrix[i][j] = 0;

    }
  }
  state->current_brick.x = 5;
  state->current_brick.y = 5;
  move_up();
  for (int i = CUR_BRICK_X; i < CUR_BRICK_X + 4; i++) {
    ck_assert_int_eq(state->current_field.field[5][i], 1);
  }

  ck_assert_int_eq(state->current_state, 2);

}
START_TEST(s21_t_moved) {
  Game_t *state = game_init();
   clean_screan();
  for (int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
    if(j== 0)
        state->current_brick.matrix[i][j] = 1;
    else
        state->current_brick.matrix[i][j] = 0;

    }
  }
  state->current_brick.x = 5;
  state->current_brick.y = 5;
  moved();
  for (int i = CUR_BRICK_Y; i < CUR_BRICK_Y + 4; i++) {
    ck_assert_int_eq(state->current_field.field[i][5], 1);
  }

  ck_assert_int_eq(state->current_state, 2);

}
START_TEST(s21_t_move_left) {
  Game_t *state = game_init();
  clean_screan();
  for (int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
    if(j== 0)
        state->current_brick.matrix[i][j] = 1;
    else
        state->current_brick.matrix[i][j] = 0;

    }
  }
  state->current_brick.x = 5;
  state->current_brick.y = 5;
  move_left();
  for (int i = CUR_BRICK_Y; i < CUR_BRICK_Y + 4; i++) {
    ck_assert_int_eq(state->current_field.field[i][4], 1);
  }

  ck_assert_int_eq(state->current_state, 2);

}
START_TEST(s21_t_move_right) {
  Game_t *state = game_init();
  clean_screan();
  for (int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
    if(j== 0)
        state->current_brick.matrix[i][j] = 1;
    else
        state->current_brick.matrix[i][j] = 0;

    }
  }
  state->current_brick.x = 5;
  state->current_brick.y = 5;
  move_right();
    // for (int i = 0; i < ROWS_FIELD; i++) {
    //     for (int j = 0; j < COLS_FIELD; j++) {
    //         if (state->current_field.field[i][j] == 0) printf("..");
    //         if (state->current_field.field[i][j] == 1) printf("[]");
    //     }
    //     printf("\n");
    // }
  
  for (int i = CUR_BRICK_Y; i < CUR_BRICK_Y + 4; i++) {
    ck_assert_int_eq(state->current_field.field[i][6], 1);
  }

  ck_assert_int_eq(state->current_state, 2);

}
Suite *test_logic(void) {
  Suite *s = suite_create("===Game logic===");
  TCase *tc = tcase_create("logic_tc");

  tcase_add_test(tc, s21_t_start_1);
  tcase_add_test(tc, s21_t_pause_1);
  tcase_add_test(tc, s21_t_clean_screen_1);
  tcase_add_test(tc, s21_t_gameover_1);
  tcase_add_test(tc, s21_t_shift_field_down_and_check_strike_1);
  tcase_add_test(tc, s21_t_collide_and_spawn);
  tcase_add_test(tc, s21_t_roteate_brick);
  tcase_add_test(tc, s21_t_moved);
  tcase_add_test(tc, s21_t_move_left);
  tcase_add_test(tc, s21_t_move_right);
  suite_add_tcase(s, tc);
  return s;
}