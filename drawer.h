#ifndef DRAWER_H
#define DRAWER_H
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QList>
#include <qmath.h>
#include <QGlobal.h>
#include <QTime>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>

#include "graphstructure.h"
#include "problemsolver.h"

class Drawer : public QWidget
{
public:
    Drawer(QWidget *parent = 0);
    void resetAllData();
    QString insert_man;
    QString insert_woman;
    QString set_priorities;
    QString operationState;
    void setPrioritiesOf();
    GraphStructure graphStructure;
    void generateRandomGraph(int gendergroupSize);
    ProblemSolver* solver = new ProblemSolver(&graphStructure.men, &graphStructure.women, &graphStructure.menPriorities, &graphStructure.womenPriorities, &graphStructure.neighbours);
    void solveTheProblem();

private:
    double radius;
    QPoint cursorPosition;
    void paintEvent(QPaintEvent* event);
    bool eventFilter(QObject *obj, QEvent *event);
    bool cursorpositionInBorder(QPoint cursorPosition);
    void DrawEll(double x, double y, double radius, QPainter* painter, int i);
    void DrawEll(double x, double y, double radius, QPainter* painter);
    QPoint Knocking(QPoint point);
    int randInt(int low, int high);
    bool clickedOnElement(int actualXPosition, int actualYPosition);
    int indexOfClickedElement(QPoint cursorPosition);
    void initManWomanPairSolution();
};

#endif // DRAWER_H
