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
    double circleRadius;
    QString state_insert_man;
    QString state_insert_woman;
    QString state_set_priorities;
    GraphStructure graphStructure;

    void resetAllData();
    void setPrioritiesOf();
    Drawer(QWidget *parent = 0);
    void setState(QString state);    
    void inserXMan(int number);
    void inserXWoman(int number);
    void generateRandomGraph(int gendergroupSize);
    void generatePriorities(bool isPrioListRandom);
    ProblemSolver* solver = new ProblemSolver(&graphStructure.manList, &graphStructure.womanList, &graphStructure.manPrioritiesList, &graphStructure.womanPrioritiesList, &graphStructure.neighbours);

private:
    QString currentState;
    QPoint cursorPosition;

    void paintEvent(QPaintEvent* event);
    QPoint Knocking(QPoint point);
    int randInt(int low, int high);
    void initManWomanPairSolution();
    void drawManElements(QPainter* painter);
    void linkGraphElements(QPainter* painter);
    void drawWomanElements(QPainter* painter);
    bool eventFilter(QObject *obj, QEvent *event);
    int indexOfClickedElement(QPoint cursorPosition);
    bool cursorpositionInBorder(QPoint cursorPosition);
    void insertGenderElement(QString gender, int number);
    bool clickedOnElement(int actualXPosition, int actualYPosition);
    void DrawEll(double x, double y, double circleRadius, QPainter* painter);
    void drawPrioritySelecterElementAndPrioritizedElements(QPainter* painter);
    void DrawEll(double x, double y, double circleRadius, QPainter* painter, int i);
};

#endif // DRAWER_H
