#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawer = ui->widget;

    connect(ui->action_insert_man, SIGNAL(triggered()), this, SLOT(setStateToInsertMan()));
    connect(ui->action_insert_woman, SIGNAL(triggered()), this, SLOT(setStateToInsertWoman()));
    connect(ui->action_reset_all_data, SIGNAL(triggered()), this, SLOT(resetAllDataForDraw()));
    connect(ui->action_set_priorities_of, SIGNAL(triggered()), this, SLOT(setPrioritiesOfElement()));
    connect(ui->action_generate_random_graph, SIGNAL(triggered()), this, SLOT(generateRandomGraph()));
    connect(ui->action_solve_the_problem, SIGNAL(triggered()), this, SLOT(solverPairingProblem()));


    dialog = new Dialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStateToInsertMan() {
    drawer->setState(drawer->state_insert_man);
}

void MainWindow::setStateToInsertWoman() {
    drawer->setState(drawer->state_insert_woman);
}

void MainWindow::resetAllDataForDraw() {
    drawer->resetAllData();
}

void MainWindow::setPrioritiesOfElement() {
    drawer->setState(drawer->state_set_priorities);
}

void MainWindow::generateRandomGraph() {
    if (dialog->exec() == QDialog::Accepted) {
        drawer->generateRandomGraph(dialog->getSize());
    }
}

void MainWindow::solverPairingProblem() {
    drawer->solver->solvePairingProblem();
}
