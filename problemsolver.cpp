#include "problemsolver.h"

ProblemSolver::ProblemSolver(QList<int>* manList, QList<int>* womanList, QList<QList<int> >* manPrioritiesList, QList<QList<int> >* womanPrioritiesList, std::vector< std::vector<bool> >* neighbours)
{
    initIntValue = -1;
    this->manList = manList;
    this->womanList = womanList;
    this->neighbours = neighbours;
    this->manPrioritiesList = manPrioritiesList;
    this->womanPrioritiesList = womanPrioritiesList;
}

void ProblemSolver::solvePairingProblem() {

    initManWomanPairSolution();

    while(!everyManHasPair()) {
        for (int i=0; i < manWomanPairSolution.size(); i++) {
            if (manWomanPairSolution[i] == initIntValue) {
                proposeNextGirlForMan(i);
            }
        }
    }

    leaveUnnecessaryNeighbours();
}

int ProblemSolver::getActualPairForMan(int manIndex) {
    return manWomanPairSolution[manIndex];
}

int ProblemSolver::getActualPositionForManInPrefOreder(int prefIndex, int manIndex) {
    for (int i=0; i<(*womanPrioritiesList)[prefIndex].length(); i++) {
        if (womanPrioritiesList->value(prefIndex)[i] == manIndex) {
            return i;
        }
    }
}

int ProblemSolver::getActualPositionForWomanInPrefOreder(int prefIndex, int womanIndex) {
    for (int i=0; i<(*manPrioritiesList)[prefIndex].length(); i++) {
        if (manPrioritiesList->value(prefIndex)[i] == womanIndex) {
            return i;
        }
    }
}

bool ProblemSolver::everyManHasPair() {
    for (int i=0; i<manWomanPairSolution.size(); i++) {
        if (getActualPairForMan(i) == initIntValue) {
            return false;
        }
    }

    return true;
}

void ProblemSolver::proposeNextGirlForMan(int manIndex) {
    int nextGirlIndex = initIntValue;
    if (!manPrioritiesList->value(manIndex).empty()) {
        nextGirlIndex = manPrioritiesList->value(manIndex).first();
    } else {
        manWomanPairSolution[manIndex] = -2;
        return;
    }


    if (!girlHasPair(nextGirlIndex)) {
        takeTheGirlsHand(manIndex, nextGirlIndex);
    } else {
        if (!isGirlsActualPairBetter(nextGirlIndex, manIndex)) {
            deleteGirlsActualPair(nextGirlIndex);
            takeTheGirlsHand(manIndex, nextGirlIndex);
        } {
            (*manPrioritiesList)[manIndex].removeFirst();
        }
    }
}

bool ProblemSolver::girlHasPair(int girlIndex) {
    for (int i=0; i<manWomanPairSolution.size(); i++) {
        if (manWomanPairSolution[i] == girlIndex) {
            return true;
        }
    }

    return false;
}

bool ProblemSolver::isGirlsActualPairBetter(int nextGirlIndex, int manIndex) {
    int actualManIndex = initIntValue;

    for (int i=0; i<manWomanPairSolution.size(); i++) {
        if (manWomanPairSolution[i] == nextGirlIndex) {
            actualManIndex = i;
            break;
        }
    }

    if (getActualPositionForManInPrefOreder(nextGirlIndex, actualManIndex) < getActualPositionForManInPrefOreder(nextGirlIndex, manIndex)) {
        return true;
    } else {
        return false;
    }
}

void ProblemSolver::deleteGirlsActualPair(int nextGirlIndex) {
    for (int i=0; i<manWomanPairSolution.size(); i++) {
        if (manWomanPairSolution[i] == nextGirlIndex) {
            manWomanPairSolution[i] = initIntValue;
        }
    }
}

void ProblemSolver::takeTheGirlsHand(int manIndex, int nextGirlIndex) {
    manWomanPairSolution[manIndex] = nextGirlIndex;
    (*manPrioritiesList)[manIndex].removeFirst();
}

void ProblemSolver::initManWomanPairSolution() {
    manWomanPairSolution.resize(manList->length());

    for (int i=0; i< manWomanPairSolution.size(); i++) {
        manWomanPairSolution[i] = initIntValue;
    }
}

void ProblemSolver::leaveUnnecessaryNeighbours() {
    for (int i=0; i < neighbours->size(); i++) {
        for (int j=0; j < neighbours->size(); j++) {
            (*neighbours).at(i).at(j) = false;
        }
    }

    for (int i=0; i<manWomanPairSolution.size(); i++) {
        if (manWomanPairSolution[i] != -2) {
            (*neighbours).at((*manList).at(i)).at((*womanList).at(manWomanPairSolution[i])) = true;
            (*neighbours).at((*womanList).at(manWomanPairSolution[i])).at((*manList).at(i)) = true;
        }
    }
}
