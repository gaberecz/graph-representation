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
    int actualSelecterPosition;
    QList<int> elementsXPosition;
    QList<int> elementsYPosition;
    QString actualSelecterGender;
    QList<int> actualPriorityPositions;
    QList<QList<int>> manPrioritiesList;
    QList<QList<int>> allPossiblePairing;
    QList<QList<QList<int>>> blockingPairs;
    QList<QList<int>> womanPrioritiesList;
    std::vector< std::vector<bool> > neighbours;

    void addMan(QPoint point);
    bool selectingPriorities();
    void addWoman(QPoint point);
    void initNeighboursVector();
    int insertedElementsNumber();
    void generateAllPossiblePairing();
    void setPrioritiesForElement(int index);
    void setPriorityselectorDatasToDefault();
    void generatePrioritiesForElements(bool isPrioListRandom, int prioListLength);
    void insertXMan(int number, int width, int height, int circleRadius);
    void insertXWoman(int number, int width, int height, int circleRadius);
    int positionOfXthElementInGenderbasedList(int indexOfELement, QString genderOfList);
    int getXthElementsPositionInYsPreferenceList(int element, QList<int> prefList);
    QList<int> getPreferenceListElementsOfGenderlessElement(int clickedElementIndex);

private:
    QString man;
    QString woman;
    int initIntValue;
    QList<int> emptyQList;
    QList<QList<int>> emptyQQList;
    QString initStringValue;

    void fillNeighbourData();
    int randInt(int low, int high);
    void addXYPositions(int xPos, int yPos);
    void generatePermutation(QList<int> list, QList<int> permutationPrefix);
    QString genderOfXthElement(int indexOfELement);
    void insertGenderElement(QString gender, int number, int width, int height, int circleRadius);
};

#endif // GRAPHSTRUCTURE_H
