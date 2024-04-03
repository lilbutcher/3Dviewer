#include "tests.h"

#include <check.h>

#include "../3d_viewer.h"

#define eps 1e-6

START_TEST(test_1) {
  Data *data3d = malloc(sizeof(Data));
  data3d->v = malloc(sizeof(vertex));
  double answer_v[5][8] = {{0.0, 0.35, 0.0},
                           {-0.7, -.35, -.7},
                           {0.7, -0.35, -0.7},
                           {0.7, -0.35, 0.7},
                           {-0.7, -0.35, 0.7}};

  char filename[100] = {"pyramid.txt"};
  *data3d = parse_file(filename, data3d);
  printf("\nvertexes = %d polygons = % d\n", data3d->v->amount_vert,
         data3d->amount_polygon);
  for (int i = 0; i < data3d->v->amount_vert; i++) {
    printf("v_turn_x %f %f %f \n", data3d->v->coord[i].x, data3d->v->coord[i].y,
           data3d->v->coord[i].z);
    ck_assert_double_eq_tol(data3d->v->coord[i].x, answer_v[i][0], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].y, answer_v[i][1], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].z, answer_v[i][2], eps);
  }

  for (int i = 0; i < data3d->amount_polygon; i++) {
    printf("amount_p = %d f ", data3d->p[i].amount_p);
    for (int j = 0; j < data3d->p[i].amount_p; j++) {
      printf("%d ", data3d->p[i].p[j]);
      // ck_assert_int_eq(data3d->p[i].p[j], answer_p[i][j]);
    }
    printf("\n");
  }
  ck_assert_int_eq(data3d->v->amount_vert, 5);
  ck_assert_int_eq(data3d->amount_polygon, 8);
  freeAllData(data3d);
  // free(data3d);
  // free(data3d->v);
}
END_TEST

START_TEST(turn_x) {
  Data *data3d = malloc(sizeof(Data));
  data3d->v = malloc(sizeof(vertex));
  double answer_x[5][3] = {{0.0, 0.349967, 0.004798},
                           {-0.700000, -0.340372, -0.704732},
                           {0.700000, -0.340372, -0.704732},
                           {0.700000, -0.359562, 0.695137},
                           {-0.700000, -0.359562, 0.695137}};
  char filename[100] = {"pyramid.txt"};
  double angle = M_PI / 4;  // 45 градусов
  *data3d = parse_file(filename, data3d);
  *data3d = turnX(data3d, angle);
  for (int i = 0; i < data3d->v->amount_vert; i++) {
    printf("v_turn_x %f %f %f \n", data3d->v->coord[i].x, data3d->v->coord[i].y,
           data3d->v->coord[i].z);
    ck_assert_double_eq_tol(data3d->v->coord[i].x, answer_x[i][0], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].y, answer_x[i][1], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].z, answer_x[i][2], eps);
  }
  freeAllData(data3d);
}
END_TEST

START_TEST(turn_y) {
  Data *data3d = malloc(sizeof(Data));
  data3d->v = malloc(sizeof(vertex));
  double answer_y[5][3] = {{0.0, 0.350000, 0.0},
                           {-0.709529, -0.350000, -0.690339},
                           {0.690339, -0.350000, -0.709529},
                           {0.709529, -0.350000, 0.690339},
                           {-0.690339, -0.350000, 0.709529}};
  char filename[100] = {"pyramid.txt"};
  double angle = M_PI / 4;  // 45 градусов
  *data3d = parse_file(filename, data3d);
  *data3d = turnY(data3d, angle);
  for (int i = 0; i < data3d->v->amount_vert; i++) {
    printf("v_turn_y %f %f %f \n", data3d->v->coord[i].x, data3d->v->coord[i].y,
           data3d->v->coord[i].z);
    ck_assert_double_eq_tol(data3d->v->coord[i].x, answer_y[i][0], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].y, answer_y[i][1], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].z, answer_y[i][2], eps);
  }
  freeAllData(data3d);
}
END_TEST

START_TEST(turn_z) {
  Data *data3d = malloc(sizeof(Data));
  data3d->v = malloc(sizeof(vertex));
  double answer_z[5][3] = {{0.004798, 0.349967, 0.0},
                           {-0.704732, -0.340372, -0.700000},
                           {0.695137, -0.359562, -0.700000},
                           {0.695137, -0.359562, 0.700000},
                           {-0.704732, -0.340372, 0.700000}};
  char filename[100] = {"pyramid.txt"};
  double angle = M_PI / 4;  // 45 градусов
  *data3d = parse_file(filename, data3d);
  *data3d = turnZ(data3d, angle);
  for (int i = 0; i < data3d->v->amount_vert; i++) {
    printf("v_turn_z %f %f %f \n", data3d->v->coord[i].x, data3d->v->coord[i].y,
           data3d->v->coord[i].z);
    ck_assert_double_eq_tol(data3d->v->coord[i].x, answer_z[i][0], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].y, answer_z[i][1], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].z, answer_z[i][2], eps);
  }
  freeAllData(data3d);
}
END_TEST

START_TEST(move_x) {
  const double dx = 1.0f;
  double answer_move_x[5][3] = {{0.001000, 0.350000, 0.0},
                                {-0.699000, -0.350000, -0.700000},
                                {0.701000, -0.350000, -0.700000},
                                {0.701000, -0.350000, 0.700000},
                                {-0.699000, -0.350000, 0.700000}};
  Data *data3d = malloc(sizeof(Data));
  data3d->v = malloc(sizeof(vertex));
  char filename[100] = {"pyramid.txt"};
  *data3d = parse_file(filename, data3d);
  *data3d = moveObj(data3d, dx, 0.0f, 0.0f);
  for (int i = 0; i < data3d->v->amount_vert; i++) {
    printf("v_move_x %f %f %f \n", data3d->v->coord[i].x, data3d->v->coord[i].y,
           data3d->v->coord[i].z);
    ck_assert_double_eq_tol(data3d->v->coord[i].x, answer_move_x[i][0], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].y, answer_move_x[i][1], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].z, answer_move_x[i][2], eps);
  }
  freeAllData(data3d);
}
END_TEST

START_TEST(move_y) {
  // x, y, z
  const double dy = 1.0f;
  double answer_move_y[5][3] = {{0.0, 0.351000, 0.0},
                                {-0.700000, -0.349000, -0.700000},
                                {0.700000, -0.349000, -0.700000},
                                {0.700000, -0.349000, 0.700000},
                                {-0.700000, -0.349000, 0.700000}};
  Data *data3d = malloc(sizeof(Data));
  data3d->v = malloc(sizeof(vertex));
  char filename[100] = {"pyramid.txt"};
  *data3d = parse_file(filename, data3d);
  *data3d = moveObj(data3d, 0.0f, dy, 0.0f);
  for (int i = 0; i < data3d->v->amount_vert; i++) {
    printf("v_move_y %f %f %f \n", data3d->v->coord[i].x, data3d->v->coord[i].y,
           data3d->v->coord[i].z);
    ck_assert_double_eq_tol(data3d->v->coord[i].x, answer_move_y[i][0], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].y, answer_move_y[i][1], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].z, answer_move_y[i][2], eps);
  }
  freeAllData(data3d);
}
END_TEST

START_TEST(move_z) {
  // x, y, z
  // Data moveObj(Data *data3d, double offsetX, double offsetY, double offsetZ)
  const double dz = 1.0f;
  double answer_move_z[5][3] = {{0.0, 0.367500, 0.001000},
                                {-0.735000, -0.367500, -0.699000},
                                {0.735000, -0.367500, -0.699000},
                                {0.735000, -0.367500, 0.701000},
                                {-0.735000, -0.367500, 0.701000}};
  Data *data3d = malloc(sizeof(Data));
  data3d->v = malloc(sizeof(vertex));
  char filename[100] = {"pyramid.txt"};
  *data3d = parse_file(filename, data3d);
  *data3d = moveObj(data3d, 0.0f, 0.0f, dz);
  for (int i = 0; i < data3d->v->amount_vert; i++) {
    printf("v_move_z %f %f %f \n", data3d->v->coord[i].x, data3d->v->coord[i].y,
           data3d->v->coord[i].z);
    ck_assert_double_eq_tol(data3d->v->coord[i].x, answer_move_z[i][0], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].y, answer_move_z[i][1], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].z, answer_move_z[i][2], eps);
  }
  freeAllData(data3d);
}
END_TEST

START_TEST(scale_test) {
  double answer_scale[5][3] = {{0.0, 0.175000, 0.00000},
                               {-0.350000, -0.175000, -0.350000},
                               {0.350000, -0.175000, -0.350000},
                               {0.350000, -0.175000, 0.350000},
                               {-0.350000, -0.175000, 0.350000}};
  Data *data3d = malloc(sizeof(Data));
  data3d->v = malloc(sizeof(vertex));
  char filename[100] = {"pyramid.txt"};
  const double scale = 0.5;
  *data3d = parse_file(filename, data3d);
  *data3d = scaleObj(data3d, scale);

  for (int i = 0; i < data3d->v->amount_vert; i++) {
    printf("scale %f %f %f \n", data3d->v->coord[i].x, data3d->v->coord[i].y,
           data3d->v->coord[i].z);
    ck_assert_double_eq_tol(data3d->v->coord[i].x, answer_scale[i][0], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].y, answer_scale[i][1], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].z, answer_scale[i][2], eps);
  }
  freeAllData(data3d);
}
END_TEST

START_TEST(scale_test_1) {
  double answer_scale[5][3] = {{0.000000, 0.700000, 0.000000},
                               {-1.400000, -0.700000, -1.400000},
                               {1.400000, -0.700000, -1.400000},
                               {1.400000, -0.700000, 1.400000},
                               {-1.400000, -0.700000, 1.400000}};
  Data *data3d = malloc(sizeof(Data));
  data3d->v = malloc(sizeof(vertex));
  char filename[100] = {"pyramid.txt"};
  const double scale = 2.0;
  *data3d = parse_file(filename, data3d);
  //  Data scaleObj(Data *data3d, double scale)
  *data3d = scaleObj(data3d, scale);

  for (int i = 0; i < data3d->v->amount_vert; i++) {
    printf("scale_1 %f %f %f \n", data3d->v->coord[i].x, data3d->v->coord[i].y,
           data3d->v->coord[i].z);
    ck_assert_double_eq_tol(data3d->v->coord[i].x, answer_scale[i][0], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].y, answer_scale[i][1], eps);
    ck_assert_double_eq_tol(data3d->v->coord[i].z, answer_scale[i][2], eps);
  }
  freeAllData(data3d);
}
END_TEST

Suite *parse_file_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("num_test");
  tc = tcase_create("create_num_test");
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, turn_x);
  tcase_add_test(tc, turn_y);
  tcase_add_test(tc, turn_z);
  tcase_add_test(tc, move_x);
  tcase_add_test(tc, move_y);
  tcase_add_test(tc, move_z);
  tcase_add_test(tc, scale_test);
  tcase_add_test(tc, scale_test_1);

  suite_add_tcase(s, tc);
  return s;
}
