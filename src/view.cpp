#include "view.h"

View::View(QWidget *parent) : QOpenGLWidget{parent} {}

void View::initializeGL() {
  float r, g, b, a = normaliza_0_1(255.f, RGB_MIN, RGB_MAX);
  initializeOpenGLFunctions();
  qColorToRGB(Qt::blue, r, g, b);
  glClearColor(r, g, b, a);
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
  //    float r, g, b;
  glClearColor(b_red, b_green, b_blue, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBegin(GL_LINES);
  //    qColorToRGB(Qt::black, r, g, b);
  glColor3f(f_red, f_green, f_blue);
  if(probe != NULL) {
      int n = 0;
      for (int i = 0; i < probe->faceCount; i++) {
        for (int j = 0; j < probe->faces[i].count_number_vertex; j++) {
          for (int k = 0; k < probe->faces[i].number_vertex[j]; k++) {
            glVertex3f(probe->vertices[n++], probe->vertices[n++],
                       probe->vertices[n++]);
            glVertex3f(probe->vertices[n++], probe->vertices[n++],
                       probe->vertices[n++]);
          }
        }
      }
  }
  glEnd();

//  glBegin(GL_LINES);
//  //    qColorToRGB(Qt::red, r, g, b);
//  glColor3f(f_red, f_green, f_blue);
//  glVertex3f(0.0f, 1.0f, 0.0f);
//  glVertex3f(1.0f, 0.0f, 0.0f);
//  glEnd();
  //    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  //    f->glClear(GL_COLOR_BUFFER_BIT);

  //    QOpenGLFunctions_3_2_Core *f =
  //    QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_2_Core>();

  //    f->glDrawArraysInstanced(...);
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
void View::qColorToRGB(const QColor &C, float &r, float &g, float &b) const {
  r = normaliza_0_1(C.red(), RGB_MIN, RGB_MAX);
  g = normaliza_0_1(C.green(), RGB_MIN, RGB_MAX);
  b = normaliza_0_1(C.blue(), RGB_MIN, RGB_MAX);
}

float View::normaliza_0_1(float val, float min, float max) const {
  return (val - min) / (max - min);
}

void View::my_paint() {
    paintGL();
}
