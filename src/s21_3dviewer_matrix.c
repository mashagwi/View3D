#include <math.h>

#include "parser.h"

matrix_t s21_create_matrix(int rows, int columns) {
  matrix_t result;
  result.columns = columns;
  result.rows = rows;
  if (rows > 0 && columns > 0) {
    result.matrix = (float**)calloc(rows, sizeof(float*));
    for (int i = 0; i < result.rows; i++) {
      result.matrix[i] = (float*)calloc(result.columns, sizeof(float));
    }
    result.matrix_type = ZERO_MATRIX;
  } else {
    result.matrix_type = INCORRECT_MATRIX;
    result.columns = 0;
    result.rows = 0;
    result.matrix = NULL;
  }
  return result;
}

void s21_remove_matrix(matrix_t* A) {
  if (A != NULL) {
    if (A->rows > 0 && A->columns > 0) {
      for (int i = 0; i < A->rows; i++) {
        free(A->matrix[i]);
      }
      free(A->matrix);
      A->matrix = NULL;
      A->columns = 0;
      A->rows = 0;
      A->matrix_type = INCORRECT_MATRIX;
    }
  }
}

matrix_t return_x(float a) {
  matrix_t result = s21_create_matrix(4, 4);
  result.matrix[0][0] = result.matrix[3][3] = 1.0;
  result.matrix[1][1] = result.matrix[2][2] = cos(a);
  result.matrix[2][1] = sin(a);
  result.matrix[1][2] = -sin(a);
  result.matrix_type = CORRECT_MATRIX;
  return result;
}

matrix_t return_y(float a) {
  matrix_t result = s21_create_matrix(4, 4);
  result.matrix[1][1] = result.matrix[3][3] = 1.0;
  result.matrix[2][2] = result.matrix[0][0] = cos(a);
  result.matrix[0][2] = sin(a);
  result.matrix[2][0] = -sin(a);
  result.matrix_type = CORRECT_MATRIX;
  return result;
}

matrix_t return_z(float a) {
  matrix_t result = s21_create_matrix(4, 4);
  result.matrix[2][2] = result.matrix[3][3] = 1.0;
  result.matrix[1][1] = result.matrix[0][0] = cos(a);
  result.matrix[1][0] = sin(a);
  result.matrix[0][1] = -sin(a);
  result.matrix_type = CORRECT_MATRIX;
  return result;
}

matrix_t rotating(float ax, float ay, float az) {
  matrix_t x = return_x(ax);
  matrix_t y = return_y(ay);
  matrix_t z = return_z(az);
  matrix_t xy = s21_mult_matrix(&x, &y);
  matrix_t result = s21_mult_matrix(&xy, &z);

  s21_remove_matrix(&x);
  s21_remove_matrix(&y);
  s21_remove_matrix(&z);
  s21_remove_matrix(&xy);

  return result;
}

matrix_t shifting(float a, float b, float c) {
  matrix_t result = s21_create_matrix(4, 4);
  for (int i = 0; i < result.rows; i++) {
    result.matrix[i][i] = 1.0;
  }
  result.matrix[0][3] = a;
  result.matrix[1][3] = b;
  result.matrix[2][3] = c;
  result.matrix_type = CORRECT_MATRIX;
  return result;
}

matrix_t scaling(float a, float b, float c) {
  matrix_t result = s21_create_matrix(4, 4);
  result.matrix[0][0] = a;
  result.matrix[1][1] = b;
  result.matrix[2][2] = c;
  result.matrix[3][3] = 1.0;
  result.matrix_type = CORRECT_MATRIX;
  return result;
}

matrix_t matrix_alteration(float ax, float ay, float az, float da, float db,
                        float dc, float ka, float kb, float kc) {
  matrix_t rotate = rotating(ax, ay, az);
  matrix_t shift = shifting(da, db, dc);
  matrix_t scale = scaling(ka, kb, kc);

  matrix_t rs = s21_mult_matrix(&rotation, &shift);
  matrix_t result = s21_mult_matrix(&rs, &scaling);

  s21_remove_matrix(&rotate);
  s21_remove_matrix(&shift);
  s21_remove_matrix(&scale);
  s21_remove_matrix(&rs);

  return result;
}