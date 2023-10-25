#ifndef VIEW_H
#define VIEW_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

extern "C" {
#include "parser.h"
}

#define RGB_MIN 1
#define RGB_MAX 255
#define COEFF_PART 0.8
#define COEFF_ROTATE 0.0628319
#define COEFF_SHIFT 0.01
#define COEFF_SCALE 0.6

class View : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  View(QWidget *parent = nullptr);

  OBJData *probe = {};

  int project_type = 0;
  int vert_type = 0;
  int face_type = 0;
  GLfloat vertices_size = 10.0;
  GLfloat lines_width = 1.0;
  double v_red = 1, v_green = 1, v_blue = 1;
  double f_red = 1, f_green = 1, f_blue = 1;
  double b_red = 0, b_green = 0, b_blue = 0;
  matrix_t matrix_alt;

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void transform(float, float, float, float *, float *, float *);
};

#endif  // VIEW_H
