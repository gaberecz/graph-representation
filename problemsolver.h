#ifndef PROBLEMSOLVER_H
#define PROBLEMSOLVER_H

#include <QList>
#include <QDebug>

class ProblemSolver
{
public:
    ProblemSolver(QList<int>* men, QList<int>* women, QList<QList<int> >* menPriorities, QList<QList<int> >* womenPriorities, std::vector< std::vector<bool> >* neighbours);

    QList<int>* men;
    QList<int>* women;

    QList<int>* emptyQList;
    QList<QList<int>>* menPriorities;
    QList<QList<int>>* womenPriorities;
    std::vector<int> manWomanPairSolution;
    std::vector< std::vector<bool> >* neighbours;

    void solveTheProblem();

private:
    int getActualPairForMan(int manIndex);
    int getActualPositionForManInPrefOreder(int prefIndex, int manIndex);
    int getActualPositionForWomanInPrefOreder(int prefIndex, int womanIndex);
    bool everyManHasPair();
    void proposeNextGirlForMan(int manIndex);
    void chooseBetterManForWoman();
    bool isGirlsActualPairBetter(int nextGirlIndex, int manIndex);
    bool girlHasPair(int nextGirlIndex);
    void deleteGirlsActualPair(int nextGirlIndex);
    void takeTheGirlsHand(int manIndex, int nextGirlIndex);
    void initManWomanPairSolution();
    void leaveUnnecessaryNeighbours();
};

#endif // PROBLEMSOLVER_H
