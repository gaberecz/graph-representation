#include "graphstructure.h"

GraphStructure::GraphStructure()
{

}

void GraphStructure::addMan(QPoint point) {
    addXYPositions(point.x(), point.y());
    men << elementsXPosition.length() - 1;
}

void GraphStructure::addWoman(QPoint point) {
    addXYPositions(point.x(), point.y());
    women << elementsXPosition.length() - 1;
}

void GraphStructure::addXYPositions(int xPos, int yPos) {
    elementsXPosition << xPos;
    elementsYPosition << yPos;
}
