/********************************************************************************
** Form generated from reading UI file 'custom_scene_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOM_SCENE_WIDGET_H
#define UI_CUSTOM_SCENE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomSceneWidget
{
public:

    void setupUi(QWidget *CustomSceneWidget)
    {
        if (CustomSceneWidget->objectName().isEmpty())
            CustomSceneWidget->setObjectName(QStringLiteral("CustomSceneWidget"));
        CustomSceneWidget->resize(400, 300);

        retranslateUi(CustomSceneWidget);

        QMetaObject::connectSlotsByName(CustomSceneWidget);
    } // setupUi

    void retranslateUi(QWidget *CustomSceneWidget)
    {
        CustomSceneWidget->setWindowTitle(QApplication::translate("CustomSceneWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CustomSceneWidget: public Ui_CustomSceneWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOM_SCENE_WIDGET_H
