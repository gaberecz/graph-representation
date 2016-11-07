#include "problemsolver.h"

ProblemSolver::ProblemSolver(QList<int>* manList, QList<int>* womanList, QList<QList<int> >* manPrioritiesList, QList<QList<int> >* womanPrioritiesList, std::vector< std::vector<bool> >* neighbours)
{
    initIntValue = -1;
    sbsNextMan = 0;
    statusWillBeLonely = -2;
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

void ProblemSolver::solvePairingProblemNextStep() {
    if (sbsNextMan == manWomanPairSolution.size()) {
        sbsNextMan = 0;
    }

    if (!everyManHasPair()) {
        if (manWomanPairSolution[sbsNextMan] == initIntValue) {
            proposeNextGirlForMan(sbsNextMan);
        }
    }

    if (everyManHasPair()) {
        sbsNextMan = statusWillBeLonely;
    }

    if (sbsNextMan != statusWillBeLonely) {
        sbsNextMan++;
    }
    qDebug() << manWomanPairSolution;
    leaveUnnecessaryNeighbours();

}

void ProblemSolver::cleanWomanPrioritiesAfterWorkDone() {
    for (int i=0; i < womanPrioritiesList->size(); i++) {
        if (!girlHasPair(i)) {
            (*womanPrioritiesList)[i].clear();
        }
    }
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
        manWomanPairSolution[manIndex] = statusWillBeLonely;
        return;
    }


    if (!girlHasPair(nextGirlIndex)) {
        takeTheGirlsHand(manIndex, nextGirlIndex);
    } else {
        if (!isGirlsActualPairBetter(nextGirlIndex, manIndex)) {
            deleteGirlsActualPair(nextGirlIndex);
            takeTheGirlsHand(manIndex, nextGirlIndex);
        } else {
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
        if (manWomanPairSolution[i] != statusWillBeLonely && manWomanPairSolution[i] != initIntValue) {
            (*neighbours).at((*manList).at(i)).at((*womanList).at(manWomanPairSolution[i])) = true;
            (*neighbours).at((*womanList).at(manWomanPairSolution[i])).at((*manList).at(i)) = true;
        }
    }
}

void ProblemSolver::leaveUnnecessaryElementsFromPrioLists() {
    for (int i=0; i<manPrioritiesList->size(); i++) {
        for (int j=0; j<(*manPrioritiesList)[i].size(); j++) {
            if (!(*womanPrioritiesList)[(*manPrioritiesList)[i][j]].contains(i)) {
                (*manPrioritiesList)[i].removeAt(j);
                j--;
            }
        }
    }

    for (int i=0; i<womanPrioritiesList->size(); i++) {
        for (int j=0; j<(*womanPrioritiesList)[i].size(); j++) {
            if (!(*manPrioritiesList)[(*womanPrioritiesList)[i][j]].contains(i)) {
                (*womanPrioritiesList)[i].removeAt(j);
                j--;
            }
        }
    }
}
