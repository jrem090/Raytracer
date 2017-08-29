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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_custom_scene_widget
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QPushButton *item_button;

    void setupUi(QWidget *custom_scene_widget)
    {
        if (custom_scene_widget->objectName().isEmpty())
            custom_scene_widget->setObjectName(QStringLiteral("custom_scene_widget"));
        custom_scene_widget->resize(400, 300);
        verticalLayout = new QVBoxLayout(custom_scene_widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        scrollArea = new QScrollArea(custom_scene_widget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 380, 251));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        item_button = new QPushButton(custom_scene_widget);
        item_button->setObjectName(QStringLiteral("item_button"));

        verticalLayout->addWidget(item_button);


        retranslateUi(custom_scene_widget);

        QMetaObject::connectSlotsByName(custom_scene_widget);
    } // setupUi

    void retranslateUi(QWidget *custom_scene_widget)
    {
        custom_scene_widget->setWindowTitle(QApplication::translate("custom_scene_widget", "Form", Q_NULLPTR));
        item_button->setText(QApplication::translate("custom_scene_widget", "New Item", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class custom_scene_widget: public Ui_custom_scene_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOM_SCENE_WIDGET_H
