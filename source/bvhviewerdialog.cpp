#include "bvhviewerdialog.h"

#include "ui_bvhviewerdialog.h"

BVHViewerDialog::BVHViewerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BVHViewerDialog)
{
    ui->setupUi(this);
    bvher = new BVHViewer();
    bvher->moveToThread(&bvh_thread);
    connect(&bvh_thread, &QThread::finished,
            bvher, &QObject::deleteLater);
    //connect(this, SIGNAL(bvh_command(int,int,bvh_node*,int,float,float,float,float,float,float)),
    //        bvher, SLOT(bvh_trace(int,int,bvh_node*,int,float,float,float,float,float,float)));
    connect(bvher, SIGNAL(bvh_complete()),
            this, SLOT(finish_bvh()));
    connect(bvher, SIGNAL(progress_update(float)),
            this, SLOT(update_progress(float)));
    bvh_thread.start();
}

BVHViewerDialog::~BVHViewerDialog()
{
    bvh_thread.quit();
    delete  bvher;
    delete ui;
}

void BVHViewerDialog::bvh_command(int width, int height, bvh_node* world,
                       int samples,
                       float cam_x, float cam_y, float cam_z,
                       float focal_x, float focal_y, float focal_z)
{
    bvher->bvh_trace(width, height, world, samples, cam_x, cam_y, cam_z, focal_x, focal_y, focal_z);
}

void BVHViewerDialog::finish_bvh()
{
    ui->widget->setStyleSheet("QWidget {background-image: url(./bvhout.ppm) stretch;}");
}

void BVHViewerDialog::update_progress(float percent)
{
    ui->progressBar->setValue(percent);
}
