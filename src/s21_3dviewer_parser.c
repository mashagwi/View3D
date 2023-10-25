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
  initializeOBJData(objData);

  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    freeOBJData(*objData);
    return EXIT_FAILURE;
  }

  char* line = calloc(256, sizeof(char));
  while (fgets(line, 256, file) != NULL) {
    if (line[0] == '#') {
      continue;
    } else if (line[0] == 'v' && line[1] == ' ') {
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

      float maxCoord = x > y ? (x > z ? x : z) : (y > z ? y : z);
      if (maxCoord > (*objData)->maxVertexValue) {
        (*objData)->maxVertexValue = maxCoord;
      }
    } else if (line[0] == 'f' && line[1] == ' ') {
      (*objData)->faceCount++;
      if ((*objData)->faceCount == 1) {
        (*objData)->faces = calloc(1, sizeof(face));
      } else
        (*objData)->faces =
            realloc((*objData)->faces, (*objData)->faceCount * sizeof(face));

      int number = 0, offset = 0;
      char* data = line + 2;
      (*objData)->faces[(*objData)->faceCount - 1].count_number_vertex = 0;
      int i = 0;
      while (sscanf(data, "%d%n", &number, &offset) == 1) {
        data += offset;
        (*objData)->faces[(*objData)->faceCount - 1].count_number_vertex++;
        if ((*objData)->faces[(*objData)->faceCount - 1].count_number_vertex ==
            1)
          (*objData)->faces[(*objData)->faceCount - 1].number_vertex =
              calloc(1, sizeof(int));
        else
          (*objData)->faces[(*objData)->faceCount - 1].number_vertex = realloc(
              (*objData)->faces[(*objData)->faceCount - 1].number_vertex,
              (*objData)->faces[(*objData)->faceCount - 1].count_number_vertex *
                  sizeof(int));
        (*objData)->faces[(*objData)->faceCount - 1].number_vertex[i++] =
            number;
        if (*data == '/')
          while (*data != ' ' && *data != '\0') data++;
      }
    }
  }
  free(line);
  fclose(file);
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
