#ifndef S21_3D_VIEWER_PARSER_H
#define S21_3D_VIEWER_PARSER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct face_t {
  int* number_vertex;
  int count_number_vertex;
} face;

typedef struct {
  int vertexCount;  // Количество вершин
  float* vertices;  // Массив вершин (x, y, z)
  face* faces;
  int faceCount;  // Количество граней
  float maxVertexValue;  // Максимальное значение среди всех вершин
  int maxFaceValue;  // Максимальное значение среди всех граней
} OBJData;

void initializeOBJData(OBJData** objData);  // инициализация структуры

int parseOBJFile(const char* filename, OBJData** objData);  // парсинг файла

void freeOBJData(OBJData* objData);  // освобождение памяти

void return_x(OBJData* objData, double x);  // поворот по оси X

void return_y(OBJData* objData, double y);  // поворот по оси Y

void return_z(OBJData* objData, double z);  // поворот по оси Z

#endif  // S21_3D_VIEWER_PARSER_H
