#include "problemsolver.h"

ProblemSolver::ProblemSolver(/*QList<int>* manList, QList<int>* womanList, QList<QList<int> >* manPrioritiesList, QList<QList<int> >* womanPrioritiesList, std::vector< std::vector<bool> >* neighbours, QList<QList<int>>* blockingPairs*/)
{
    initIntValue = -1;
    sbsNextMan = 0;
    statusWillBeLonely = -2;
    sbsProcessFinished = -2;
    /*this->manList = manList;
    this->womanList = womanList;
    this->neighbours = neighbours;
    this->manPrioritiesList = manPrioritiesList;
    this->womanPrioritiesList = womanPrioritiesList;
    this->blockingPairs = blockingPairs;*/
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
        sbsNextMan = sbsProcessFinished;
    }

    if (sbsNextMan != sbsProcessFinished) {
        sbsNextMan++;
    }

    leaveUnnecessaryNeighbours();
}

void ProblemSolver::cleanWomanPrioritiesAfterWorkDone() {
    for (int i=0; i < (*graphStructure).womanPrioritiesList.size(); i++) {
        if (!girlHasPair(i)) {
            (*graphStructure).womanPrioritiesList[i].clear();
            //(*womanPrioritiesList)[i].clear();
        }
    }
}

int ProblemSolver::getActualPairForMan(int manIndex) {
    return manWomanPairSolution[manIndex];
}

int ProblemSolver::getActualPositionForManInPrefOreder(int prefIndex, int manIndex) {
    for (int i=0; i<(*graphStructure).womanPrioritiesList[prefIndex].length(); i++) {
        if ((*graphStructure).womanPrioritiesList[prefIndex][i] == manIndex) {
            return i;
        }
    }
}

int ProblemSolver::getActualPositionForWomanInPrefOreder(int prefIndex, int womanIndex) {
    for (int i=0; i<(*graphStructure).manPrioritiesList[prefIndex].length(); i++) {
        if ((*graphStructure).manPrioritiesList[prefIndex][i] == womanIndex) {
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
    if (!(*graphStructure).manPrioritiesList[manIndex].empty()) {
        nextGirlIndex = (*graphStructure).manPrioritiesList[manIndex].first();
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
            (*graphStructure).manPrioritiesList[manIndex].removeFirst();
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
    (*graphStructure).manPrioritiesList[manIndex].removeFirst();
}

void ProblemSolver::initManWomanPairSolution() {
    manWomanPairSolution.resize((*graphStructure).manList.length());

    for (int i=0; i< manWomanPairSolution.size(); i++) {
        manWomanPairSolution[i] = initIntValue;
    }
}

void ProblemSolver::leaveUnnecessaryNeighbours() {
    for (int i=0; i < (*graphStructure).neighbours.size(); i++) {
        for (int j=0; j < (*graphStructure).neighbours.size(); j++) {
            (*graphStructure).neighbours[i][j] = false;
            //(*neighbours).at(i).at(j) = false;
        }
    }

    for (int i=0; i<manWomanPairSolution.size(); i++) {
        if (manWomanPairSolution[i] != statusWillBeLonely && manWomanPairSolution[i] != initIntValue) {
            (*graphStructure).neighbours[(*graphStructure).manList[i]][(*graphStructure).womanList[manWomanPairSolution[i]]] = true;
            (*graphStructure).neighbours[(*graphStructure).womanList[manWomanPairSolution[i]]][(*graphStructure).manList[i]] = true;
            //(*neighbours).at((*manList).at(i)).at((*womanList).at(manWomanPairSolution[i])) = true;
            //(*neighbours).at((*womanList).at(manWomanPairSolution[i])).at((*manList).at(i)) = true;
        }
    }
}

void ProblemSolver::leaveUnnecessaryElementsFromPrioLists() {
    for (int i=0; i<(*graphStructure).manPrioritiesList.size(); i++) {
        for (int j=0; j<(*graphStructure).manPrioritiesList[i].size(); j++) {
            if (!(*graphStructure).womanPrioritiesList[(*graphStructure).manPrioritiesList[i][j]].contains(i)) {
                (*graphStructure).manPrioritiesList[i].removeAt(j);
                j--;
            }
        }
    }

    for (int i=0; i<(*graphStructure).womanPrioritiesList.size(); i++) {
        for (int j=0; j<(*graphStructure).womanPrioritiesList[i].size(); j++) {
            if (!(*graphStructure).manPrioritiesList[(*graphStructure).womanPrioritiesList[i][j]].contains(i)) {
                (*graphStructure).womanPrioritiesList[i].removeAt(j);
                j--;
            }
        }
    }
}

void ProblemSolver::generateAllBlockingPairs() {

    /*for(int i=0; i<(*graphStructure).manPrioritiesList.size(); i++) {
        qDebug() << "m_" << i << ": " << (*graphStructure).manPrioritiesList[i];
    }

    for(int i=0; i<(*graphStructure).womanPrioritiesList.size(); i++) {
        qDebug() << "w_" << i << ": " << (*graphStructure).womanPrioritiesList[i];
    }

    for (int indexOfPairs=0; indexOfPairs<(*graphStructure).allPossiblePairing.size(); indexOfPairs++) {
        qDebug() << "pairing_" << indexOfPairs << ": " << (*graphStructure).allPossiblePairing[indexOfPairs];
    }

    qDebug() << "second pairing second pair: " << ((*graphStructure).allPossiblePairing[1]).indexOf((*graphStructure).allPossiblePairing[1][1], 0);

    qDebug() << "second pairing second pair: " << ((*graphStructure).allPossiblePairing[1]).indexOf((*graphStructure).allPossiblePairing[1][2], 0);*/

    for (int indexOfPairs=0; indexOfPairs<(*graphStructure).allPossiblePairing.size(); indexOfPairs++) {
        (*graphStructure).blockingPairs << emptyQQList;
        for (int indexOfCouples=0; indexOfCouples<(*graphStructure).allPossiblePairing[indexOfPairs].size(); indexOfCouples++) {
          int positionOfActualPairInPrefList = (*graphStructure).manPrioritiesList[indexOfCouples].indexOf((*graphStructure).allPossiblePairing[indexOfPairs][indexOfCouples], 0);
          //qDebug() << "positionOfActualPairInPrefList = " << positionOfActualPairInPrefList;

          for (int indexOfMorePreferedWoman=0; indexOfMorePreferedWoman<positionOfActualPairInPrefList; indexOfMorePreferedWoman++) {
            int womanWithHigherPref = (*graphStructure).manPrioritiesList[indexOfCouples][indexOfMorePreferedWoman];
            //qDebug() << "womanWithHigherPref = " << womanWithHigherPref;

            for (int indexOfMorePreferedMan=0; indexOfMorePreferedMan<(*graphStructure).womanPrioritiesList[womanWithHigherPref].size(); indexOfMorePreferedMan++) {
                int manPreferedByWoman = (*graphStructure).womanPrioritiesList[womanWithHigherPref][indexOfMorePreferedMan];
                int manOfStablePair = (*graphStructure).allPossiblePairing[indexOfPairs].indexOf(womanWithHigherPref, 0);

                if ( manPreferedByWoman == manOfStablePair) {
                    //qDebug() << indexOfCouples << " = " << manPreferedByWoman << " = " << manOfStablePair;
                    break;
                }

                if (manPreferedByWoman == indexOfCouples) {
                    (*graphStructure).blockingPairs[indexOfPairs] << emptyQList;
                    (*graphStructure).blockingPairs[indexOfPairs].last() << indexOfCouples;
                    (*graphStructure).blockingPairs[indexOfPairs].last() << womanWithHigherPref;
                }
            }
          }
        }
    }

    /*for (int i=0; i<(*graphStructure).blockingPairs.size(); i++) {
        qDebug() << i << ": " << (*graphStructure).blockingPairs[i];
    }*/
}

void ProblemSolver::addActualGraphStructure(GraphStructure* graphStructure) {
    this->graphStructure = graphStructure;
    (*this->graphStructure).generateAllPossiblePairing();
}
