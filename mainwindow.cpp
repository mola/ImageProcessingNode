#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <nodes/DataModelRegistry>

#include "model/ImageLoaderModel.hpp"
#include "model/ImageShowModel.hpp"
#include "model/monofilter.h"
#include "model/thresholdfilter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    DataModelRegistry::registerModel<ImageLoaderModel>();
    DataModelRegistry::registerModel<ImageShowModel>();

    DataModelRegistry::registerModel<MonoFilter>();

    DataModelRegistry::registerModel<ThresholdFilter>();

    mScene = new FlowScene();
    mView = new FlowView(mScene);

    setCentralWidget( mView );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNewImage_triggered()
{


}

void MainWindow::on_actionMonoFilter_triggered()
{


}
