#include "graphstructure.h"

GraphStructure::GraphStructure()
{

}

void GraphStructure::addMan(int xPos, int yPos) {
    addXYPositions(xPos, yPos);
    men << elementsXPosition.length() - 1;
}

void GraphStructure::addWoman(int xPos, int yPos) {
    addXYPositions(xPos, yPos);
    women <<elementsXPosition.length() - 1;
}

void GraphStructure::addXYPositions(int xPos, int yPos) {
    elementsXPosition << xPos;
    elementsYPosition << yPos;
}
