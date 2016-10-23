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
    connect(ui->action_reset_all_data, SIGNAL(triggered()), this, SLOT(resetAllData()));
    connect(ui->action_set_priorities_of, SIGNAL(triggered()), this, SLOT(setPrioritiesOf()));
    //connect(ui->action_set_max_prio_length, SIGNAL(triggered()), this, SLOT(setPrioritiesOf()));
    connect(ui->action_generate_random_graph, SIGNAL(triggered()), this, SLOT(generateRandomGraph()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertMan() {
    drawer->operationState = drawer->insert_man;
}

void MainWindow::insertWoman() {
    drawer->operationState = drawer->insert_woman;
}

void MainWindow::resetAllData() {
    drawer->resetAllData();
}

void MainWindow::setPrioritiesOf() {
    drawer->operationState = drawer->set_priorities;
    drawer->graphStructure.initNeighboursVector();
}

void MainWindow::generateRandomGraph() {
    if (dialog->exec() == QDialog::Accepted) {
        drawer->CreateARandomGraph(dialog->getSize());
    }
}
