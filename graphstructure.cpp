#include "graphstructure.h"

GraphStructure::GraphStructure()
{
    actualSelecterPosition = -1;
    prioritizerPoint = -1;
    actualSelecterGender = "none";
}

void GraphStructure::addMan(QPoint point) {
    addXYPositions(point.x(), point.y());
    men << elementsXPosition.length() - 1;
    prioritySetLength = men.length();
    menPriorities << emptyQList;
}

void GraphStructure::addWoman(QPoint point) {
    addXYPositions(point.x(), point.y());
    women << elementsXPosition.length() - 1;
    womenPriorities << emptyQList;
}

void GraphStructure::addXYPositions(int xPos, int yPos) {
    elementsXPosition << xPos;
    elementsYPosition << yPos;
}

QString GraphStructure::genderOfXthElement(int indexOfELement) {
    for(int i=0; i < men.length(); i++) {
        if (men[i] == indexOfELement) {
            return "man";
        }
    }
    for(int i=0; i < women.length(); i++) {
        if (women[i] == indexOfELement) {
            return "woman";
        }
    }
}

int GraphStructure::positionOfXthElementInGenderbasedList(int indexOfELement, QString genderOfList) {
    if (genderOfList == "man") {
        for(int i=0; i < men.length(); i++) {
            if (men[i] == indexOfELement) {
                return i;
            }
        }
    } else if (genderOfList == "woman") {
        for(int i=0; i < women.length(); i++) {
            if (women[i] == indexOfELement) {
                return i;
            }
        }
    }
}


void GraphStructure::setPrioritiesForElement(int index) {
    if (actualSelecterPosition == -1) {
        actualSelecterGender = genderOfXthElement(index);
        //qDebug() << actualSelecterGender;
        actualSelecterPosition = positionOfXthElementInGenderbasedList(index, actualSelecterGender);
        prioritizerPoint = index;
        //qDebug() << actualSelecterPosition;

    } else {
        QString chosenPointGender = genderOfXthElement(index);

        if (actualSelecterGender == "man" && chosenPointGender != "man") {
            int pos = positionOfXthElementInGenderbasedList(index, "woman");
            if (!menPriorities[actualSelecterPosition].contains(pos)) {
                menPriorities[actualSelecterPosition] << pos;
            }

            //qDebug() << menPriorities;
            actualPriorityPositions << index;
            if (menPriorities[actualSelecterPosition].length() == prioritySetLength) {
                setPriorityselectorDatasToDefault();
            }
        } else if (actualSelecterGender == "woman" && chosenPointGender != "woman") {
            int pos = positionOfXthElementInGenderbasedList(index, "man");
            if (!womenPriorities[actualSelecterPosition].contains(pos)) {
                womenPriorities[actualSelecterPosition] << pos;
            }

            //qDebug() << womenPriorities;
            actualPriorityPositions << index;
            if (womenPriorities[actualSelecterPosition].length() == prioritySetLength) {
                setPriorityselectorDatasToDefault();
            }
        }
    }
}

void GraphStructure::setPriorityselectorDatasToDefault() {
    actualSelecterPosition = -1;
    actualSelecterGender = "none";
    actualPriorityPositions.clear();
    fillNeighbourData();
    qDebug() << "everething set to def";
}

void GraphStructure::fillNeighbourData() {
    for (int i=0; i < menPriorities.length(); i++) {
        for (int j=0; j < womenPriorities.length(); j++) {
            if (menPriorities[i].contains(j) && womenPriorities[j].contains(i)) {
                neighbours[men[i]][women[j]] = true;
                neighbours[women[j]][men[i]] = true;
            }
        }
    }

    qDebug() << neighbours;
}

void GraphStructure::initNeighboursVector() {
    neighbours.resize(elementsXPosition.length());
    for (int i=0;i<elementsXPosition.length();i++) {
        neighbours[i].resize(elementsXPosition.length());
    }

    for (int i=0; i < neighbours.size(); i++) {
        for (int j=0; j < neighbours.size(); j++) {
            neighbours[i][j] = false;
        }
    }

    qDebug() << neighbours;
}

void GraphStructure::generateRandomGraph(int genderSize) {

}

void GraphStructure::solveTheProblem() {

}
