#ifndef GRAPHSTRUCTURE_H
#define GRAPHSTRUCTURE_H

#include <QList>
#include <QGraphicsScene>
#include <QDebug>
#include <QTime>
#include <qmath.h>

class GraphStructure
{
public:
    GraphStructure();

    QList<int> manList;
    QList<int> womanList;
    int prioritizerPoint;
    QList<int> elementsXPosition;
    QList<int> elementsYPosition;
    QList<int> actualPriorityPositions;
    QList<QList<int>> manPrioritiesList;
    QList<QList<int>> womanPrioritiesList;
    std::vector< std::vector<bool> > neighbours;

    void addMan(QPoint point);
    bool selectingPriorities();
    void addWoman(QPoint point);
    void initNeighboursVector();
    int insertedElementsNumber();
    void setPrioritiesForElement(int index);
    void setPriorityselectorDatasToDefault();
    void generatePrioritiesForElements(bool isPrioListRandom);
    void insertXMan(int number, int width, int height, int circleRadius);
    void insertXWoman(int number, int width, int height, int circleRadius);

private:
    QString man;
    QString woman;
    int initIntValue;
    QList<int> emptyQList;
    QString initStringValue;
    int actualSelecterPosition;
    QString actualSelecterGender;

    void fillNeighbourData();
    int randInt(int low, int high);
    void addXYPositions(int xPos, int yPos);
    QString genderOfXthElement(int indexOfELement);
    int positionOfXthElementInGenderbasedList(int indexOfELement, QString genderOfList);
    void insertGenderElement(QString gender, int number, int width, int height, int circleRadius);
};

#endif // GRAPHSTRUCTURE_H
