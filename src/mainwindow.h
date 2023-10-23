#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "view.h"
#include <QSettings>

#include "qgifimage.h"

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
    void default_val();

    void saveSettings();

    void set_info(QString filename, int verticles, int lines);

    void on_pushButton_clicked();

    void on_v_circle_clicked();

    void on_v_square_clicked();

    void on_v_no_clicked();

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

    void on_hsbWidth_valueChanged(int value);

    void on_scale_value_valueChanged(int value);

    /// @brief Сохраняет скрин в выбранном формате
    void on_save_screenshot_clicked();

    /// @brief Сбрасывает все в начальное состояние
    void on_reset_clicked();

    /// @brief Запускает таймер для создания gif
    void on_save_gif_clicked();

    /// @brief Делает gif и сохраняет
    void slotTimer();

private:
    Ui::MainWindow *ui;

    QString settingFile;
    QTimer *timer;
    QGifImage *gif;
    QImage *gifImage;
    int gifTime = 0;
};
#endif // MAINWINDOW_H
