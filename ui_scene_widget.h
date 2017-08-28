/********************************************************************************
** Form generated from reading UI file 'scene_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCENE_WIDGET_H
#define UI_SCENE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_scene_widget
{
public:

    void setupUi(QWidget *scene_widget)
    {
        if (scene_widget->objectName().isEmpty())
            scene_widget->setObjectName(QStringLiteral("scene_widget"));
        scene_widget->resize(400, 300);

        retranslateUi(scene_widget);

        QMetaObject::connectSlotsByName(scene_widget);
    } // setupUi

    void retranslateUi(QWidget *scene_widget)
    {
        scene_widget->setWindowTitle(QApplication::translate("scene_widget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class scene_widget: public Ui_scene_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENE_WIDGET_H
