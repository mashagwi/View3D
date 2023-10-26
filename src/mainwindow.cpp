#include "mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL>

#include "ui_mainwindow.h"
#include "view.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  if (QSysInfo::productType() == "windows") {
    settingFile = QCoreApplication::applicationDirPath() + "/settings.conf";
  } else if (QSysInfo::productType() == "macos") {
    this->settingFile =
        QApplication::applicationDirPath() + "/../../../settings.conf";
  } else {
    // По умолчанию, используем путь для Linux
    settingFile = QCoreApplication::applicationDirPath() + "/settings.conf";
  }

  timer = new QTimer;
  gifImage = new QImage[50]{};
  connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));

  default_val();

  char rgba_color_b[40];
  char rgba_color_f[40];
  char rgba_color_v[40];
  sprintf(rgba_color_b, "background-color: rgb(%d,%d,%d)",
          (int)(ui->openGLWidget->b_red * 255),
          (int)(ui->openGLWidget->b_green * 255),
          (int)(ui->openGLWidget->b_blue * 255));
  ui->check_color_back->setStyleSheet(rgba_color_b);

  switch (ui->openGLWidget->face_type) {
    case SOLID:
      ui->f_solid->setChecked(true);
      break;
    case DASHED:
      ui->f_dashed->setChecked(true);
      break;
    case NONE:
      ui->f_no->setChecked(true);
      break;
  }
  sprintf(rgba_color_f, "background-color: rgb(%d,%d,%d)",
          (int)(ui->openGLWidget->f_red * 255),
          (int)(ui->openGLWidget->f_green * 255),
          (int)(ui->openGLWidget->f_blue * 255));
  ui->check_color_face->setStyleSheet(rgba_color_f);

  switch (ui->openGLWidget->vert_type) {
    case NO:
      ui->v_no->setChecked(true);
      break;
    case CIRCLE:
      ui->v_circle->setChecked(true);
      break;
    case SQUARE:
      ui->v_square->setChecked(true);
      break;
  }
  sprintf(rgba_color_v, "background-color: rgb(%d,%d,%d)",
          (int)(ui->openGLWidget->v_red * 255),
          (int)(ui->openGLWidget->v_green * 255),
          (int)(ui->openGLWidget->v_blue * 255));
  ui->check_color_vert->setStyleSheet(rgba_color_v);
}

MainWindow::~MainWindow() {
  saveSettings();
  delete timer;
  delete[] gifImage;
  delete ui;
}

void MainWindow::default_val() {
  if (QFile::exists(settingFile)) {
    QSettings settings(settingFile, QSettings::IniFormat);
    settings.beginGroup("Translate");
    ui->translate_x->setValue(settings.value("x").value<int>());
    ui->translate_y->setValue(settings.value("y").value<int>());
    ui->translate_z->setValue(settings.value("z").value<int>());
    settings.endGroup();

    settings.beginGroup("Rotate");
    ui->rotate_x->setValue(settings.value("x").value<int>());
    ui->rotate_y->setValue(settings.value("y").value<int>());
    ui->rotate_z->setValue(settings.value("z").value<int>());
    settings.endGroup();

    settings.beginGroup("Scale");
    ui->scale_value->setValue(settings.value("s").value<int>());
    settings.endGroup();

    settings.beginGroup("LineSet");
    ui->openGLWidget->face_type = settings.value("face_type").value<int>();
    ui->openGLWidget->f_red = settings.value("LineColorRed").value<double>();
    ui->openGLWidget->f_green =
        settings.value("LineColorGreen").value<double>();
    ui->openGLWidget->f_blue = settings.value("LineColorBlue").value<double>();
    ui->thickness->setValue(settings.value("value").value<int>());
    settings.endGroup();

    settings.beginGroup("Verticies");
    ui->openGLWidget->vert_type = settings.value("vert_type").value<int>();
    ui->openGLWidget->v_red = settings.value("ColorRed").value<double>();
    ui->openGLWidget->v_green = settings.value("ColorGreen").value<double>();
    ui->openGLWidget->v_blue = settings.value("ColorBlue").value<double>();
    ui->hsbWidth->setValue(settings.value("size").value<int>());
    settings.endGroup();

    settings.beginGroup("background");
    ui->openGLWidget->b_red = settings.value("b_red").value<double>();
    ui->openGLWidget->b_green = settings.value("b_green").value<double>();
    ui->openGLWidget->b_blue = settings.value("b_blue").value<double>();
    settings.endGroup();
  }
}

void MainWindow::saveSettings() {
  QSettings settings(settingFile, QSettings::IniFormat);

  settings.beginGroup("Translate");
  settings.setValue("x", ui->translate_x->value());
  settings.setValue("y", ui->translate_y->value());
  settings.setValue("z", ui->translate_z->value());
  settings.endGroup();

  settings.beginGroup("Rotate");
  settings.setValue("x", ui->rotate_x->value());
  settings.setValue("y", ui->rotate_y->value());
  settings.setValue("z", ui->rotate_z->value());
  settings.endGroup();

  settings.beginGroup("Scale");
  settings.setValue("s", ui->scale_value->value());
  settings.endGroup();

  settings.beginGroup("LineSet");
  settings.setValue("face_type", ui->openGLWidget->face_type);
  settings.setValue("LineColorRed", ui->openGLWidget->f_red);
  settings.setValue("LineColorGreen", ui->openGLWidget->f_green);
  settings.setValue("LineColorBlue", ui->openGLWidget->f_blue);
  settings.setValue("value", ui->thickness->value());
  settings.endGroup();

  settings.beginGroup("Verticies");
  settings.setValue("vert_type", ui->openGLWidget->vert_type);
  settings.setValue("ColorRed", ui->openGLWidget->v_red);
  settings.setValue("ColorGreen", ui->openGLWidget->v_green);
  settings.setValue("ColorBlue", ui->openGLWidget->v_blue);
  settings.setValue("size", ui->hsbWidth->value());
  settings.endGroup();

  settings.beginGroup("background");
  settings.setValue("b_red", ui->openGLWidget->b_red);
  settings.setValue("b_green", ui->openGLWidget->b_green);
  settings.setValue("b_blue", ui->openGLWidget->b_blue);
  settings.endGroup();
}

void MainWindow::on_pushButton_clicked() {
  QString str;
  str = QFileDialog::getOpenFileName(
      this, "Выбрать файл",
      QApplication::applicationDirPath() + "/../../../../src/objects", "*.obj");
  std::string expression = str.toStdString();
  char *file = expression.data();

  parseOBJFile(file, &(ui->openGLWidget->probe));

  set_info(str, (*(ui->openGLWidget->probe)).vertexCount,
           (*(ui->openGLWidget->probe)).faceCount);

  ui->openGLWidget->matrix_alt =
      matrix_alteration(ui->rotate_x->value() * COEFF_ROTATE,
                        ui->rotate_y->value() * COEFF_ROTATE,
                        ui->rotate_z->value() * COEFF_ROTATE,
                        (ui->translate_x->value() - 50) * COEFF_SHIFT,
                        (ui->translate_y->value() - 50) * COEFF_SHIFT,
                        (ui->translate_z->value() - 50) * COEFF_SHIFT,
                        ui->scale_value->value() * COEFF_PART * COEFF_SCALE /
                            50.0 / ui->openGLWidget->probe->maxVertexValue);
  ui->openGLWidget->update();
}

void MainWindow::set_info(QString filename, int vertex, int face) {
  QStringList pieces = filename.split("/");

  ui->info->setText("Название файла:\n" + pieces[pieces.length() - 1] +
                    "\n\n Количество вершин:" + QString::number(vertex) +
                    "\n Количество линий: " + QString::number(face));
}

void MainWindow::on_v_circle_clicked() {
  ui->openGLWidget->vert_type = CIRCLE;

  ui->openGLWidget->update();
}

void MainWindow::on_v_square_clicked() {
  ui->openGLWidget->vert_type = SQUARE;
  ui->openGLWidget->update();
}

void MainWindow::on_v_no_clicked() {
  ui->openGLWidget->vert_type = NO;
  ui->openGLWidget->update();
}

void MainWindow::on_scale_min_clicked() {
  ui->scale_value->setValue(ui->scale_value->value() - 10);
}

void MainWindow::on_scale_max_clicked() {
  ui->scale_value->setValue(ui->scale_value->value() + 10);
}

void MainWindow::on_f_solid_clicked() {
  ui->openGLWidget->face_type = SOLID;
  ui->openGLWidget->update();
}

void MainWindow::on_f_dashed_clicked() {
  ui->openGLWidget->face_type = DASHED;
  ui->openGLWidget->update();
}

void MainWindow::on_f_no_clicked() {
  ui->openGLWidget->face_type = NONE;
  ui->openGLWidget->update();
}

void MainWindow::on_check_color_back_clicked() {
  QColor b_color =
      QColorDialog::getColor(Qt::white, this->ui->tabWidget, "Выбор цвета");
  if (b_color.isValid()) {
    ui->openGLWidget->b_red = b_color.redF();
    ui->openGLWidget->b_green = b_color.greenF();
    ui->openGLWidget->b_blue = b_color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", b_color.red(),
            b_color.green(), b_color.blue());
    ui->check_color_back->setStyleSheet(rgba_color);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_check_color_face_clicked() {
  QColor face_color =
      QColorDialog::getColor(Qt::white, this->ui->tabWidget, "Выбор цвета");
  if (face_color.isValid()) {
    ui->openGLWidget->f_red = face_color.redF();
    ui->openGLWidget->f_green = face_color.greenF();
    ui->openGLWidget->f_blue = face_color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", face_color.red(),
            face_color.green(), face_color.blue());
    ui->check_color_face->setStyleSheet(rgba_color);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_check_color_vert_clicked() {
  QColor vert_color =
      QColorDialog::getColor(Qt::white, this->ui->tabWidget, "Выбор цвета");
  if (vert_color.isValid()) {
    ui->openGLWidget->v_red = vert_color.redF();
    ui->openGLWidget->v_green = vert_color.greenF();
    ui->openGLWidget->v_blue = vert_color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", vert_color.red(),
            vert_color.green(), vert_color.blue());
    ui->check_color_vert->setStyleSheet(rgba_color);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_thickness_valueChanged(int value) {
  ui->openGLWidget->lines_width = value / 10;
  ui->openGLWidget->update();
}

void MainWindow::on_projection_currentIndexChanged(int index) {
  if (index == 0) {
    ui->openGLWidget->project_type = PARALLEL;
  } else if (index == 1) {
    ui->openGLWidget->project_type = CENTRAL;
  }
  ui->openGLWidget->update();
}

void MainWindow::on_rotate_x_valueChanged(int value) {
  if (ui->openGLWidget->probe != NULL) {
    ui->openGLWidget->matrix_alt = matrix_alteration(
        value * COEFF_ROTATE, ui->rotate_y->value() * COEFF_ROTATE,
        ui->rotate_z->value() * COEFF_ROTATE,
        (ui->translate_x->value() - 50) * COEFF_SHIFT,
        (ui->translate_y->value() - 50) * COEFF_SHIFT,
        (ui->translate_z->value() - 50) * COEFF_SHIFT,
        ui->scale_value->value() * COEFF_PART * COEFF_SCALE / 50.0 /
            ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_rotate_y_valueChanged(int value) {
  if (ui->openGLWidget->probe != NULL) {
    ui->openGLWidget->matrix_alt = matrix_alteration(
        ui->rotate_x->value() * COEFF_ROTATE, value * COEFF_ROTATE,
        ui->rotate_z->value() * COEFF_ROTATE,
        (ui->translate_x->value() - 50) * COEFF_SHIFT,
        (ui->translate_y->value() - 50) * COEFF_SHIFT,
        (ui->translate_z->value() - 50) * COEFF_SHIFT,
        ui->scale_value->value() * COEFF_PART * COEFF_SCALE / 50.0 /
            ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_rotate_z_valueChanged(int value) {
  if (ui->openGLWidget->probe != NULL) {
    ui->openGLWidget->matrix_alt = matrix_alteration(
        ui->rotate_x->value() * COEFF_ROTATE,
        ui->rotate_y->value() * COEFF_ROTATE, value * COEFF_ROTATE,
        (ui->translate_x->value() - 50) * COEFF_SHIFT,
        (ui->translate_y->value() - 50) * COEFF_SHIFT,
        (ui->translate_z->value() - 50) * COEFF_SHIFT,
        ui->scale_value->value() * COEFF_PART * COEFF_SCALE / 50.0 /
            ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_translate_x_valueChanged(int value) {
  if (ui->openGLWidget->probe != NULL) {
    ui->openGLWidget->matrix_alt = matrix_alteration(
        ui->rotate_x->value() * COEFF_ROTATE,
        ui->rotate_y->value() * COEFF_ROTATE,
        ui->rotate_z->value() * COEFF_ROTATE, (value - 50) * COEFF_SHIFT,
        (ui->translate_y->value() - 50) * COEFF_SHIFT,
        (ui->translate_z->value() - 50) * COEFF_SHIFT,
        ui->scale_value->value() * COEFF_PART * COEFF_SCALE / 50.0 /
            ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_translate_y_valueChanged(int value) {
  if (ui->openGLWidget->probe != NULL) {
    ui->openGLWidget->matrix_alt =
        matrix_alteration(ui->rotate_x->value() * COEFF_ROTATE,
                          ui->rotate_y->value() * COEFF_ROTATE,
                          ui->rotate_z->value() * COEFF_ROTATE,
                          (ui->translate_x->value() - 50) * COEFF_SHIFT,
                          (value - 50) * COEFF_SHIFT,
                          (ui->translate_z->value() - 50) * COEFF_SHIFT,
                          ui->scale_value->value() * COEFF_PART * COEFF_SCALE /
                              50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_translate_z_valueChanged(int value) {
  if (ui->openGLWidget->probe != NULL) {
    ui->openGLWidget->matrix_alt =
        matrix_alteration(ui->rotate_x->value() * COEFF_ROTATE,
                          ui->rotate_y->value() * COEFF_ROTATE,
                          ui->rotate_z->value() * COEFF_ROTATE,
                          (ui->translate_x->value() - 50) * COEFF_SHIFT,
                          (ui->translate_y->value() - 50) * COEFF_SHIFT,
                          (value - 50) * COEFF_SHIFT,
                          ui->scale_value->value() * COEFF_PART * COEFF_SCALE /
                              50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_hsbWidth_valueChanged(int value) {
  ui->openGLWidget->vertices_size = value / 2;
  ui->openGLWidget->update();
}

void MainWindow::on_scale_value_valueChanged(int value) {
  if (ui->openGLWidget->probe != NULL) {
    ui->openGLWidget->matrix_alt =
        matrix_alteration(ui->rotate_x->value() * COEFF_ROTATE,
                          ui->rotate_y->value() * COEFF_ROTATE,
                          ui->rotate_z->value() * COEFF_ROTATE,
                          (ui->translate_x->value() - 50) * COEFF_SHIFT,
                          (ui->translate_y->value() - 50) * COEFF_SHIFT,
                          (ui->translate_z->value() - 50) * COEFF_SHIFT,
                          value * COEFF_PART * COEFF_SCALE / 50.0 /
                              ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_save_screenshot_clicked() {
  QString format, fileName;
  int type = ui->format->currentIndex();
  if (type == 0) {
    format = ".bmp";
  } else {
    format = ".jpeg";
  }
  QFileDialog dialogPhoto(this);
  QDateTime dateTime = dateTime.currentDateTime();
  QString currentDateTime = dateTime.toString("dd.MM.yy_HH.mm.ss");
  fileName = QFileDialog::getSaveFileName(
      this, "Сохранить как...", "Screenshot_" + currentDateTime + format);
  if (!fileName.isEmpty()) {
    QImage photo = ui->openGLWidget->grab().toImage();
    QString extension = QFileInfo(fileName).suffix();
    if (extension.toLower() == "bmp") {
      photo.save(fileName, "BMP");
    } else if (extension.toLower() == "jpeg" || extension.toLower() == "jpg") {
      photo.save(fileName, "JPEG");
    }
  }
}

void MainWindow::on_save_gif_clicked() {
  saveSettings();
  ui->save_gif->setEnabled(false);
  timer->start(100);
}

void MainWindow::slotTimer() {
  if (gifTime < 50) {
    gifImage[gifTime] = ui->openGLWidget->grab().toImage();
    gifImage[gifTime] = gifImage[gifTime].scaled(640, 480);
    ++gifTime;
  } else {
    QDateTime dateTime = dateTime.currentDateTime();
    QString currentDateTime = dateTime.toString("dd.MM.yy_HH.mm.ss");
    QString fileName = QFileDialog::getSaveFileName(
        this, "Сохранение GIF", "GIF_" + currentDateTime, "GIF (*.gif)");
    gif = new QGifImage;
    for (int i = 0; i < gifTime; ++i) {
      QImage scaledImage = gifImage[i].scaled(640, 480);
      gif->addFrame(scaledImage, 100);
    }
    gif->save(fileName);
    ui->save_gif->setEnabled(true);
    timer->stop();
    delete gif;
    gifTime = 0;
  }
}

void MainWindow::on_MainWindow_destroyed() { saveSettings(); }
