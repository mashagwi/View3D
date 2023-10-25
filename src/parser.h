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

/// @brief Инициализация структуры OBJData.
/// @param objData Указатель на указатель на структуру OBJData.
void initializeOBJData(OBJData** objData);

/// @brief Парсинг файла формата OBJ и заполнение структуры OBJData.
/// @param filename Имя файла для парсинга.
/// @param objData Указатель на указатель на структуру OBJData, в которую будет
/// сохранена информация.
/// @return Возвращает 0 в случае успешного парсинга, и другое значение в случае
/// ошибки.
int parseOBJFile(const char* filename, OBJData** objData);

/// @brief Освобождение памяти, выделенной под структуру OBJData.
/// @param objData Указатель на структуру OBJData, которую нужно освободить.
void freeOBJData(OBJData* objData);

/// @brief Создание матрицы с заданным количеством строк и столбцов.
matrix_t s21_create_matrix(int rows, int columns);

/// @brief Освобождение памяти, выделенной под матрицу.
/// @param A Указатель на матрицу для освобождения.
void s21_remove_matrix(matrix_t* A);

/// @brief Умножение двух матриц A и B.
matrix_t s21_mult_matrix(matrix_t* A, matrix_t* B);

/// @brief Проверка равенства двух матриц A и B.
int s21_eq_matrix(matrix_t* A, matrix_t* B);

/// @brief Создание матрицы для вращения вокруг оси X на угол a.
matrix_t return_x(float a);

/// @brief Создание матрицы для вращения вокруг оси Y на угол a.
matrix_t return_y(float a);

/// @brief Создание матрицы для вращения вокруг оси Z на угол a.
matrix_t return_z(float a);

/// @brief Создание матрицы для произвольного вращения вокруг осей X, Y и Z.
matrix_t rotating(float ax, float ay, float az);

/// @brief Создание матрицы для перемещения по координатам a, b, c.
matrix_t shifting(float a, float b, float c);

/// @brief Создание матрицы для масштабирования на коэффициент a.
matrix_t scaling(float a);

/// @brief Создание матрицы для сочетания всех изменений: вращения (ax, ay, az),
///        перемещения (da, db, dc) и масштабирования (ka).
matrix_t matrix_alteration(float ax, float ay, float az, float da, float db,
                           float dc, float ka);

/// @brief Сравнивает две матрицы A и B на равенство.
/// @param A Указатель на первую матрицу.
/// @param B Указатель на вторую матрицу.
/// @return 0, если матрицы не равны; 1, если матрицы равны.
int s21_eq_matrix(matrix_t* A, matrix_t* B);

/// @brief Заполняет матрицу A случайными данными.
/// @param A Указатель на матрицу, которую необходимо заполнить.
void fill_matrix(matrix_t* A);

/// @brief Заполняет матрицу A данными из массива arr.
/// @param A Указатель на матрицу, которую необходимо заполнить.
/// @param arr Указатель на массив данных для заполнения матрицы.
void matrix_fill_array(matrix_t* A, const double* arr);

/// @brief Проверяет корректность матрицы A.
/// @param A Указатель на матрицу, которую необходимо проверить.
/// @return 1, если матрица корректна; 0, если матрица содержит ошибки или не
/// корректна.
int s21_correct_matrix(matrix_t* A);

#endif  // S21_3D_VIEWER_PARSER_H
