#ifndef CUSTOM_ITEM_H
#define CUSTOM_ITEM_H

#include <QWidget>

namespace Ui {
class custom_item;
}

class custom_item : public QWidget
{
    Q_OBJECT

public:
    explicit custom_item(QWidget *parent = 0);
    ~custom_item();

private:
    Ui::custom_item *ui;
};

#endif // CUSTOM_ITEM_H
