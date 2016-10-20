#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawer.h"
#include <QDebug>

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
public:
    Drawer* drawer;

public slots:
    void insertMan();
    void insertWoman();
    void resetAllData();
    void setPrioritiesOf();
};

#endif // MAINWINDOW_H
