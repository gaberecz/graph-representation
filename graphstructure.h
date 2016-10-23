#ifndef GRAPHSTRUCTURE_H
#define GRAPHSTRUCTURE_H

#include <QList>
#include <QGraphicsScene>
#include <QDebug>

class GraphStructure
{
public:
    GraphStructure();
    QList<int> elementsXPosition;
    QList<int> elementsYPosition;

    QList<int> men;
    QList<int> women;

    QList<int> emptyQList;
    QList<QList<int>> menPriorities;
    QList<QList<int>> womenPriorities;
    QString actualSelecterGender;
    int actualSelecterPosition;
    int prioritySetLength;
    int prioritizerPoint;
    QList<int> actualPriorityPositions;
    std::vector< std::vector<bool> > neighbours;

    void addMan(QPoint point);
    void addWoman(QPoint point);
    void addXYPositions(int xPos, int yPos);
    void setPrioritiesForElement(int index);
    QString genderOfXthElement(int indexOfELement);
    int positionOfXthElementInGenderbasedList(int indexOfELement, QString genderOfList);
    void initNeighboursVector();
    void setPriorityselectorDatasToDefault();
    void generateRandomGraph(int genderSize);
    void solveTheProblem();

private:
    void fillNeighbourData();
};

#endif // GRAPHSTRUCTURE_H
