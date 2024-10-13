#include "s21_tests.h"
// #include <check.h>

// #include "../brick_game/tetris/inc/fsm_header.h"
// #include "../brick_game/tetris/inc/logic.h"
// #include "../brick_game/tetris/inc/objects.h"

Suite *test_logic(void);

int main(void) {
  int num_failures = 0;
  int num_of_tests = 0;

  Suite *test_suite[] = {test_logic(), NULL

  };

  for (int i = 0; test_suite[i] != NULL; i++) {
    SRunner *runner = srunner_create(test_suite[i]);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    num_failures += srunner_ntests_failed(runner);
    num_of_tests += srunner_ntests_run(runner);
    srunner_free(runner);
  }

  printf("============== NUMBER OF FAILURES:\t %d \t============\n",
         num_failures);
  printf("============== \t TOTAL OF TESTS:\t %d \t============\n",
         num_of_tests);
}