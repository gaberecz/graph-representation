#include "problemsolver.h"

ProblemSolver::ProblemSolver(QList<int>* men, QList<int>* women, QList<QList<int> >* menPriorities, QList<QList<int> >* womenPriorities, std::vector< std::vector<bool> >* neighbours)
{
    this->men = men;
    this->women = women;
    this->menPriorities = menPriorities;
    this->womenPriorities = womenPriorities;
    this->neighbours = neighbours;
}

void ProblemSolver::solveTheProblem() {

    initManWomanPairSolution();
    qDebug() << manWomanPairSolution;

    while(!everyManHasPair()) {
        for (int i=0; i < manWomanPairSolution.size(); i++) {
            if (manWomanPairSolution[i] == -1) {
                proposeNextGirlForMan(i);
            }
        }
    }

    leaveUnnecessaryNeighbours();

    qDebug() << manWomanPairSolution;
}

int ProblemSolver::getActualPairForMan(int manIndex) {
    return manWomanPairSolution[manIndex];
}

int ProblemSolver::getActualPositionForManInPrefOreder(int prefIndex, int manIndex) {
    for (int i=0; i<(*womenPriorities)[prefIndex].length(); i++) {
        if (womenPriorities->value(prefIndex)[i] == manIndex) {
            return i;
        }
    }
}

int ProblemSolver::getActualPositionForWomanInPrefOreder(int prefIndex, int womanIndex) {
    for (int i=0; i<(*menPriorities)[prefIndex].length(); i++) {
        if (menPriorities->value(prefIndex)[i] == womanIndex) {
            return i;
        }
    }
}

bool ProblemSolver::everyManHasPair() {
    for (int i=0; i<manWomanPairSolution.size(); i++) {
        if (getActualPairForMan(i) == -1) {
            return false;
        }
    }

    return true;
}

void ProblemSolver::proposeNextGirlForMan(int manIndex) {
    int nextGirlIndex = menPriorities->value(manIndex).first();

    if (!girlHasPair(nextGirlIndex)) {
        takeTheGirlsHand(manIndex, nextGirlIndex);
    } else {
        if (!isGirlsActualPairBetter(nextGirlIndex, manIndex)) {
            deleteGirlsActualPair(nextGirlIndex);
            takeTheGirlsHand(manIndex, nextGirlIndex);
        }
    }
}

bool ProblemSolver::girlHasPair(int nextGirlIndex) {
    for (int i=0; i<manWomanPairSolution.size(); i++) {
        if (manWomanPairSolution[i] == nextGirlIndex) {
            return true;
        }
    }

    return false;
}

bool ProblemSolver::isGirlsActualPairBetter(int nextGirlIndex, int manIndex) {
    int actualManIndex = -1;

    for (int i=0; i<manWomanPairSolution.size(); i++) {
        if (manWomanPairSolution[i] == nextGirlIndex) {
            actualManIndex = i;
            break;
        }
    }

    if (getActualPositionForManInPrefOreder(nextGirlIndex, manIndex) > getActualPositionForManInPrefOreder(nextGirlIndex, manIndex)) {
        return true;
    } else {
        return false;
    }
}

void ProblemSolver::deleteGirlsActualPair(int nextGirlIndex) {
    for (int i=0; i<manWomanPairSolution.size(); i++) {
        if (manWomanPairSolution[i] == nextGirlIndex) {
            manWomanPairSolution[i] = -1;
        }
    }
}

void ProblemSolver::takeTheGirlsHand(int manIndex, int nextGirlIndex) {
    manWomanPairSolution[manIndex] = nextGirlIndex;
    (*menPriorities)[manIndex].removeFirst();
}

void ProblemSolver::initManWomanPairSolution() {
    manWomanPairSolution.resize(men->length());

    for (int i=0; i< manWomanPairSolution.size(); i++) {
        manWomanPairSolution[i] = -1;
    }
}

void ProblemSolver::leaveUnnecessaryNeighbours() {
    for (int i=0; i < neighbours->size(); i++) {
        for (int j=0; j < neighbours->size(); j++) {
            (*neighbours).at(i).at(j) = false;
        }
    }

    for (int i=0; i<manWomanPairSolution.size(); i++) {
        (*neighbours).at((*men).at(i)).at((*women).at(manWomanPairSolution[i])) = true;
        (*neighbours).at((*women).at(manWomanPairSolution[i])).at((*men).at(i)) = true;
    }
}
