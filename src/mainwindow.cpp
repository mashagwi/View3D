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
  setWindowTitle("3DViewer_v1.0");

  timer = new QTimer;
  gifImage = new QImage[50]{};
  connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));

  sliderSetup();
  default_val();
  connectSetup();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::sliderSetup() {
  // Translate
  ui->translate_x->setRange(0, 100);
  ui->translate_x->setSingleStep(1);

  ui->translate_y->setRange(0, 100);
  ui->translate_y->setSingleStep(1);

  ui->translate_z->setRange(0, 100);
  ui->translate_z->setSingleStep(1);
  // Rotate
  ui->rotate_x->setRange(0, 360);
  ui->rotate_x->setSingleStep(8);
  ui->rotate_x->setPageStep(5 * 8);

  ui->rotate_y->setRange(0, 360);
  ui->rotate_y->setSingleStep(8);
  ui->rotate_y->setPageStep(5 * 8);

  ui->rotate_z->setRange(0, 360);
  ui->rotate_z->setSingleStep(8);
  ui->rotate_z->setPageStep(5 * 8);
  // Scale
  ui->scale_value->setRange(1, 100);
  ui->scale_value->setSingleStep(1);
  // Thickness
  ui->thickness->setRange(1, 100);
  ui->thickness->setSingleStep(1);
  // HorizontalScrollBar
  ui->hsbWidth->setRange(1, 100);
  ui->hsbWidth->setSingleStep(1);

  ui->v_circle->setChecked(true);
  ui->f_solid->setChecked(true);
}

void MainWindow::default_val() {
  ui->translate_x->setValue(50);
  ui->translate_y->setValue(50);
  ui->translate_z->setValue(50);
  ui->translate_lcd_x->setText(QString::number(0));
  ui->translate_lcd_y->setText(QString::number(0));
  ui->translate_lcd_z->setText(QString::number(0));

  ui->rotate_x->setValue(180);
  ui->rotate_y->setValue(180);
  ui->rotate_z->setValue(180);
  ui->roteta_lcd_x->setText(QString::number(0));
  ui->roteta_lcd_y->setText(QString::number(0));
  ui->roteta_lcd_z->setText(QString::number(0));

  ui->scale_value->setValue(50);
  ui->hsbWidth->setValue(1);
  ui->scale_value->setValue(50);

  ui->v_circle->setChecked(true);
  ui->f_solid->setChecked(true);
  ui->tabWidget->setCurrentIndex(0);
  ui->check_color_vert->setStyleSheet("background-color: yellow;");
  ui->check_color_face->setStyleSheet("background-color: black;");
  ui->check_color_back->setStyleSheet("background-color: green;");
  ui->openGLWidget->update();
}

void MainWindow::connectSetup() {
  connect(ui->rotate_x, SIGNAL(valueChanged(int)), this, SLOT(on_rotate_x_valueChanged(int value)));
  connect(ui->rotate_y, SIGNAL(valueChanged(int)), this, SLOT(on_rotate_y_valueChanged(int value)));
  connect(ui->rotate_z, SIGNAL(valueChanged(int)), this, SLOT(on_rotate_z_valueChanged(int value)));
  connect(ui->translate_x, SIGNAL(valueChanged(int)), this, SLOT(on_translate_x_valueChanged(int value)));
  connect(ui->translate_y, SIGNAL(valueChanged(int)), this, SLOT(on_translate_y_valueChanged(int value)));
  connect(ui->translate_z, SIGNAL(valueChanged(int)), this, SLOT(on_translate_z_valueChanged(int value)));
}

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

void MainWindow::on_scale_min_clicked() {

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
    ui->roteta_lcd_x->setText(QString::number(value - 180)); // отобразает изминение показаний

//    ui->openGLWidget->matrix_alt = matrix_alteration (value*COEF_ROTATE,
//                                                      (ui->rotate_y->value())*COEF_ROTATE,
//                                                      (ui->rotate_z->value())*COEF_ROTATE,
//                                                      (ui->translate_x->value())*COEF_SHIFT,
//                                                      (ui->translate_y->value())*COEF_SHIFT,
//                                                       (ui->translate_z->value())*COEF_SHIFT,
//                                                        (ui->scale_value->value())*COEF_SHIFT);

//  ui->openGLWidget->my_paint();




//    ui->openGLWidget->matrix_alt = matrix_alteration (value * COEFF_ROTATE,
//                                                      ui->rotate_y->value() * COEFF_ROTATE,
//                                                      ui->rotate_z->value() * COEFF_ROTATE,
//                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
//                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
//                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
//                                                      ui->scale_value->value() * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_rotate_y_valueChanged(int value) {
    ui->roteta_lcd_y->setText(QString::number(value - 180)); // отобразает изминение показаний

//  return_y (&ui->openGLWidget->probe, (ui->rotate_y->value()));
//  ui->openGLWidget->rotate_y = value;
//  ui->openGLWidget->update();



//    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
//                                                      value * COEFF_ROTATE,
//                                                      ui->rotate_z->value() * COEFF_ROTATE,
//                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
//                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
//                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
//                                                      ui->scale_value->value() * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_rotate_z_valueChanged(int value) {
    ui->roteta_lcd_z->setText(QString::number(value - 180)); // отобразает изминение показаний


//  return_z(&ui->openGLWidget->probe, (value - ui->openGLWidget->rotate_z));
//  ui->openGLWidget->rotate_z = value;
//  ui->openGLWidget->update();




//    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
//                                                      ui->rotate_y->value() * COEFF_ROTATE,
//                                                      value * COEFF_ROTATE,
//                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
//                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
//                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
//                                                      ui->scale_value->value() * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_translate_x_valueChanged(int value) {
    ui->translate_lcd_x->setText(QString::number(value - 50)); // отобразает изминение показаний


//  move_X(&ui->openGLWidget->probe, (value - ui->openGLWidget->translate_x) *
//                                       ui->openGLWidget->normalize_coef / 100);
//  ui->openGLWidget->translate_x = value;
//  ui->openGLWidget->update();


//    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
//                                                      ui->rotate_y->value() * COEFF_ROTATE,
//                                                      ui->rotate_z->value() * COEFF_ROTATE,
//                                                      (value - 50) * COEFF_SHIFT,
//                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
//                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
//                                                      ui->scale_value->value() * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_translate_y_valueChanged(int value) {
    ui->translate_lcd_y->setText(QString::number(value - 50)); // отобразает изминение показаний



//  move_Y(&ui->openGLWidget->probe, (value - ui->openGLWidget->translate_y) *
//                                       ui->openGLWidget->normalize_coef / 100);
//  ui->openGLWidget->translate_y = value;
//  ui->openGLWidget->update();



//    ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
//                                                      ui->rotate_y->value() * COEFF_ROTATE,
//                                                      ui->rotate_z->value() * COEFF_ROTATE,
//                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
//                                                      (value - 50) * COEFF_SHIFT,
//                                                      (ui->translate_z->value() - 50) * COEFF_SHIFT,
//                                                      ui->scale_value->value() * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
    ui->openGLWidget->update();
}

void MainWindow::on_translate_z_valueChanged(int value) {
        ui->translate_lcd_z->setText(QString::number(value - 50)); // отобразает изминение показаний


//  move_Z(&ui->openGLWidget->probe, (value - ui->openGLWidget->translate_z) *
//                                       ui->openGLWidget->normalize_coef / 100);
//  ui->openGLWidget->translate_z = value;
//  ui->openGLWidget->update();



//        ui->openGLWidget->matrix_alt = matrix_alteration (ui->rotate_y->value() * COEFF_ROTATE,
//                                                      ui->rotate_y->value() * COEFF_ROTATE,
//                                                      ui->rotate_z->value() * COEFF_ROTATE,
//                                                      (ui->translate_x->value() - 50) * COEFF_SHIFT,
//                                                      (ui->translate_y->value() - 50) * COEFF_SHIFT,
//                                                      (value - 50) * COEFF_SHIFT,
//                                                      ui->scale_value->value() * COEFF_PART / 50.0 / ui->openGLWidget->probe->maxVertexValue);
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


void MainWindow::on_save_screenshot_clicked() {
    QString format, fileName;
    int type = ui->format->currentIndex();
    if( type == 0) {
         format = "bmp";
    } else {
         format = "jpeg";
    }
    QString initialPath =
    QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if (initialPath.isEmpty()) initialPath = QDir::currentPath();
    initialPath += tr(".") + format;
    QFileDialog fileDialog(this, tr("Сохранить как..."), initialPath);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setDirectory(initialPath);
    fileDialog.selectMimeTypeFilter("image/" + format);
    fileDialog.setDefaultSuffix(format);
    if (fileDialog.exec() != QDialog::Accepted) return;
    fileName = fileDialog.selectedFiles().first();
    QPixmap originalPixmap = QWidget::grab(ui->widget->frameGeometry());
    originalPixmap.save(fileName);
}


void MainWindow::on_reset_clicked() {
    default_val();
    ui->openGLWidget->update();
}


void MainWindow::on_save_gif_clicked() {
    ui->save_gif->setEnabled(false);
    timer->start(100);
}

void MainWindow::slotTimer() {
    if (gifTime < 50) {
        gifImage[gifTime] = ui->openGLWidget->grab().toImage();
         ++gifTime;
    } else {
        QDateTime dateTime = dateTime.currentDateTime();
        QString currentDateTime = dateTime.toString("dd.MM.yy_HH.mm.ss");
        QString fileName = QFileDialog::getSaveFileName(
            this, "Save GIF", "GIF_" + currentDateTime, "GIF (*.gif)");

        gif = new QGifImage;
        for (int i = 0; i < gifTime; ++i) {
            gif->addFrame(gifImage[i], 0);
        }
        gif->save(fileName);
        ui->save_gif->setEnabled(true);
        timer->stop();
        delete gif;
        gifTime = 0;
    }
}
