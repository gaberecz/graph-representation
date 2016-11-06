#include "graphstructure.h"

GraphStructure::GraphStructure() {
    initIntValue = -1;
    initStringValue = "none";
    man = "man";
    woman = "woman";

    prioritizerPoint = initIntValue;
    actualSelecterPosition = initIntValue;
    actualSelecterGender = initStringValue;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

void GraphStructure::addMan(QPoint point) {
    addXYPositions(point.x(), point.y());
    manList << elementsXPosition.length() - 1;
    manPrioritiesList << emptyQList;
}

void GraphStructure::addWoman(QPoint point) {
    addXYPositions(point.x(), point.y());
    womanList << elementsXPosition.length() - 1;
    womanPrioritiesList << emptyQList;
}

void GraphStructure::addXYPositions(int xPos, int yPos) {
    elementsXPosition << xPos;
    elementsYPosition << yPos;
}

QString GraphStructure::genderOfXthElement(int indexOfELement) {
    for(int i=0; i < manList.length(); i++) {
        if (manList[i] == indexOfELement) {
            return man;
        }
    }

    return woman;
}

int GraphStructure::positionOfXthElementInGenderbasedList(int indexOfELement, QString genderOfList) {
    if (genderOfList == man) {
        for(int i=0; i < manList.length(); i++) {
            if (manList[i] == indexOfELement) {
                return i;
            }
        }
    } else if (genderOfList == woman) {
        for(int i=0; i < womanList.length(); i++) {
            if (womanList[i] == indexOfELement) {
                return i;
            }
        }
    }
}


void GraphStructure::setPrioritiesForElement(int index) {
    if (actualSelecterPosition == initIntValue) {
        prioritizerPoint = index;
        actualSelecterGender = genderOfXthElement(index);
        actualSelecterPosition = positionOfXthElementInGenderbasedList(index, actualSelecterGender);
    } else {
        QString choosenPointGender = genderOfXthElement(index);

        if (actualSelecterGender == man && choosenPointGender != man) {
            int pos = positionOfXthElementInGenderbasedList(index, woman);

            if (!manPrioritiesList[actualSelecterPosition].contains(pos)) {
                manPrioritiesList[actualSelecterPosition] << pos;
            }

            actualPriorityPositions << index;

            if (manPrioritiesList[actualSelecterPosition].length() == womanList.length()) {
                setPriorityselectorDatasToDefault();
            }
        } else if (actualSelecterGender == woman && choosenPointGender != woman) {
            int pos = positionOfXthElementInGenderbasedList(index, man);

            if (!womanPrioritiesList[actualSelecterPosition].contains(pos)) {
                womanPrioritiesList[actualSelecterPosition] << pos;
            }

            actualPriorityPositions << index;

            if (womanPrioritiesList[actualSelecterPosition].length() == manList.length()) {
                setPriorityselectorDatasToDefault();
            }
        }
    }
}

int GraphStructure::randInt(int low, int high) {
    return qrand() % ((high + 1) - low) + low;
}

void GraphStructure::setPriorityselectorDatasToDefault() {
    fillNeighbourData();
    prioritizerPoint = initIntValue;
    actualSelecterPosition = initIntValue;
    actualSelecterGender = initStringValue;
    actualPriorityPositions.clear();
}

void GraphStructure::fillNeighbourData() {
    for (int i=0; i < manPrioritiesList.length(); i++) {
        for (int j=0; j < womanPrioritiesList.length(); j++) {
            if (manPrioritiesList[i].contains(j) && womanPrioritiesList[j].contains(i)) {
                neighbours[manList[i]][womanList[j]] = true;
                neighbours[womanList[j]][manList[i]] = true;
            }
        }
    }
}

void GraphStructure::initNeighboursVector() {
    neighbours.resize(insertedElementsNumber());
    for (int i=0;i<insertedElementsNumber();i++) {
        neighbours[i].resize(insertedElementsNumber());
    }

    for (int i=0; i < neighbours.size(); i++) {
        for (int j=0; j < neighbours.size(); j++) {
            neighbours[i][j] = false;
        }
    }

}

int GraphStructure::insertedElementsNumber() {
    return elementsXPosition.length();
}

bool GraphStructure::selectingPriorities() {
    return actualSelecterPosition != -1;
}



void GraphStructure::insertXMan(int number, int width, int height, int circleRadius) {
    insertGenderElement(man, number, width, height, circleRadius);
}

void GraphStructure::insertXWoman(int number, int width, int height, int circleRadius) {
    insertGenderElement(woman, number, width, height, circleRadius);
}

void GraphStructure::insertGenderElement(QString gender, int number, int width, int height, int circleRadius) {
    int insertionXPosition = circleRadius / 2 + 5;
    int insertionYPosition = circleRadius / 2 + 5;

    if (gender == woman) {
        insertionYPosition = height - circleRadius / 2 - 5;
    }

    for (int i=0; i<number; i++) {
        if (gender == man) {
            addMan(QPoint(insertionXPosition, insertionYPosition));
        } else if (gender == woman) {
            addWoman(QPoint(insertionXPosition, insertionYPosition));
        }

        if (insertionXPosition + circleRadius < width) {
            insertionXPosition += circleRadius + 5;
        } else {
            insertionXPosition = circleRadius / 2 + 5;
            if (gender == man) {
                insertionYPosition += circleRadius + 5;
            } else if (gender == woman) {
                insertionYPosition -= circleRadius + 5;
            }
        }

    }
}

void GraphStructure::generatePrioritiesForElements(bool isPrioListRandom, int prioListLength) {
    initNeighboursVector();

    for (int i=0; i<manPrioritiesList.size(); i++) {
        QList<int> possibleElementsList;

        if (isPrioListRandom) {
            prioListLength = randInt(0, prioListLength);
        }

        for (int i=0; i<womanList.size(); i++) {
            possibleElementsList << i;
        }

        while (manPrioritiesList[i].size() != prioListLength) {
            int randomIndex = randInt(0,possibleElementsList.size() - 1);
            manPrioritiesList[i] << possibleElementsList[randomIndex];
            possibleElementsList.removeAt(randomIndex);
        }
    }

    for (int i=0; i<womanPrioritiesList.size(); i++) {
        QList<int> possibleElementsList;

        if (isPrioListRandom) {
            prioListLength = randInt(0, prioListLength);
        }

        for (int i=0; i<manList.size(); i++) {
            possibleElementsList << i;
        }

        while (womanPrioritiesList[i].size() != prioListLength) {
            int randomIndex = randInt(0,possibleElementsList.size() - 1);
            womanPrioritiesList[i] << possibleElementsList[randomIndex];
            possibleElementsList.removeAt(randomIndex);
        }
    }

    fillNeighbourData();
}
