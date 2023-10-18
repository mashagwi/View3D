#ifndef VIEW_H
#define VIEW_H

#define GL_SILENCE_DEPRECATION

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QColor>

extern "C" {
     #include "parser.h"
 }

#define RGB_MIN 1
#define RGB_MAX 255

class View: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    View(QWidget *parent = nullptr);

    int project_type = 0;
    int vert_type = 0;
    int face_type = 0;
    int face_thickness = 0;
    OBJData *probe = {};
    double v_red = 1, v_green = 1, v_blue = 1;
    double f_red = 1, f_green = 1, f_blue = 1;
    double b_red = 0, b_green = 0, b_blue = 0;

    void my_paint();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    void qColorToRGB(const QColor &C, float &r, float &g, float &b) const;
    float normaliza_0_1(float val, float min, float max) const;
};

#endif // VIEW_H
