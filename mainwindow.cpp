#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

void MainWindow::resizeEvent(QResizeEvent *event)
{
ui->x11->resize(event->size().width(),event->size().height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

