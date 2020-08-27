#ifndef BVHVIEWERDIALOG_H
#define BVHVIEWERDIALOG_H

#include <QDialog>
#include <QThread>

#include "bvhviewer.h"
#include "vec3.h"
#include "bvh_node.h"

namespace Ui {
class BVHViewerDialog;
}

class BVHViewerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BVHViewerDialog(QWidget *parent = nullptr);
    ~BVHViewerDialog();

public slots:
    //void bvhtrace();
    void finish_bvh();
    void update_progress(float percent);

//signals:
void    bvh_command(int width, int height, bvh_node* world,
                     int samples,
                     float cam_x, float cam_y, float cam_z,
                     float focal_x, float focal_y, float focal_z);
private:
    Ui::BVHViewerDialog *ui;

    BVHViewer *bvher;
    QThread bvh_thread;
};

#endif // BVHVIEWERDIALOG_H
