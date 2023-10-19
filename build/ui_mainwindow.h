/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <view.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLabel *label;
    View *openGLWidget;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QFrame *frame;
    QPushButton *close;
    QPushButton *fold;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *scale_min;
    QSlider *scale_value;
    QPushButton *scale_max;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_7;
    QRadioButton *v_square;
    QRadioButton *v_no;
    QRadioButton *v_circle;
    QLabel *label_6;
    QPushButton *check_color_vert;
    QScrollBar *horizontalScrollBar;
    QWidget *tab_2;
    QRadioButton *f_solid;
    QRadioButton *f_dashed;
    QLabel *label_8;
    QScrollBar *thickness;
    QLabel *label_15;
    QPushButton *check_color_face;
    QWidget *widget;
    QPushButton *check_color_back;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QSlider *translate_x;
    QSlider *translate_y;
    QSlider *translate_z;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QSlider *rotate_x;
    QSlider *rotate_y;
    QSlider *rotate_z;
    QComboBox *projection;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1130, 866);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(770, 80, 311, 32));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(770, 50, 311, 20));
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);
        openGLWidget = new View(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(20, 20, 700, 700));
        openGLWidget->setMinimumSize(QSize(700, 700));
        openGLWidget->setMaximumSize(QSize(700, 700));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(780, 120, 111, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(880, 170, 101, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(890, 320, 71, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(900, 460, 58, 16));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(760, 350, 21, 16));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(760, 390, 21, 16));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(760, 430, 21, 16));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(760, 200, 21, 16));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(760, 280, 21, 16));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(760, 240, 21, 16));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(1010, 10, 101, 41));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        close = new QPushButton(frame);
        close->setObjectName(QString::fromUtf8("close"));
        close->setGeometry(QRect(60, 10, 31, 32));
        fold = new QPushButton(frame);
        fold->setObjectName(QString::fromUtf8("fold"));
        fold->setGeometry(QRect(10, 10, 31, 32));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(780, 490, 301, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        scale_min = new QPushButton(layoutWidget);
        scale_min->setObjectName(QString::fromUtf8("scale_min"));

        horizontalLayout->addWidget(scale_min);

        scale_value = new QSlider(layoutWidget);
        scale_value->setObjectName(QString::fromUtf8("scale_value"));
        scale_value->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(scale_value);

        scale_max = new QPushButton(layoutWidget);
        scale_max->setObjectName(QString::fromUtf8("scale_max"));

        horizontalLayout->addWidget(scale_max);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(750, 560, 321, 141));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 10, 81, 16));
        v_square = new QRadioButton(tab);
        v_square->setObjectName(QString::fromUtf8("v_square"));
        v_square->setGeometry(QRect(110, 30, 99, 20));
        v_no = new QRadioButton(tab);
        v_no->setObjectName(QString::fromUtf8("v_no"));
        v_no->setGeometry(QRect(110, 50, 99, 20));
        v_circle = new QRadioButton(tab);
        v_circle->setObjectName(QString::fromUtf8("v_circle"));
        v_circle->setGeometry(QRect(110, 10, 99, 20));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 80, 58, 16));
        check_color_vert = new QPushButton(tab);
        check_color_vert->setObjectName(QString::fromUtf8("check_color_vert"));
        check_color_vert->setGeometry(QRect(230, 10, 51, 51));
        horizontalScrollBar = new QScrollBar(tab);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(100, 80, 160, 21));
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        f_solid = new QRadioButton(tab_2);
        f_solid->setObjectName(QString::fromUtf8("f_solid"));
        f_solid->setGeometry(QRect(110, 10, 99, 20));
        f_dashed = new QRadioButton(tab_2);
        f_dashed->setObjectName(QString::fromUtf8("f_dashed"));
        f_dashed->setGeometry(QRect(110, 30, 99, 20));
        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 10, 71, 16));
        thickness = new QScrollBar(tab_2);
        thickness->setObjectName(QString::fromUtf8("thickness"));
        thickness->setGeometry(QRect(120, 70, 160, 16));
        thickness->setOrientation(Qt::Horizontal);
        label_15 = new QLabel(tab_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(20, 70, 71, 16));
        check_color_face = new QPushButton(tab_2);
        check_color_face->setObjectName(QString::fromUtf8("check_color_face"));
        check_color_face->setGeometry(QRect(240, 10, 51, 51));
        tabWidget->addTab(tab_2, QString());
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        check_color_back = new QPushButton(widget);
        check_color_back->setObjectName(QString::fromUtf8("check_color_back"));
        check_color_back->setGeometry(QRect(130, 20, 51, 51));
        tabWidget->addTab(widget, QString());
        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(790, 200, 291, 101));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        translate_x = new QSlider(layoutWidget1);
        translate_x->setObjectName(QString::fromUtf8("translate_x"));
        translate_x->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(translate_x);

        translate_y = new QSlider(layoutWidget1);
        translate_y->setObjectName(QString::fromUtf8("translate_y"));
        translate_y->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(translate_y);

        translate_z = new QSlider(layoutWidget1);
        translate_z->setObjectName(QString::fromUtf8("translate_z"));
        translate_z->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(translate_z);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(790, 350, 291, 101));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        rotate_x = new QSlider(layoutWidget2);
        rotate_x->setObjectName(QString::fromUtf8("rotate_x"));
        rotate_x->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(rotate_x);

        rotate_y = new QSlider(layoutWidget2);
        rotate_y->setObjectName(QString::fromUtf8("rotate_y"));
        rotate_y->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(rotate_y);

        rotate_z = new QSlider(layoutWidget2);
        rotate_z->setObjectName(QString::fromUtf8("rotate_z"));
        rotate_z->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(rotate_z);

        projection = new QComboBox(centralwidget);
        projection->addItem(QString());
        projection->addItem(QString());
        projection->setObjectName(QString::fromUtf8("projection"));
        projection->setGeometry(QRect(930, 120, 103, 32));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1130, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\277\321\203\321\202\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\265\320\272\321\206\320\270\321\217", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\260\321\211\320\265\320\275\320\270\320\265", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        close->setText(QCoreApplication::translate("MainWindow", "\320\245", nullptr));
        fold->setText(QCoreApplication::translate("MainWindow", "_", nullptr));
        scale_min->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        scale_max->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\262\320\265\321\200\321\210\320\270\320\275", nullptr));
        v_square->setText(QCoreApplication::translate("MainWindow", "\320\232\320\262\320\260\320\264\321\200\320\260\321\202\321\213", nullptr));
        v_no->setText(QCoreApplication::translate("MainWindow", "\320\275\320\265\321\202", nullptr));
        v_circle->setText(QCoreApplication::translate("MainWindow", "\320\232\321\200\321\203\320\263\320\270", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200", nullptr));
        check_color_vert->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\321\210\320\270\320\275\321\213", nullptr));
        f_solid->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\273\320\276\321\210\320\275\320\260\321\217", nullptr));
        f_dashed->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\320\275\320\272\321\202\320\270\321\200\320\275\320\260\321\217", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\273\320\270\320\275\320\270\320\270", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\320\242\320\276\320\273\321\211\320\270\320\275\320\260", nullptr));
        check_color_face->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\320\233\320\270\320\275\320\270\320\270\320\270", nullptr));
        check_color_back->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(widget), QCoreApplication::translate("MainWindow", "\320\244\320\276\320\275", nullptr));
        projection->setItemText(0, QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\273\320\273\320\265\320\273\321\214\320\275\320\260\321\217", nullptr));
        projection->setItemText(1, QCoreApplication::translate("MainWindow", " \320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\260\321\217", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
