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

  timer = new QTimer;
  gifImage = new QImage[50]{};
  connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));
  this->settingFile = QApplication::applicationDirPath() + "/settings.conf";

  default_val();
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
    settings.beginGroup("LineSet");
    if (settings.value("solid").toBool()) {
      ui->f_solid->setChecked(true);
    } else if (settings.value("dashed").toBool()) {
      ui->f_dashed->setChecked(true);
    }
    ui->check_color_face->setPalette(
        QPalette(settings.value("LineColor").value<QColor>()));
    ui->thickness->setValue(settings.value("value").toInt());
    settings.endGroup();

    settings.beginGroup("Verticies");
    if (settings.value("disable").toBool()) {
      ui->v_no->setChecked(true);
    } else if (settings.value("circle").toBool()) {
      ui->v_circle->setChecked(true);
    } else if (settings.value("square").toBool()) {
      ui->v_square->setChecked(true);
    }
    if (settings.value("color").toString().length() > 0) {
      ui->check_color_vert->setPalette(
          QPalette(settings.value("color").value<QColor>()));
    }
    ui->hsbWidth->setValue(settings.value("size").toInt());
    settings.endGroup();

    settings.beginGroup("background");
    if (settings.value("color").toString().length() > 0) {
      ui->check_color_back->setPalette(
          QPalette(settings.value("color").value<QColor>()));
    }
    settings.endGroup();
  }
}

void MainWindow::saveSettings() {
  QSettings settings(settingFile, QSettings::IniFormat);

  settings.beginGroup("LineSet");
  settings.setValue("solid", ui->f_solid->isChecked());
  settings.setValue("dashed", ui->f_dashed->isChecked());
  settings.setValue("LineColor",
                    ui->check_color_face->palette().color(QPalette::Button));
  settings.setValue("value", ui->thickness->value());
  settings.endGroup();

  settings.beginGroup("Verticies");
  settings.setValue("disable", ui->v_no->isChecked());
  settings.setValue("circle", ui->v_circle->isChecked());
  settings.setValue("square", ui->v_square->isChecked());
  settings.setValue("color",
                    ui->check_color_vert->palette().color(QPalette::Button));
  settings.setValue("size", ui->hsbWidth->value());
  settings.endGroup();

  settings.beginGroup("background");
  settings.setValue("color",
                    ui->check_color_back->palette().color(QPalette::Button));
  settings.endGroup();
}

void MainWindow::on_pushButton_clicked() {
  QString str;
  str = QFileDialog::getOpenFileName(this, "Выбрать файл", "../src/objects",
                                     "*.obj");
  std::string expression = str.toStdString();
  char *file = expression.data();

  parseOBJFile(file, &(ui->openGLWidget->probe));

  set_info(str, (*(ui->openGLWidget->probe)).vertexCount,
           (*(ui->openGLWidget->probe)).faceCount);

  ui->openGLWidget->matrix_alt =
      matrix_alteration(ui->rotate_y->value() * COEFF_ROTATE,
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
  saveSettings();
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
