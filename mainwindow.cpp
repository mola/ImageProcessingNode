#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <nodes/DataModelRegistry>

#include "model/ImageLoaderModel.hpp"
#include "model/ImageShowModel.hpp"
#include "model/monofilter.h"
#include "model/thresholdfilter.h"
#include "model/histogram.h"
#include "model/spatialfilter.h"
#include "model/sobelfilter.h"
#include "model/scaler.h"
#include "model/erosionfilter.h"
#include "model/delatefilter.h"
#include "model/segmentation.h"
#include "model/boundryextraction.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    DataModelRegistry::registerModel<ImageLoaderModel>();
    DataModelRegistry::registerModel<ImageShowModel>();

    DataModelRegistry::registerModel<MonoFilter>();

    DataModelRegistry::registerModel<ThresholdFilter>();
    DataModelRegistry::registerModel<Histogram>();
    DataModelRegistry::registerModel<SpatialFilter>();
    DataModelRegistry::registerModel<SobelFilter>();
    DataModelRegistry::registerModel<Scaler>();
    DataModelRegistry::registerModel<ErosionFilter>();
    DataModelRegistry::registerModel<DilationFilter>();
    DataModelRegistry::registerModel<Segmentation>();
    DataModelRegistry::registerModel<BoundryExtraction>();

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
