#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNewImage_triggered();

    void on_actionMonoFilter_triggered();

private:
    Ui::MainWindow *ui;

    FlowScene *mScene;
    FlowView *mView;
};

#endif // MAINWINDOW_H
