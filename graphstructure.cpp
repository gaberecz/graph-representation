#include "graphstructure.h"

GraphStructure::GraphStructure()
{
    actualSelecterPosition = -1;
    actualSelecterGender = "none";
    prioritySetLength = 3;
}

void GraphStructure::addMan(QPoint point) {
    addXYPositions(point.x(), point.y());
    men << elementsXPosition.length() - 1;
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
        qDebug() << actualSelecterGender;
        actualSelecterPosition = positionOfXthElementInGenderbasedList(index, actualSelecterGender);
        qDebug() << actualSelecterPosition;

    } else {
        if (actualSelecterGender == "man") {
            int pos = positionOfXthElementInGenderbasedList(index, "woman");
            if (!menPriorities[actualSelecterPosition].contains(pos)) {
                menPriorities[actualSelecterPosition] << pos;
            }
            qDebug() << menPriorities;
            if (menPriorities[actualSelecterPosition].length() == prioritySetLength) {
                setPriorityselectorDatasToDefault();
            }
        } else if (actualSelecterGender == "woman") {
            int pos = positionOfXthElementInGenderbasedList(index, "man");
            if (!womenPriorities[actualSelecterPosition].contains(pos)) {
                womenPriorities[actualSelecterPosition] << pos;
            }
            qDebug() << womenPriorities;
            if (womenPriorities[actualSelecterPosition].length() == prioritySetLength) {
                setPriorityselectorDatasToDefault();
            }
        }
    }
}

void GraphStructure::setPriorityselectorDatasToDefault() {
    actualSelecterPosition = -1;
    actualSelecterGender = "none";
    qDebug() << "everething set to def";
}
