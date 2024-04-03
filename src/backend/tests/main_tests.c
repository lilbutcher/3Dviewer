#include "tests.h"

int main() {
  int error = 0;
  Suite *s;
  SRunner *runner;

  s = parse_file_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  srunner_ntests_failed(runner);
  srunner_free(runner);
  return (error == 0) ? 1 : 0;
}