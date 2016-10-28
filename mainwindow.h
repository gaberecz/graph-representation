#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawer.h"
#include <QDebug>
#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Dialog* dialog;
public:
    Drawer* drawer;

public slots:
    void setStateToInsertMan();
    void setStateToInsertWoman();
    void resetAllDataForDraw();
    void setPrioritiesOfElement();
    void generateRandomGraph();
    void solverPairingProblem();
};

#endif // MAINWINDOW_H
