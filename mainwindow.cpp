#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawer = ui->widget;

    connect(ui->action_insert_man, SIGNAL(triggered()), this, SLOT(insertMan()));
    connect(ui->action_insert_woman, SIGNAL(triggered()), this, SLOT(insertWoman()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertMan() {
    drawer->operationState =drawer->insert_man;
}

void MainWindow::insertWoman() {
    drawer->operationState =drawer->insert_woman;
}
