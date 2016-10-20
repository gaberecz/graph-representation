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

class Drawer : public QWidget
{
public:
    Drawer(QWidget *parent = 0);
    void paintEvent(QPaintEvent* event);
    bool eventFilter(QObject *obj, QEvent *event);
    QString insert_man;
    QString insert_woman;
    QString operationState;

private:
    double radius;
    QPoint CursorPosition;
    GraphStructure graphStructure;
    bool cursorpositionInBorder(QPoint CursorPosition);
    void DrawEll(double x, double y, double radius, QPainter* painter, int i);
};

#endif // DRAWER_H
