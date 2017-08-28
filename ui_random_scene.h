/********************************************************************************
** Form generated from reading UI file 'random_scene.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANDOM_SCENE_H
#define UI_RANDOM_SCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_random_scene
{
public:
    QGridLayout *gridLayout;
    QCheckBox *diffuse_check;
    QSpinBox *image_box;
    QSpacerItem *verticalSpacer;
    QSpinBox *checker_box;
    QSpinBox *metal_box;
    QLabel *label_2;
    QLabel *label_4;
    QCheckBox *checker_check;
    QCheckBox *image_check;
    QSpinBox *diffuse_box;
    QLabel *label_5;
    QLabel *label_1;
    QLabel *label_3;
    QCheckBox *glass_check;
    QCheckBox *metal_check;
    QCheckBox *base_check;
    QSpinBox *glass_box;

    void setupUi(QWidget *random_scene)
    {
        if (random_scene->objectName().isEmpty())
            random_scene->setObjectName(QStringLiteral("random_scene"));
        random_scene->resize(400, 300);
        gridLayout = new QGridLayout(random_scene);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        diffuse_check = new QCheckBox(random_scene);
        diffuse_check->setObjectName(QStringLiteral("diffuse_check"));

        gridLayout->addWidget(diffuse_check, 0, 2, 1, 1);

        image_box = new QSpinBox(random_scene);
        image_box->setObjectName(QStringLiteral("image_box"));

        gridLayout->addWidget(image_box, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 1, 1, 1);

        checker_box = new QSpinBox(random_scene);
        checker_box->setObjectName(QStringLiteral("checker_box"));

        gridLayout->addWidget(checker_box, 4, 1, 1, 1);

        metal_box = new QSpinBox(random_scene);
        metal_box->setObjectName(QStringLiteral("metal_box"));

        gridLayout->addWidget(metal_box, 1, 1, 1, 1);

        label_2 = new QLabel(random_scene);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label_4 = new QLabel(random_scene);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        checker_check = new QCheckBox(random_scene);
        checker_check->setObjectName(QStringLiteral("checker_check"));

        gridLayout->addWidget(checker_check, 4, 2, 1, 1);

        image_check = new QCheckBox(random_scene);
        image_check->setObjectName(QStringLiteral("image_check"));

        gridLayout->addWidget(image_check, 3, 2, 1, 1);

        diffuse_box = new QSpinBox(random_scene);
        diffuse_box->setObjectName(QStringLiteral("diffuse_box"));

        gridLayout->addWidget(diffuse_box, 0, 1, 1, 1);

        label_5 = new QLabel(random_scene);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_1 = new QLabel(random_scene);
        label_1->setObjectName(QStringLiteral("label_1"));

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        label_3 = new QLabel(random_scene);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        glass_check = new QCheckBox(random_scene);
        glass_check->setObjectName(QStringLiteral("glass_check"));

        gridLayout->addWidget(glass_check, 2, 2, 1, 1);

        metal_check = new QCheckBox(random_scene);
        metal_check->setObjectName(QStringLiteral("metal_check"));

        gridLayout->addWidget(metal_check, 1, 2, 1, 1);

        base_check = new QCheckBox(random_scene);
        base_check->setObjectName(QStringLiteral("base_check"));

        gridLayout->addWidget(base_check, 6, 1, 1, 1);

        glass_box = new QSpinBox(random_scene);
        glass_box->setObjectName(QStringLiteral("glass_box"));

        gridLayout->addWidget(glass_box, 2, 1, 1, 1);


        retranslateUi(random_scene);

        QMetaObject::connectSlotsByName(random_scene);
    } // setupUi

    void retranslateUi(QWidget *random_scene)
    {
        random_scene->setWindowTitle(QApplication::translate("random_scene", "Form", Q_NULLPTR));
        diffuse_check->setText(QApplication::translate("random_scene", "Motion", Q_NULLPTR));
        label_2->setText(QApplication::translate("random_scene", "Image", Q_NULLPTR));
        label_4->setText(QApplication::translate("random_scene", "Metal", Q_NULLPTR));
        checker_check->setText(QApplication::translate("random_scene", "Motion", Q_NULLPTR));
        image_check->setText(QApplication::translate("random_scene", "Motion", Q_NULLPTR));
        label_5->setText(QApplication::translate("random_scene", "Checker", Q_NULLPTR));
        label_1->setText(QApplication::translate("random_scene", "Diffuse", Q_NULLPTR));
        label_3->setText(QApplication::translate("random_scene", "Glass", Q_NULLPTR));
        glass_check->setText(QApplication::translate("random_scene", "Motion", Q_NULLPTR));
        metal_check->setText(QApplication::translate("random_scene", "Motion", Q_NULLPTR));
        base_check->setText(QApplication::translate("random_scene", "Base Layer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class random_scene: public Ui_random_scene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANDOM_SCENE_H
