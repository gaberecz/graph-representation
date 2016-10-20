#ifndef GRAPHSTRUCTURE_H
#define GRAPHSTRUCTURE_H

#include <QList>

class GraphStructure
{
public:
    GraphStructure();
    QList<int> elementsXPosition;
    QList<int> elementsYPosition;
    QList<int> men;
    QList<int> women;

    void addMan(int xPos, int yPos);
    void addWoman(int xPos, int yPos);
    void addXYPositions(int xPos, int yPos);
};

#endif // GRAPHSTRUCTURE_H
