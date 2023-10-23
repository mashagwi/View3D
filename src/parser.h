#ifndef S21_3D_VIEWER_PARSER_H
#define S21_3D_VIEWER_PARSER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS 1e-07

typedef struct face_t {
  int* number_vertex;       // массив индексов вершин
  int count_number_vertex;  // количество вершин в полигоне
} face;

typedef struct {
  int vertexCount;  // количество вершин
  float* vertices;  // массив вершин (x, y, z)
  face* faces;      // массив полигонов
  int faceCount;    // количество граней
  float maxVertexValue;  // максимальное значение среди всех вершин
  int maxFaceValue;  // максимальное значение среди всех граней
} OBJData;

typedef enum {
  OK = 0,                // корректная матрица
  INCORRECT_MATRIX = 1,  // ошибка в матрице
  ZERO_MATRIX = 3,       // нулевая матрица
} matrix_type_t;

typedef struct matrix_struct {
  float** matrix;
  int rows;
  int columns;
  matrix_type_t matrix_type;
} matrix_t;

void initializeOBJData(OBJData** objData);  // инициализация структуры

int parseOBJFile(const char* filename, OBJData** objData);  // парсинг файла

void freeOBJData(OBJData* objData);  // освобождение памяти

// Работа с матрицами
matrix_t s21_create_matrix(int rows, int columns);

void s21_remove_matrix(matrix_t* A);

matrix_t s21_mult_matrix(matrix_t* A, matrix_t* B);

int s21_correct_matrix(matrix_t* A);

int s21_eq_matrix(matrix_t* A, matrix_t* B);

void fill_matrix(matrix_t* A);

void matrix_fill_array(matrix_t* A, const double* arr);

matrix_t return_x(float a);  // вращение вокруг оси X

matrix_t return_y(float a);  // вращение вокруг оси Y

matrix_t return_z(float a);  // вращение вокруг оси Z

matrix_t rotating(float ax, float ay, float az);  // произвольное вращение

matrix_t shifting(float a, float b, float c);  // перемещение

matrix_t scaling(float a);  // масштабирование

matrix_t matrix_alteration(float ax, float ay, float az, float da, float db,
                           float dc, float ka);  // сочетание всех изменений

#endif  // S21_3D_VIEWER_PARSER_H
