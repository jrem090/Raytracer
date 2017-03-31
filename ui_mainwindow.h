/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QWidget *widget;
    QSlider *num_samples;
    QSlider *num_rays;
    QDoubleSpinBox *camera_x;
    QDoubleSpinBox *camera_y;
    QDoubleSpinBox *camera_z;
    QDoubleSpinBox *point_x;
    QDoubleSpinBox *point_y;
    QDoubleSpinBox *point_z;
    QSpinBox *num_diffuse;
    QSpinBox *num_metal;
    QSpinBox *num_glass;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(454, 495);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 320, 75, 23));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 10, 400, 300));
        num_samples = new QSlider(centralWidget);
        num_samples->setObjectName(QStringLiteral("num_samples"));
        num_samples->setGeometry(QRect(140, 320, 111, 22));
        num_samples->setMinimum(1);
        num_samples->setMaximum(100);
        num_samples->setValue(10);
        num_samples->setOrientation(Qt::Horizontal);
        num_rays = new QSlider(centralWidget);
        num_rays->setObjectName(QStringLiteral("num_rays"));
        num_rays->setGeometry(QRect(310, 320, 101, 22));
        num_rays->setMinimum(1);
        num_rays->setMaximum(100);
        num_rays->setValue(10);
        num_rays->setOrientation(Qt::Horizontal);
        num_rays->setTickPosition(QSlider::NoTicks);
        camera_x = new QDoubleSpinBox(centralWidget);
        camera_x->setObjectName(QStringLiteral("camera_x"));
        camera_x->setGeometry(QRect(140, 350, 62, 22));
        camera_x->setMinimum(-10);
        camera_x->setMaximum(10);
        camera_x->setValue(-2);
        camera_y = new QDoubleSpinBox(centralWidget);
        camera_y->setObjectName(QStringLiteral("camera_y"));
        camera_y->setGeometry(QRect(240, 350, 62, 22));
        camera_y->setMinimum(-10);
        camera_y->setSingleStep(10);
        camera_y->setValue(2);
        camera_z = new QDoubleSpinBox(centralWidget);
        camera_z->setObjectName(QStringLiteral("camera_z"));
        camera_z->setGeometry(QRect(340, 350, 62, 22));
        camera_z->setMinimum(-10);
        camera_z->setMaximum(10);
        camera_z->setValue(1);
        point_x = new QDoubleSpinBox(centralWidget);
        point_x->setObjectName(QStringLiteral("point_x"));
        point_x->setGeometry(QRect(140, 380, 62, 22));
        point_x->setMinimum(-10);
        point_x->setMaximum(10);
        point_y = new QDoubleSpinBox(centralWidget);
        point_y->setObjectName(QStringLiteral("point_y"));
        point_y->setGeometry(QRect(240, 380, 62, 22));
        point_y->setMinimum(-10);
        point_y->setMaximum(10);
        point_z = new QDoubleSpinBox(centralWidget);
        point_z->setObjectName(QStringLiteral("point_z"));
        point_z->setGeometry(QRect(340, 380, 62, 22));
        point_z->setMinimum(-10);
        point_z->setMaximum(10);
        point_z->setValue(-1);
        num_diffuse = new QSpinBox(centralWidget);
        num_diffuse->setObjectName(QStringLiteral("num_diffuse"));
        num_diffuse->setGeometry(QRect(160, 410, 42, 22));
        num_metal = new QSpinBox(centralWidget);
        num_metal->setObjectName(QStringLiteral("num_metal"));
        num_metal->setGeometry(QRect(260, 410, 42, 22));
        num_glass = new QSpinBox(centralWidget);
        num_glass->setObjectName(QStringLiteral("num_glass"));
        num_glass->setGeometry(QRect(360, 410, 42, 22));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 350, 91, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 350, 16, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(120, 380, 16, 16));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(220, 350, 16, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(220, 380, 16, 16));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(320, 350, 21, 16));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(320, 380, 21, 16));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 380, 91, 16));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 410, 81, 16));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(110, 410, 41, 21));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(220, 410, 41, 21));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(320, 410, 41, 21));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(90, 320, 61, 20));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(260, 320, 61, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 454, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton->setText(QApplication::translate("MainWindow", "TRACE!", 0));
        label->setText(QApplication::translate("MainWindow", "Camera Location", 0));
        label_2->setText(QApplication::translate("MainWindow", "X:", 0));
        label_3->setText(QApplication::translate("MainWindow", "X:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Y:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Y:", 0));
        label_6->setText(QApplication::translate("MainWindow", "Z:", 0));
        label_7->setText(QApplication::translate("MainWindow", "Z:", 0));
        label_8->setText(QApplication::translate("MainWindow", "Camera Point At", 0));
        label_9->setText(QApplication::translate("MainWindow", "Number of balls", 0));
        label_10->setText(QApplication::translate("MainWindow", "Diffuse", 0));
        label_11->setText(QApplication::translate("MainWindow", "Metal", 0));
        label_12->setText(QApplication::translate("MainWindow", "Glass", 0));
        label_13->setText(QApplication::translate("MainWindow", "# samples", 0));
        label_14->setText(QApplication::translate("MainWindow", "# rays", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
