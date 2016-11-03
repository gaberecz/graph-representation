#ifndef PROBLEMSOLVER_H
#define PROBLEMSOLVER_H

#include <QList>
#include <QDebug>

class ProblemSolver
{
public:
    ProblemSolver(QList<int>* manList, QList<int>* womanList, QList<QList<int> >* manPrioritiesList, QList<QList<int> >* womanPrioritiesList, std::vector< std::vector<bool> >* neighbours);
    void solvePairingProblem();
    void leaveUnnecessaryElementsFromPrioLists();

private:
    int initIntValue;
    QList<int>* manList;
    QList<int>* womanList;
    QList<int>* emptyQList;
    QList<QList<int>>* manPrioritiesList;
    QList<QList<int>>* womanPrioritiesList;
    std::vector<int> manWomanPairSolution;
    std::vector< std::vector<bool> >* neighbours;

    bool everyManHasPair();
    void chooseBetterManForWoman();
    void initManWomanPairSolution();
    void leaveUnnecessaryNeighbours();
    bool girlHasPair(int nextGirlIndex);
    int getActualPairForMan(int manIndex);
    void proposeNextGirlForMan(int manIndex);
    void deleteGirlsActualPair(int nextGirlIndex);
    void takeTheGirlsHand(int manIndex, int nextGirlIndex);
    bool isGirlsActualPairBetter(int nextGirlIndex, int manIndex);
    int getActualPositionForManInPrefOreder(int prefIndex, int manIndex);
    int getActualPositionForWomanInPrefOreder(int prefIndex, int womanIndex);
};

#endif // PROBLEMSOLVER_H
