#ifndef PROBLEMSOLVER_H
#define PROBLEMSOLVER_H

#include <QList>
#include <QDebug>
#include "graphstructure.h"

class ProblemSolver
{
public:
    ProblemSolver(/*QList<int>* manList, QList<int>* womanList, QList<QList<int> >* manPrioritiesList, QList<QList<int> >* womanPrioritiesList, std::vector< std::vector<bool> >* neighbours, QList<QList<int>>* blockingPairs*/);
    bool everyManHasPair();
    void solvePairingProblem();
    void initManWomanPairSolution();
    void solvePairingProblemNextStep();
    void leaveUnnecessaryElementsFromPrioLists();
    void addActualGraphStructure(GraphStructure* graphStructure);

    int sbsNextMan;
    int statusWillBeLonely;
    int sbsProcessFinished;
    bool preferencListReduction;
    void generateAllBlockingPairs();
    std::vector<int> manWomanPairSolution;
    void cleanWomanPrioritiesAfterWorkDone();

private:
    int initIntValue;
    QList<int> emptyQList;
    QList<QList<int>> emptyQQList;
    GraphStructure* graphStructure;
    /*QList<int>* manList;
    QList<int>* womanList;
    QList<int>* emptyQList;
    QList<QList<int>>* manPrioritiesList;
    QList<QList<int>>* womanPrioritiesList;
    std::vector< std::vector<bool> >* neighbours;
    QList<QList<int>>* blockingPairs;*/

    void chooseBetterManForWoman();
    void leaveUnnecessaryNeighbours();
    bool girlHasPair(int nextGirlIndex);
    int getActualPairForMan(int manIndex);
    void proposeNextGirlForMan(int manIndex);
    void deleteGirlsActualPair(int nextGirlIndex);
    void takeTheGirlsHand(int manIndex, int nextGirlIndex);
    bool isGirlsActualPairBetter(int nextGirlIndex, int manIndex);
    int getActualPositionForManInPrefOreder(int prefIndex, int manIndex);
    int getActualPositionForWomanInPrefOreder(int prefIndex, int womanIndex);
    void reducePrioritiesLists(int manIndex, int nextGirlIndex);
};

#endif // PROBLEMSOLVER_H
