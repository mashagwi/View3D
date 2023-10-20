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
    matrix_alt = s21_create_matrix(4, 4);

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

    if(probe != NULL) {
        int index1, index2;
        glColor3f(v_red, v_green, v_blue);
        glPointSize(vertices_size);
        glBegin(GL_POINTS);
        for (int i = 0; i < probe->vertexCount; i++) {
            coordinate source = {probe->vertices[i * 3], probe->vertices[i * 3 + 1], probe->vertices[i * 3 + 2]};
            coordinate destination = transform(source);
            glVertex3f(destination.x, destination.y, destination.z);
        }
        glEnd();
        for (int i = 0; i < probe->faceCount; i++) {  // перебираем полигоны
            for (int j = 0; j < probe->faces[i].count_number_vertex; j++) {  // перебираем линии в полигоне
                index1 = probe->faces[i].number_vertex[j] - 1;
                if (j == probe->faces[i].count_number_vertex - 1)
                    index2 = probe->faces[i].number_vertex[0] - 1;
                else
                    index2 = probe->faces[i].number_vertex[j + 1] - 1;
                glBegin(GL_LINES);
                glColor3f(f_red, f_green, f_blue);
                glLineWidth(lines_width);
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
    for (int i = 0; i < 3; i++) {
        matrix_alt.matrix[i][i] = element;
    }
    matrix_alt.matrix[3][3] = 1.0;
}

coordinate View::transform(coordinate input) {
    matrix_t B = s21_create_matrix(4, 1);
    B.matrix[0][0] = input.x;
    B.matrix[1][0] = input.y;
    B.matrix[2][0] = input.z;
    B.matrix[3][0] = 1.0;
    matrix_t C = s21_mult_matrix(&matrix_alt, &B);
    coordinate result = {C.matrix[0][0], C.matrix[1][0], C.matrix[2][0]};
    s21_remove_matrix(&B);
    return result;
}
