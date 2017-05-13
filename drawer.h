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
    QString state_solution_step_by_step;
    GraphStructure graphStructure;

    void resetAllData();
    void setPrioritiesOf();
    void solveTheProblem();
    Drawer(QWidget *parent = 0);
    void setState(QString state);    
    void solveTheProblemStepByStep();
    void drawBlockingEdgesStepByStep();
    void generatePriorities(bool isPrioListRandom);
    ProblemSolver* solver = new ProblemSolver(&graphStructure.manList, &graphStructure.womanList, &graphStructure.manPrioritiesList, &graphStructure.womanPrioritiesList, &graphStructure.neighbours);

private:
    QString currentState;
    QPoint cursorPosition;
    bool secondLeftArrowButtonPush;
    QList<QString> labelLettersForMen;
    QList<QString> labelLettersForWomen;

    void initSetOfLabels();
    void actionInsertElement();
    void actionSetPriority();
    void drawNextManPairing();
    void inserXMan(int number);
    void inserXWoman(int number);
    QPoint Knocking(QPoint point);
    QString RelabelIntegerNumber(int index, QString gender);
    void drawNextPairingElements();
    int randInt(int low, int high);
    void initManWomanPairSolution();
    void paintEvent(QPaintEvent* event);
    void actionInterruptPrioritySelection();
    void drawManElements(QPainter* painter);
    void drawDrawingplace(QPainter* painter);
    void linkGraphElements(QPainter* painter);
    void drawWomanElements(QPainter* painter);
    void generateRandomGraph(int gendergroupSize);
    bool eventFilter(QObject *obj, QEvent *event);
    bool cursorpositionInBorder(QPoint cursorPosition);
    void insertGenderElement(QString gender, int number);
    bool clickedOnElement(int actualXPosition, int actualYPosition);
    int indexOfClickedElement(int actualXPosition, int actualYPosition);
    void DrawEll(double x, double y, double circleRadius, QPainter* painter);
    void drawPrioritySelecterElementAndPrioritizedElements(QPainter* painter);
    void DrawEll(double x, double y, double circleRadius, QPainter* painter, int i);
    void DrawEll(double x, double y, double circleRadius, QPainter* painter, QString label);
};

#endif // DRAWER_H
