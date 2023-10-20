#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "view.h"
#include <QSettings>
#define COEF_SHIFT 0.01
#define COEF_ROTATE 0.0628319

extern "C" {
     #include "parser.h"
 }

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    enum vert_type { NO, CIRCLE, SQUARE };
    enum face_type { SOLID, DASHED };
    enum project_type { PARALLEL, CENTRAL };

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void default_val();

    void on_v_circle_clicked();

    void on_v_square_clicked();

    void on_v_no_clicked();

//    void on_scale_valueChanged(int value);

    void on_f_solid_clicked();

    void on_f_dashed_clicked();

    void on_check_color_back_clicked();

    void on_check_color_face_clicked();

    void on_check_color_vert_clicked();

    void on_thickness_valueChanged(int value);

    void on_rotate_x_valueChanged(int value);

    void on_rotate_y_valueChanged(int value);

    void on_rotate_z_valueChanged(int value);

    void on_translate_x_valueChanged(int value);

    void on_translate_y_valueChanged(int value);

    void on_translate_z_valueChanged(int value);



    void on_projection_currentIndexChanged(int index);

    void on_scale_min_clicked();

    void on_scale_max_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
