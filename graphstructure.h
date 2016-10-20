#ifndef GRAPHSTRUCTURE_H
#define GRAPHSTRUCTURE_H

#include <QList>
#include <QGraphicsScene>

class GraphStructure
{
public:
    GraphStructure();
    QList<int> elementsXPosition;
    QList<int> elementsYPosition;
    QList<int> men;
    QList<int> women;

    void addMan(QPoint point);
    void addWoman(QPoint point);
    void addXYPositions(int xPos, int yPos);
};

#endif // GRAPHSTRUCTURE_H
