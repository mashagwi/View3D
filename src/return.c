#include <math.h>

#include "parser.h"

void return_x(OBJData* objData, double x) {
  float angle = x * M_PI / 180;
  for (size_t i = 0; i < 3 * (size_t)objData->vertexCount; i += 3) {
    float buff_array_y = objData->vertices[i + 1];
    float buff_array_z = objData->vertices[i + 2];
    objData->vertices[i + 1] =
        cos(angle) * buff_array_y + sin(angle) * buff_array_z;
    objData->vertices[i + 2] =
        -buff_array_y * sin(angle) + cos(angle) * buff_array_z;
  }
}

void return_y(OBJData* objData, double y) {
  float angle = y * M_PI / 180;
  for (size_t i = 0; i < (size_t)objData->vertexCount * 3; i += 3) {
    float buff_array_x = objData->vertices[i];
    float buff_array_z = objData->vertices[i + 2];
    objData->vertices[i] =
        cos(angle) * buff_array_x + sin(angle) * buff_array_z;
    objData->vertices[i + 2] =
        -buff_array_x * sin(angle) + cos(angle) * buff_array_z;
  }
}

void return_z(OBJData* objData, double z) {
  float angle = z * M_PI / 180;
  for (size_t i = 0; i < 3 * (size_t)objData->vertexCount; i = i + 3) {
    float buff_array_x = objData->vertices[i];
    float buff_array_y = objData->vertices[i + 1];
    objData->vertices[i] =
        cos(angle) * buff_array_x + sin(angle) * buff_array_y;
    objData->vertices[i + 1] =
        -buff_array_x * sin(angle) + cos(angle) * buff_array_y;
  }
}
