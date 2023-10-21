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
  ui->label->setText(str);

//  OBJData *probe = {};

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
  ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
                                                    ui->rotate_y->value() * COEFF_ROTATE,
                                                    ui->rotate_z->value() * COEFF_ROTATE,
                                                    (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                    (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                    (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                    ui->scale_value->value() * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
  ui->openGLWidget->update();
}

void MainWindow::default_val() {
//  ui->translate_x->setValue(0);
//  ui->translate_y->setValue(0);
//  ui->translate_z->setValue(0);
//  ui->rotate_x->setValue(0);
//  ui->rotate_y->setValue(0);
//  ui->rotate_z->setValue(0);
//  ui->scale_value->setValue(50);
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

//void MainWindow::on_scale_valueChanged(int value) {
//  //    ui->openGLWidget->size = value;
//  //    ui->openGLWidget->update();
//}

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
//    QColor color = QColorDialog::getColor(Qt::white, this);
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
//    ui->openGLWidget->matrix_alt = matrix_alteration (value*COEF_ROTATE,
//                                                      (ui->rotate_y->value())*COEF_ROTATE,
//                                                      (ui->rotate_z->value())*COEF_ROTATE,
//                                                      (ui->translate_x->value())*COEF_SHIFT,
//                                                      (ui->translate_y->value())*COEF_SHIFT,
//                                                       (ui->translate_z->value())*COEF_SHIFT,
//                                                        (ui->scale_value->value())*COEF_SHIFT);

//  ui->openGLWidget->my_paint();
    ui->openGLWidget->matrix_alt = matrix_alteration (value * COEFF_ROTATE,
                                                      ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_z->value() * COEFF_ROTATE,
                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                      ui->scale_value->value() * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_rotate_y_valueChanged(int value) {
//  return_y (&ui->openGLWidget->probe, (ui->rotate_y->value()));
//  ui->openGLWidget->rotate_y = value;
//  ui->openGLWidget->update();
    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
                                                      value * COEFF_ROTATE,
                                                      ui->rotate_z->value() * COEFF_ROTATE,
                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                      ui->scale_value->value() * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_rotate_z_valueChanged(int value) {
//  return_z(&ui->openGLWidget->probe, (value - ui->openGLWidget->rotate_z));
//  ui->openGLWidget->rotate_z = value;
//  ui->openGLWidget->update();
    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_y->value() * COEFF_ROTATE,
                                                      value * COEFF_ROTATE,
                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                      ui->scale_value->value() * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_translate_x_valueChanged(int value) {
//  move_X(&ui->openGLWidget->probe, (value - ui->openGLWidget->translate_x) *
//                                       ui->openGLWidget->normalize_coef / 100);
//  ui->openGLWidget->translate_x = value;
//  ui->openGLWidget->update();
    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_z->value() * COEFF_ROTATE,
                                                      (value - 50) * COEFF_SHIFT,
                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                      ui->scale_value->value() * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_translate_y_valueChanged(int value) {
//  move_Y(&ui->openGLWidget->probe, (value - ui->openGLWidget->translate_y) *
//                                       ui->openGLWidget->normalize_coef / 100);
//  ui->openGLWidget->translate_y = value;
//  ui->openGLWidget->update();
    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_z->value() * COEFF_ROTATE,
                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                      (value - 50) * COEFF_SHIFT,
                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                      ui->scale_value->value() * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_translate_z_valueChanged(int value) {
//  move_Z(&ui->openGLWidget->probe, (value - ui->openGLWidget->translate_z) *
//                                       ui->openGLWidget->normalize_coef / 100);
//  ui->openGLWidget->translate_z = value;
//  ui->openGLWidget->update();
    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_z->value() * COEFF_ROTATE,
                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                      (value - 50) * COEFF_SHIFT,
                                                      ui->scale_value->value() * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_hsbWidth_valueChanged(int value)
{
    ui->openGLWidget->vertices_size = ui->hsbWidth->value() / 2;
    ui->openGLWidget->update();
}

void MainWindow::on_scale_value_valueChanged(int value)
{
    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_y->value() * COEFF_ROTATE,
                                                      ui->rotate_z->value() * COEFF_ROTATE,
                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
                                                      value * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
//    printf("matrix:\n %f %f %f %f\n %f %f %f %f\n %f %f %f %f\n %f  %f %f %f\n", ui->openGLWidget->matrix_alt.matrix[0][0], ui->openGLWidget->matrix_alt.matrix[0][1], ui->openGLWidget->matrix_alt.matrix[0][2], ui->openGLWidget->matrix_alt.matrix[0][3],
//            ui->openGLWidget->matrix_alt.matrix[1][0], ui->openGLWidget->matrix_alt.matrix[1][1], ui->openGLWidget->matrix_alt.matrix[1][2], ui->openGLWidget->matrix_alt.matrix[1][3],
//            ui->openGLWidget->matrix_alt.matrix[2][0], ui->openGLWidget->matrix_alt.matrix[2][1], ui->openGLWidget->matrix_alt.matrix[2][2], ui->openGLWidget->matrix_alt.matrix[2][3],
//            ui->openGLWidget->matrix_alt.matrix[3][0], ui->openGLWidget->matrix_alt.matrix[3][1], ui->openGLWidget->matrix_alt.matrix[3][2], ui->openGLWidget->matrix_alt.matrix[3][3]);
    ui->openGLWidget->update();
}

