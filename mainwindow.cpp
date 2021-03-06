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
    connect(ui->action_solve_the_problem, SIGNAL(triggered()), this, SLOT(solverPairingProblem()));
    connect(ui->action_insert_men, SIGNAL(triggered()), this, SLOT(insertXMan()));
    connect(ui->action_insert_women, SIGNAL(triggered()), this, SLOT(insertXWoman()));
    connect(ui->action_generate_priorities, SIGNAL(triggered()), this, SLOT(generatePriorities()));
    connect(ui->action_solve_the_problem_step_by_step, SIGNAL(triggered()), this, SLOT(solverPairingProblemStepByStep()));
    connect(ui->actionCheck_if_problem_contains_pair, SIGNAL(triggered()), this, SLOT(drawBlockingEdges()));
    connect(ui->actionMake_preferencelist_reduction_enabled, SIGNAL(triggered()), this, SLOT(makePreferenceListReductionEnabled()));
    connect(ui->actionMake_preferencelist_reduction_disabled, SIGNAL(triggered()), this, SLOT(makePreferenceListReductionDisabled()));



    dialog = new Dialog(this);
    prioDialog = new PrioritiesDialog(this);
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

void MainWindow::solverPairingProblem() {
    drawer->solveTheProblem();
}

void MainWindow::insertXMan() {
    if (dialog->exec() == QDialog::Accepted) {
        drawer->graphStructure.insertXMan(dialog->getSize(), drawer->width(), drawer->height(), drawer->circleRadius);
    }
}

void MainWindow::insertXWoman() {
    if (dialog->exec() == QDialog::Accepted) {
        drawer->graphStructure.insertXWoman(dialog->getSize(), drawer->width(), drawer->height(), drawer->circleRadius);
    }
}

void MainWindow::generatePriorities() {
    if (prioDialog->exec() == QDialog::Accepted) {
        drawer->graphStructure.generatePrioritiesForElements(prioDialog->isPriolistLengthRandom(), prioDialog->getSize());
    }
}

void MainWindow::solverPairingProblemStepByStep() {
    drawer->solveTheProblemStepByStep();
}

void MainWindow::drawBlockingEdges() {
    drawer->setState(drawer->state_diff_pairs);
    drawer->generateBlockingEdgesStepByStep();
}

void MainWindow::makePreferenceListReductionEnabled() {
    drawer->solver->preferencListReduction = true;
}

void MainWindow::makePreferenceListReductionDisabled() {
    drawer->solver->preferencListReduction = false;
}
