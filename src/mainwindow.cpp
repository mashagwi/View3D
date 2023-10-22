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
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  QString str;
  str = QFileDialog::getOpenFileName(this, "Выбрать файл",
                                     "../../../../src/objects", "*.obj");
  std::string expression = str.toStdString();
  char *file = expression.data();

  parseOBJFile(file, &(ui->openGLWidget->probe));
  for (int i = 0; i < (*(ui->openGLWidget->probe)).vertexCount; i++)
    printf("v: %d: %f %f %f\n", i, (*(ui->openGLWidget->probe)).vertices[i * 3],
           (*(ui->openGLWidget->probe)).vertices[i * 3 + 1], (*(ui->openGLWidget->probe)).vertices[i * 3 + 2]);
  for (int i = 0; i < (*(ui->openGLWidget->probe)).faceCount; i++) {
    printf("f: %d:  count_number_vertex: %d ", i,
           (*(ui->openGLWidget->probe)).faces[i].count_number_vertex);
    for (int j = 0; j < (*(ui->openGLWidget->probe)).faces[i].count_number_vertex; j++)
      printf(" %d", (*(ui->openGLWidget->probe)).faces[i].number_vertex[j]);
    printf("\n");

  }
  set_info(str, (*(ui->openGLWidget->probe)).vertexCount, (*(ui->openGLWidget->probe)).faceCount);

  ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
                                                    ui->rotate_y->value() * COEFF_ROTATE,
                                                    ui->rotate_z->value() * COEFF_ROTATE,
                                                    (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                    (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                    (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                    ui->scale_value->value() * COEFF_PART * COEFF_SCALE / 50.0 / ui->openGLWidget->probe->maxVertexValue);
  ui->openGLWidget->update();
}

void MainWindow::set_info(QString filename, int vertex, int face) {
    QStringList pieces = filename.split( "/" );

    ui->info->setText(
        "Название файла:\n" + pieces[pieces.length() - 1] +
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

void MainWindow::on_scale_min_clicked()
{
    ui->scale_value->setValue(ui->scale_value->value() - 10);
}

void MainWindow::on_scale_max_clicked()
{
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

void MainWindow::on_check_color_vert_clicked()
{
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
  ui->openGLWidget->face_thickness = value / 10;
  ui->openGLWidget->update();
}

void MainWindow::on_projection_currentIndexChanged(int index)
{
    if(index == 0) {
        ui->openGLWidget->project_type = PARALLEL;
    } else if (index == 1) {
         ui->openGLWidget->project_type = CENTRAL;
    }
    ui->openGLWidget->update();
}

void MainWindow::on_rotate_x_valueChanged(int value) {
    ui->openGLWidget->matrix_alt = matrix_alteration (value * COEFF_ROTATE,
                                                      ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_z->value() * COEFF_ROTATE,
                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                      ui->scale_value->value() * COEFF_PART * COEFF_SCALE / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_rotate_y_valueChanged(int value) {
    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_x->value() * COEFF_ROTATE,
                                                      value * COEFF_ROTATE,
                                                      ui->rotate_z->value() * COEFF_ROTATE,
                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                      ui->scale_value->value() * COEFF_PART * COEFF_SCALE / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_rotate_z_valueChanged(int value) {
    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_y->value() * COEFF_ROTATE,
                                                      value * COEFF_ROTATE,
                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                      ui->scale_value->value() * COEFF_PART * COEFF_SCALE / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_translate_x_valueChanged(int value) {
    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_z->value() * COEFF_ROTATE,
                                                      (value - 50) * COEFF_SHIFT,
                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                      ui->scale_value->value() * COEFF_PART * COEFF_SCALE / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_translate_y_valueChanged(int value) {
    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_z->value() * COEFF_ROTATE,
                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                      (value - 50) * COEFF_SHIFT,
                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                      ui->scale_value->value() * COEFF_PART * COEFF_SCALE / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_translate_z_valueChanged(int value) {
    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_z->value() * COEFF_ROTATE,
                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                      (value - 50) * COEFF_SHIFT,
                                                      ui->scale_value->value() * COEFF_PART * COEFF_SCALE / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_hsbWidth_valueChanged(int value)
{
    ui->openGLWidget->vertices_size = value / 2;
    ui->openGLWidget->update();
}

void MainWindow::on_scale_value_valueChanged(int value)
{
    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_x->value() * COEFF_ROTATE,
                                                      ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_z->value() * COEFF_ROTATE,
                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                      value * COEFF_PART * COEFF_SCALE / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

