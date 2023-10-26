#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>

#include "qgifimage.h"
#include "view.h"

extern "C" {
#include "parser.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);

  enum vert_type { NO, CIRCLE, SQUARE };
  enum face_type { SOLID, DASHED, NONE };
  enum project_type { PARALLEL, CENTRAL };

  ~MainWindow();

 private slots:
  /// @brief Устанавливает значения по умолчанию.
  void default_val();

  /// @brief Сохраняет текущие настройки.
  void saveSettings();

  /// @brief Устанавливает информацию о файле, количестве вершин и линиях.
  /// @param filename Имя файла.
  /// @param verticles Количество вершин.
  /// @param lines Количество линий.
  void set_info(QString filename, int verticles, int lines);

  /// @brief Обработчик события нажатия на кнопку "ОК".
  void on_pushButton_clicked();

  /// @brief Обработчик события выбора круговых вершин.
  void on_v_circle_clicked();

  /// @brief Обработчик события выбора квадратных вершин.
  void on_v_square_clicked();

  /// @brief Обработчик события выбора отсутствия вершин.
  void on_v_no_clicked();

  /// @brief Обработчик события выбора сплошной заливки.
  void on_f_solid_clicked();

  /// @brief Обработчик события выбора пунктирной заливки.
  void on_f_dashed_clicked();

  /// @brief Обработчик события выбора цвета фона.
  void on_check_color_back_clicked();

  /// @brief Обработчик события выбора цвета грани.
  void on_check_color_face_clicked();

  /// @brief Обработчик события выбора цвета вершин.
  void on_check_color_vert_clicked();

  /// @brief Обработчик изменения значения толщины линий.
  /// @param value Новое значение толщины.
  void on_thickness_valueChanged(int value);

  /// @brief Обработчик изменения значения поворота по X.
  /// @param value Новое значение поворота.
  void on_rotate_x_valueChanged(int value);

  /// @brief Обработчик изменения значения поворота по Y.
  /// @param value Новое значение поворота.
  void on_rotate_y_valueChanged(int value);

  /// @brief Обработчик изменения значения поворота по Z.
  /// @param value Новое значение поворота.
  void on_rotate_z_valueChanged(int value);

  /// @brief Обработчик изменения значения трансляции по X.
  /// @param value Новое значение трансляции.
  void on_translate_x_valueChanged(int value);

  /// @brief Обработчик изменения значения трансляции по Y.
  /// @param value Новое значение трансляции.
  void on_translate_y_valueChanged(int value);

  /// @brief Обработчик изменения значения трансляции по Z.
  /// @param value Новое значение трансляции.
  void on_translate_z_valueChanged(int value);

  /// @brief Обработчик выбора типа проекции.
  /// @param index Индекс выбранной проекции.
  void on_projection_currentIndexChanged(int index);

  /// @brief Обработчик события уменьшения масштаба.
  void on_scale_min_clicked();

  /// @brief Обработчик события увеличения масштаба.
  void on_scale_max_clicked();

  /// @brief Обработчик изменения значения ширины моста HSB.
  /// @param value Новое значение ширины моста HSB.
  void on_hsbWidth_valueChanged(int value);

  /// @brief Обработчик изменения значения масштабирования.
  /// @param value Новое значение масштабирования.
  void on_scale_value_valueChanged(int value);

  /// @brief Сохраняет скриншот в выбранном формате.
  void on_save_screenshot_clicked();

  /// @brief Запускает таймер для создания анимации GIF.
  void on_save_gif_clicked();

  /// @brief Создает анимацию GIF и сохраняет её.
  void slotTimer();

  void on_f_no_clicked();

  void on_MainWindow_destroyed();

 private:
  Ui::MainWindow *ui;

  QString settingFile;
  QTimer *timer;
  QGifImage *gif;
  QImage *gifImage;
  int gifTime = 0;
};
#endif  // MAINWINDOW_H
