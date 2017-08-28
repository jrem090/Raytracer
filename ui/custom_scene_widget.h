#ifndef CUSTOM_SCENE_WIDGET_H
#define CUSTOM_SCENE_WIDGET_H

#include "scene_widget.h"
#include <QWidget>

namespace Ui {
class CustomSceneWidget;
}

class CustomSceneWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomSceneWidget(QWidget *parent = 0);
    ~CustomSceneWidget();

private:
    Ui::CustomSceneWidget *ui;
};

#endif // CUSTOM_SCENE_WIDGET_H
