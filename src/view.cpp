#include "view.h"

View::View(QWidget *parent) : QOpenGLWidget{parent} {}

void View::initializeGL() {
  initializeOpenGLFunctions();

  glClearColor(b_red, b_green, b_blue, 1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
}

void View::paintGL() {
  if (project_type) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 3, 10);
    glTranslated(0.0, 0.0, -5.0);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
  }

  glClearColor(b_red, b_green, b_blue, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (probe != NULL) {
    if (vert_type != 0) {
      glColor3f(v_red, v_green, v_blue);
      glPointSize(vertices_size);
      if (vert_type == 1) glEnable(GL_POINT_SMOOTH);
      glBegin(GL_POINTS);
      for (int i = 0; i < probe->vertexCount; i++) {
        float out_x = 0.0, out_y = 0.0, out_z = 0.0;
        transform(probe->vertices[i * 3], probe->vertices[i * 3 + 1],
                  probe->vertices[i * 3 + 2], &out_x, &out_y, &out_z);
        glVertex3f(out_x, out_y, out_z);
      }
      glEnd();
      if (vert_type == 1) glDisable(GL_POINT_SMOOTH);
    }
    int index1, index2;
    glColor3f(f_red, f_green, f_blue);
    glLineWidth(lines_width);
    if (face_type == 1) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00FF);
    }
    if (face_type != 2) {
      for (int i = 0; i < probe->faceCount; i++) {  // перебираем полигоны
        for (int j = 0; j < probe->faces[i].count_number_vertex;
             j++) {  // перебираем линии в полигоне
          index1 = probe->faces[i].number_vertex[j] - 1;
          if (j == probe->faces[i].count_number_vertex - 1)
            index2 = probe->faces[i].number_vertex[0] - 1;
          else
            index2 = probe->faces[i].number_vertex[j + 1] - 1;
          glBegin(GL_LINES);
          float out_x = 0.0, out_y = 0.0, out_z = 0.0;
          transform(probe->vertices[index1 * 3],
                    probe->vertices[index1 * 3 + 1],
                    probe->vertices[index1 * 3 + 2], &out_x, &out_y, &out_z);
          glVertex3f(out_x, out_y, out_z);
          transform(probe->vertices[index2 * 3],
                    probe->vertices[index2 * 3 + 1],
                    probe->vertices[index2 * 3 + 2], &out_x, &out_y, &out_z);
          glVertex3f(out_x, out_y, out_z);
          glEnd();
        }
      }
    }
    if (face_type == 1) {
      glDisable(GL_LINE_STIPPLE);
    }
  }
}

void View::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void View::transform(float input_x, float input_y, float input_z,
                     float *output_x, float *output_y, float *output_z) {
  matrix_t B = s21_create_matrix(4, 1);
  B.matrix[0][0] = input_x;
  B.matrix[1][0] = input_y;
  B.matrix[2][0] = input_z;
  B.matrix[3][0] = 1.0;
  matrix_t C = s21_mult_matrix(&matrix_alt, &B);
  *output_x = C.matrix[0][0];
  *output_y = C.matrix[1][0];
  *output_z = C.matrix[2][0];
  s21_remove_matrix(&B);
}
