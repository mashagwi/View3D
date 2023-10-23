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

int s21_eq_matrix(matrix_t* A, matrix_t* B) {
  int result = EXIT_FAILURE;
  if (!s21_correct_matrix(A) && !s21_correct_matrix(B)) {
    result = EXIT_SUCCESS;
    for (int i = 0; i < A->rows && result == EXIT_SUCCESS; i++) {
      for (int j = 0; j < A->columns && result == EXIT_SUCCESS; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          result = EXIT_FAILURE;
        }
      }
    }
  }
  return result;
}

matrix_t s21_mult_matrix(matrix_t* A, matrix_t* B) {
  matrix_t result;
  if (!s21_correct_matrix(A) && !s21_correct_matrix(B) &&
      A->columns == B->rows) {
    result = s21_create_matrix(A->rows, B->columns);
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }

  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

int s21_correct_matrix(matrix_t* A) {
  int err = 0;
  if (A->rows < 1 || A->columns < 1 || !A->matrix) err = 1;
  return err;
}

void fill_matrix(matrix_t* A) {
  if (A->rows > 0 && A->columns > 0) {
    double f = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = f;
        f++;
      }
    }
    A->matrix_type = OK;
  }
}

void matrix_fill_array(matrix_t* A, const double* arr) {
  if (s21_correct_matrix(A) == 0) {
    int it = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = arr[it];
        it++;
      }
    }
  }
}

matrix_t return_x(float a) {
  matrix_t result = s21_create_matrix(4, 4);
  result.matrix[0][0] = result.matrix[3][3] = 1.0;
  result.matrix[1][1] = result.matrix[2][2] = cos(a);
  result.matrix[2][1] = sin(a);
  result.matrix[1][2] = -sin(a);
  result.matrix_type = OK;
  return result;
}

matrix_t return_y(float a) {
  matrix_t result = s21_create_matrix(4, 4);
  result.matrix[1][1] = result.matrix[3][3] = 1.0;
  result.matrix[2][2] = result.matrix[0][0] = cos(a);
  result.matrix[0][2] = sin(a);
  result.matrix[2][0] = -sin(a);
  result.matrix_type = OK;
  return result;
}

matrix_t return_z(float a) {
  matrix_t result = s21_create_matrix(4, 4);
  result.matrix[2][2] = result.matrix[3][3] = 1.0;
  result.matrix[1][1] = result.matrix[0][0] = cos(a);
  result.matrix[1][0] = sin(a);
  result.matrix[0][1] = -sin(a);
  result.matrix_type = OK;
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
  result.matrix_type = OK;
  return result;
}

matrix_t scaling(float a) {
  matrix_t result = s21_create_matrix(4, 4);
  result.matrix[0][0] = a;
  result.matrix[1][1] = a;
  result.matrix[2][2] = a;
  result.matrix[3][3] = 1.0;
  result.matrix_type = OK;
  return result;
}

matrix_t matrix_alteration(float ax, float ay, float az, float da, float db,
                           float dc, float ka) {
  matrix_t rotate = rotating(ax, ay, az);
  matrix_t shift = shifting(da, db, dc);
  matrix_t scale = scaling(ka);

  matrix_t rs = s21_mult_matrix(&rotate, &shift);

  matrix_t result = s21_mult_matrix(&rs, &scale);

  s21_remove_matrix(&rotate);
  s21_remove_matrix(&shift);
  s21_remove_matrix(&scale);
  s21_remove_matrix(&rs);

  return result;
}
