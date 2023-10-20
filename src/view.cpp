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


  //    QOpenGLWidget *widget = new QOpenGLWidget(parent);
  //    QSurfaceFormat format;
  //    format.setDepthBufferSize(24);
  //    format.setStencilBufferSize(8);
  //    format.setVersion(3, 2);
  //    format.setProfile(QSurfaceFormat::CoreProfile);
  //    widget->setFormat(format); // must be called before the widget or its
  //    parent window gets shown
}

void View::paintGL() {
    glClearColor(b_red, b_green, b_blue, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (this->vert_type == 1) {
        paint_vertices();
    }
    if (this->face_type == 1) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
      }
    glLineWidth(this->face_thickness);



    if(probe != NULL) {
        int index1, index2;
        for (int i = 0; i < probe->faceCount; i++) {  // перебираем полигоны
            for (int j = 0; j < probe->faces[i].count_number_vertex; j++) {  // перебираем линии в полигоне
                index1 = probe->faces[i].number_vertex[j] - 1;
                if (j == probe->faces[i].count_number_vertex - 1)
                    index2 = probe->faces[i].number_vertex[0] - 1;
                else
                    index2 = probe->faces[i].number_vertex[j + 1] - 1;
                glBegin(GL_LINES);
                glColor3f(f_red, f_green, f_blue);
                coordinate source = {probe->vertices[index1 * 3], probe->vertices[index1 * 3 + 1], probe->vertices[index1 * 3 + 2]};
                coordinate destination = transform(source);
                glVertex3f(destination.x, destination.y, destination.z);
                source.x = probe->vertices[index2 * 3];
                source.y = probe->vertices[index2 * 3 + 1];
                source.z = probe->vertices[index2 * 3 + 2];
                destination = transform(source);
                glVertex3f(destination.x, destination.y, destination.z);



                glEnd();
            }
        }
    }
}


void View::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //        m_projection.setToIdentity();
  //        m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
}


void View::my_paint() {
    float element = COEFF_PART / probe->maxVertexValue;
//    matrix_transformation[0][0] = element;
//    matrix_transformation[0][1] = 0;
//    matrix_transformation[0][2] = 0;
//    matrix_transformation[1][0] = 0;
//    matrix_transformation[1][1] = element;
//    matrix_transformation[1][2] = 0;
//    matrix_transformation[2][0] = 0;
//    matrix_transformation[2][1] = 0;
//    matrix_transformation[2][2] = element;



    paintGL();
}

coordinate View::transform(coordinate input) {
    coordinate result = {0, 0, 0};
    result.x = (matrix_transformation[0][0] * input.x + matrix_transformation[0][1] * input.y + matrix_transformation[0][2] * input.z);
    result.y = (matrix_transformation[1][0] * input.x + matrix_transformation[1][1] * input.y + matrix_transformation[1][2] * input.z);
    result.z = (matrix_transformation[2][0] * input.x + matrix_transformation[2][1] * input.y + matrix_transformation[2][2] * input.z);
    return result;
}

void View::divide(Matrix A, Matrix B, Matrix *C) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            *C[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                *C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void View::paint_vertices() {
  if (this->vert_type == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(this->vertices_size);
  glColor3f(this->v_red, this->v_green, this->v_blue);
  glDrawArrays(GL_POINTS, 0, probe->vertexCount);
  if (this->vert_type == 1) {
    glDisable(GL_POINT_SMOOTH);
  }
}
