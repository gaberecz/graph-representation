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

    void addMan(QPoint point);
    void addWoman(QPoint point);
    void addXYPositions(int xPos, int yPos);
    void setPrioritiesForElement(int index);
    QString genderOfXthElement(int indexOfELement);
    int positionOfXthElementInGenderbasedList(int indexOfELement, QString genderOfList);

private:
    void setPriorityselectorDatasToDefault();
};

#endif // GRAPHSTRUCTURE_H
