#include "parser.h"

void initializeOBJData(OBJData** objData) {
  (*objData) = calloc(1, sizeof(OBJData));
  (*objData)->vertexCount = 0;
  (*objData)->faceCount = 0;
  (*objData)->vertices = NULL;
  (*objData)->faces = NULL;
  (*objData)->maxVertexValue = 0.0f;
  (*objData)->maxFaceValue = 0;
}

int parseOBJFile(const char* filename, OBJData** objData) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    return EXIT_FAILURE;
  }

  initializeOBJData(objData);

  char* line = calloc(256, sizeof(char));
  while (fgets(line, 256, file) != NULL) {
    if (line[0] == '#') {
      // Это комментарий, пропустить строку
      continue;
    } else if (line[0] == 'v' && line[1] == ' ') {
      // Обработка вершин (v)
      (*objData)->vertexCount++;
      if ((*objData)->vertexCount == 1) {
        (*objData)->vertices = calloc(1, sizeof(float) * 3);
      } else
        (*objData)->vertices = realloc(
          (*objData)->vertices, (*objData)->vertexCount * 3 * sizeof(float));
      float x, y, z;
      sscanf(line + 2, "%f %f %f", &x, &y, &z);
      (*objData)->vertices[((*objData)->vertexCount - 1) * 3] = x;
      (*objData)->vertices[((*objData)->vertexCount - 1) * 3 + 1] = y;
      (*objData)->vertices[((*objData)->vertexCount - 1) * 3 + 2] = z;

      // Обновление максимальных значений
      float maxCoord = x > y ? (x > z ? x : z) : (y > z ? y : z);
      if (maxCoord > (*objData)->maxVertexValue) {
        (*objData)->maxVertexValue = maxCoord;
      }
    } else if (line[0] == 'f' && line[1] == ' ') {
      // Обработка граней (f)
      (*objData)->faceCount++;
      if ((*objData)->faceCount == 1) {
        (*objData)->faces = calloc(1, sizeof(face));
      } else
        (*objData)->faces =
          realloc((*objData)->faces, (*objData)->faceCount * sizeof(face));

      int number = 0, offset = 0;
      char *data = line + 2;
      (*objData)->faces[(*objData)->faceCount - 1].count_number_vertex = 0;
      int i = 0;
      while (sscanf(data, "%d%n", &number, &offset) == 1) {
        data += offset;
        (*objData)->faces[(*objData)->faceCount - 1].count_number_vertex++;
        if ((*objData)->faces[(*objData)->faceCount - 1].count_number_vertex == 1)
            (*objData)->faces[(*objData)->faceCount - 1].number_vertex = calloc(1, sizeof(int));
        else
            (*objData)->faces[(*objData)->faceCount - 1].number_vertex = realloc((*objData)->faces[(*objData)->faceCount - 1].number_vertex, (*objData)->faces[(*objData)->faceCount - 1].count_number_vertex * sizeof(int));
        (*objData)->faces[(*objData)->faceCount - 1].number_vertex[i++] = number;
      }

      // Обновление максимального значения
      //int maxIndex = v1 > v2 ? (v1 > v3 ? v1 : v3) : (v2 > v3 ? v2 : v3);
//      if (maxIndex > (*objData)->maxFaceValue)
//        (*objData)->maxFaceValue = maxIndex;
    }
  }
  free(line);
  fclose(file);
  // remove_array(objData);
  // free(objData);
  return EXIT_SUCCESS;
}

void freeOBJData(OBJData* objData) {
    for (int i = 0; i < objData->faceCount; i++) {
        free(objData->faces[i].number_vertex);
    }
    free(objData->faces);
    free(objData->vertices);
    free(objData);
}