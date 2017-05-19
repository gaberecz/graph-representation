#include "drawer.h"

Drawer::Drawer(QWidget *parent) :
    QWidget(parent)
{
    installEventFilter(this);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    state_insert_man = "insert_man";
    state_insert_woman = "insert_woman";
    state_set_priorities = "set_priorities";
    state_diff_pairs = "looking_for_blocking_pairs";
    state_solution_step_by_step = "solution_step_by_step";
    currentState = "";
    secondLeftArrowButtonPush = false;
    initSetOfLabels();

    QTimer* redrawTimer = new QTimer(this);
    connect(redrawTimer, SIGNAL(timeout()), this, SLOT(update()));
    redrawTimer->start(5);

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    circleRadius = 40;
    pairingId = -1;
}

void Drawer::paintEvent(QPaintEvent *event) {

    QPainter painter(this);
    drawDrawingplace(&painter);
    linkGraphElements(&painter);
    drawActualTestPairing(&painter);
    drawManElements(&painter);
    drawWomanElements(&painter);
    drawPrioritySelecterElementAndPrioritizedElements(&painter);
    drawPriorityOfMouseoverElement(&painter);
}

void Drawer::drawDrawingplace(QPainter* painter) {
    QPen pen;
    pen.setWidth(2);
    (*painter).setPen(pen);
    QFont font = (*painter).font();
    font.setPointSize(14);
    (*painter).setFont(font);

    (*painter).setBrush(QBrush("#cccbc9"));
    (*painter).drawRect(0, 0, this->width(), this->height());
}

bool Drawer::eventFilter(QObject *obj, QEvent *event) {

    if (event->type() == QMouseEvent::MouseMove) {
        cursorPosition = this->mapFromGlobal(QCursor::pos());
    } else {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                //if (cursorpositionInBorder(cursorPosition)) {
                    actionInsertElement();
                //}
            } else if (mouseEvent->button() == Qt::RightButton) {
                if (currentState.contains(state_set_priorities)) {
                    actionInterruptPrioritySelection();
                }
            }
        }
    }

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Right) {
            if (solver->sbsNextMan != solver->sbsProcessFinished) {
                if (currentState == state_solution_step_by_step) {
                    if (secondLeftArrowButtonPush) {
                        drawNextManPairing();
                    } else {
                        drawNextPairingElements();
                    }
                }
            } else {
                graphStructure.actualSelecterPosition = -1;
                solver->cleanWomanPrioritiesAfterWorkDone();
            }

            if (currentState == state_diff_pairs) {
                if (pairingId < graphStructure.allPossiblePairing.size() - 1)
                    pairingId++;
            }
        }

        if (keyEvent->key() == Qt::Key_Left) {
            if (currentState == state_diff_pairs) {
                if (pairingId > 0)
                    pairingId--;
            }
        }

        if (keyEvent->key() == Qt::Key_Up) {
            if (currentState == state_diff_pairs) {
                for (int i=pairingId+1; i<graphStructure.blockingPairs.size(); i++) {
                    if (graphStructure.blockingPairs[i].empty()) {
                        pairingId = i;
                        break;
                    }
                }
            }
        }

        if (keyEvent->key() == Qt::Key_Down) {
            if (currentState == state_diff_pairs) {
                for (int i=pairingId-1; i>0; i--) {
                    if (graphStructure.blockingPairs[i].empty()) {
                        pairingId = i;
                        break;
                    }
                }
            }
        }
    }
}

void Drawer::drawNextManPairing() {
    graphStructure.setPriorityselectorDatasToDefault();
    solver->solvePairingProblemNextStep();
    if (solver->sbsNextMan != solver->sbsProcessFinished) {
        while (solver->manWomanPairSolution[solver->sbsNextMan] != -1 && !solver->everyManHasPair()) {
            if (solver->sbsNextMan >= graphStructure.manList.size()) {
                solver->sbsNextMan = 0;
            }

            solver->sbsNextMan++;

            if (solver->sbsNextMan >= graphStructure.manList.size()) {
                solver->sbsNextMan = 0;
            }
        }
    }

    secondLeftArrowButtonPush = false;
}

void Drawer::drawNextPairingElements() {
    if (solver->sbsNextMan != solver->manWomanPairSolution.size()) {
        graphStructure.actualSelecterGender = "man";
        graphStructure.prioritizerPoint = graphStructure.manList[solver->sbsNextMan];
        graphStructure.actualSelecterPosition = graphStructure.positionOfXthElementInGenderbasedList(graphStructure.manList[solver->sbsNextMan], "man");

        for (int i=0; i < graphStructure.manPrioritiesList[solver->sbsNextMan].size(); i++) {
            graphStructure.actualPriorityPositions << graphStructure.womanList[graphStructure.manPrioritiesList[solver->sbsNextMan][i]];
        }

    }
    secondLeftArrowButtonPush = true;
}

void Drawer::actionInsertElement() {
    if (currentState == state_insert_man) {
        if (cursorpositionInBorder(cursorPosition)) {
            graphStructure.addMan(Knocking(cursorPosition));
        }
    } else if (currentState == state_insert_woman) {
        if (cursorpositionInBorder(cursorPosition)) {
            graphStructure.addWoman(Knocking(cursorPosition));
        }
    } else if (currentState == state_set_priorities) {
        actionSetPriority();
    }
}

void Drawer::actionSetPriority() {
    if (clickedOnElement(cursorPosition.x(), cursorPosition.y())) {
        //graphStructure.setPriorityselectorDatasToDefault();
        graphStructure.setPrioritiesForElement(indexOfClickedElement(cursorPosition.x(), cursorPosition.y()));
    }
}

void Drawer::actionInterruptPrioritySelection() {
    currentState = state_set_priorities;
    graphStructure.setPriorityselectorDatasToDefault();
}

bool Drawer::cursorpositionInBorder(QPoint CursorPosition) {
    return CursorPosition.x() > circleRadius/2 && CursorPosition.y() > circleRadius/2 && CursorPosition.x() < (this->width() - circleRadius/2) && CursorPosition.y() < (this->height() - circleRadius/2);
}

void Drawer::DrawEll(double x, double y, double circleRadius, QPainter* painter, int i) {
    DrawEll(x, y, circleRadius, painter, QString::number(i + 1));
}

void Drawer::DrawEll(double x, double y, double circleRadius, QPainter* painter, QString label) {
    DrawEll(x, y, circleRadius, painter);

    if (label.length() == 1) {
        painter->drawText(QPoint(x + circleRadius / 40 * 13, y + circleRadius / 4 * 3), label);
    } else {
        if (label.length() == 2)
        painter->drawText(QPoint(x + circleRadius / 40 * 7, y + circleRadius / 4 * 3), label);
        else {
            painter->drawText(QPoint(x + circleRadius / 13, y + circleRadius / 4 * 3), label);
        }
    }
}

void Drawer::DrawEll(double x, double y, double circleRadius, QPainter* painter) {
    QRectF rectangle(x, y, circleRadius, circleRadius);
    painter->drawEllipse(rectangle);
}

QPoint Drawer::Knocking(QPoint point) {

    int actualInsertionXPosition = point.x();
    int actualInsertionYPosition = point.y();
    QString tryThisDirection = "";

    if (graphStructure.insertedElementsNumber() == 0) {
        return point;
    }

    while (clickedOnElement(actualInsertionXPosition, actualInsertionYPosition)) {
        if (randInt(0,2) != 2) {
            if (randInt(0,1) == 0) {
                if (tryThisDirection != "move_right") {
                    actualInsertionXPosition -= circleRadius / 2;
                    tryThisDirection = "move_left";
                }

            } else {
                if (tryThisDirection != "move_left") {
                    actualInsertionXPosition += circleRadius / 2;
                    tryThisDirection = "move_right";
                }

            }
        } else {
            if (randInt(0,1) == 0) {
                if (tryThisDirection != "move_down") {
                    actualInsertionYPosition -= circleRadius / 2;
                    tryThisDirection = "move_up";
                }

            } else {
                if (tryThisDirection != "move_up") {
                    actualInsertionYPosition += circleRadius / 2;
                    tryThisDirection = "move_down";
                }

            }
        }
    }

    if (cursorpositionInBorder(QPoint(actualInsertionXPosition, actualInsertionYPosition))) {
        return QPoint(actualInsertionXPosition, actualInsertionYPosition);
    } else {
        return Knocking(point);
    }
}

bool Drawer::clickedOnElement(int actualXPosition, int actualYPosition) {
    QList<int> engagedXPositions = graphStructure.elementsXPosition;
    QList<int> engagedYPositions = graphStructure.elementsYPosition;
    int notDisturbedElementsNumber = 0;

    while (notDisturbedElementsNumber != graphStructure.insertedElementsNumber()) {
        for (int i=0; i<graphStructure.insertedElementsNumber(); i++) {
            if (actualXPosition >= engagedXPositions[i] - circleRadius*3/2 && actualXPosition <= engagedXPositions[i] + circleRadius/2 && actualYPosition >= engagedYPositions[i] - circleRadius*3/2 && actualYPosition <= engagedYPositions[i] + circleRadius/2) {
                return true;
            } else {
                notDisturbedElementsNumber++;
            }
        }
    }

    return false;
}

int Drawer::indexOfClickedElement(int actualXPosition, int actualYPosition) {
    QList<int> engagedXPositions = graphStructure.elementsXPosition;
    QList<int> engagedYPositions = graphStructure.elementsYPosition;

    for (int i=0; i<engagedXPositions.length() ;i++) {
        if (actualXPosition >= engagedXPositions[i] - circleRadius*3/2 && actualXPosition <= engagedXPositions[i] + circleRadius/2 && actualYPosition >= engagedYPositions[i] - circleRadius*3/2 && actualYPosition <= engagedYPositions[i] + circleRadius/2) {
            return i;
        }
    }

    return -1;
}

int Drawer::randInt(int low, int high) {
    return qrand() % ((high + 1) - low) + low;
}

void Drawer::resetAllData() {
    currentState = "";
    graphStructure.elementsXPosition.clear();
    graphStructure.elementsYPosition.clear();
    graphStructure.manList.clear();
    graphStructure.womanList.clear();
    graphStructure.manPrioritiesList.clear();
    graphStructure.womanPrioritiesList.clear();
    graphStructure.neighbours.clear();
    graphStructure.blockingPairs.clear();
    graphStructure.allPossiblePairing.clear();
    graphStructure.setPriorityselectorDatasToDefault();
    solver->sbsNextMan = 0;
    solver->preferencListReduction = false;
}

void Drawer::linkGraphElements(QPainter* painter) {
    if (!graphStructure.neighbours.empty()) {
        for (int i=0; i<graphStructure.neighbours.size(); i++) {
            for (int j=0; j<graphStructure.neighbours.size(); j++) {
                if (graphStructure.neighbours[i][j]) {
                    if (currentState != state_diff_pairs && graphStructure.allPossiblePairing.isEmpty())
                    painter->drawLine(QPoint(graphStructure.elementsXPosition[i], graphStructure.elementsYPosition[i]),QPoint(graphStructure.elementsXPosition[j], graphStructure.elementsYPosition[j]));
                }
            }
        }
    }
}

void Drawer::drawManElements(QPainter* painter) {
    for (int i=0; i< graphStructure.manList.length();i++) {
        if (currentState == state_solution_step_by_step && solver->manWomanPairSolution[i] == solver->statusWillBeLonely) {
            painter->setBrush(QBrush("#990099"));
        } else {
            painter->setBrush(QBrush("#2BB9FF"));
        }
        DrawEll(graphStructure.elementsXPosition[graphStructure.manList[i]]-circleRadius/2, graphStructure.elementsYPosition[graphStructure.manList[i]]-circleRadius/2, circleRadius, painter, i);
    }
}

void Drawer::drawWomanElements(QPainter* painter) {
    for (int i=0; i< graphStructure.womanList.length();i++) {
        if (currentState == state_solution_step_by_step && graphStructure.womanPrioritiesList[i].isEmpty()) {
            painter->setBrush(QBrush("#990099"));
        } else {
            painter->setBrush(QBrush("#E41818"));
        }
        DrawEll(graphStructure.elementsXPosition[graphStructure.womanList[i]]-circleRadius/2, graphStructure.elementsYPosition[graphStructure.womanList[i]]-circleRadius/2, circleRadius, painter, RelabelIntegerNumberOfWomen(i));
    }
}

void Drawer::drawPrioritySelecterElementAndPrioritizedElements(QPainter* painter) {

    if (graphStructure.selectingPriorities()) {

        painter->setBrush(QBrush("#00FF44"));
        DrawEll(graphStructure.elementsXPosition[graphStructure.prioritizerPoint]-circleRadius/2, graphStructure.elementsYPosition[graphStructure.prioritizerPoint]-circleRadius/2, circleRadius, painter);

        painter->setBrush(QBrush("#FFFF00"));
        for (int i=0; i < graphStructure.actualPriorityPositions.length(); i++) {
            DrawEll(graphStructure.elementsXPosition[graphStructure.actualPriorityPositions[i]]-circleRadius/2, graphStructure.elementsYPosition[graphStructure.actualPriorityPositions[i]]-circleRadius/2, circleRadius, painter, i);
        }
    }
}

void Drawer::setState(QString state) {
    currentState = state;

    if (state == state_set_priorities) {
        graphStructure.initNeighboursVector();
    }
}

void Drawer::solveTheProblem() {
    setState(state_solution_step_by_step);
    solver->addActualGraphStructure(&graphStructure);
    solver->leaveUnnecessaryElementsFromPrioLists();
    solver->solvePairingProblem();
    solver->cleanWomanPrioritiesAfterWorkDone();
    graphStructure.debugManWomanPriorities();
}

void Drawer::solveTheProblemStepByStep() {
    solver->addActualGraphStructure(&graphStructure);
    solver->leaveUnnecessaryElementsFromPrioLists();
    setState(state_solution_step_by_step);
    solver->initManWomanPairSolution();
}

void Drawer::initSetOfLabels() {
    labelLettersForWomen << "A";
    labelLettersForWomen << "B";
    labelLettersForWomen << "C";
    labelLettersForWomen << "D";
    labelLettersForWomen << "E";
    labelLettersForWomen << "F";
    labelLettersForWomen << "G";
    labelLettersForWomen << "H";
    labelLettersForWomen << "I";
    labelLettersForWomen << "J";
}

QString Drawer::RelabelIntegerNumberOfWomen(int index) {
    QString newLabel = QString::number(index);

    for (int i=0; i<10; i++) {
        newLabel.replace(QString::number(i), labelLettersForWomen[i]);
    }

    return newLabel;
}

void Drawer::generateBlockingEdgesStepByStep(){
    graphStructure.generateAllPossiblePairing();
    solver->addActualGraphStructure(&graphStructure);
    solver->generateAllBlockingPairs();
    pairingId = 0;
}

void Drawer::drawActualTestPairing(QPainter* painter) {


    if ( currentState == state_diff_pairs && !graphStructure.allPossiblePairing.isEmpty()) {

        for(int indexOfPair=0; indexOfPair < graphStructure.allPossiblePairing[pairingId].size(); indexOfPair++) {
            //painter->setPen(QPen(QColor(Qt::green), 2));
            painter->drawLine(QPoint(graphStructure.elementsXPosition[graphStructure.manList[indexOfPair]], graphStructure.elementsYPosition[graphStructure.manList[indexOfPair]]),
                    QPoint(graphStructure.elementsXPosition[graphStructure.womanList[graphStructure.allPossiblePairing[pairingId][indexOfPair]]],
                            graphStructure.elementsYPosition[graphStructure.womanList[graphStructure.allPossiblePairing[pairingId][indexOfPair]]]));
        }

        painter->setPen(QPen(QColor(Qt::red), 2));
        for (int i=0; i<graphStructure.blockingPairs[pairingId].size(); i++) {
            painter->drawLine(QPoint(graphStructure.elementsXPosition[graphStructure.manList[graphStructure.blockingPairs[pairingId][i][0]]],
                                     graphStructure.elementsYPosition[graphStructure.manList[graphStructure.blockingPairs[pairingId][i][0]]]),
                              QPoint(graphStructure.elementsXPosition[graphStructure.womanList[graphStructure.blockingPairs[pairingId][i][1]]],
                                     graphStructure.elementsYPosition[graphStructure.womanList[graphStructure.blockingPairs[pairingId][i][1]]]));
        }

        painter->setPen(QPen(QColor(Qt::black), 2));

        painter->drawText(QPoint(this->width() -circleRadius/2 - circleRadius/3 * (QString::number(pairingId + 1).length() + QString::number(graphStructure.allPossiblePairing.size()).length()),
                                 circleRadius/2), QString::number(pairingId + 1) + "/" + QString::number(graphStructure.allPossiblePairing.size()));
    }
}

void Drawer::drawPriorityOfMouseoverElement(QPainter* painter) {
    if (clickedOnElement(cursorPosition.x(), cursorPosition.y())) {

        painter->setBrush(QBrush("#FFFF00"));
        int clickedElementIndex = indexOfClickedElement(cursorPosition.x(), cursorPosition.y());
        QList<int> elementsToDraw = graphStructure.getPreferenceListElementsOfGenderlessElement(clickedElementIndex);

        for (int i=0; i<elementsToDraw.size(); i++) {
            DrawEll(graphStructure.elementsXPosition[elementsToDraw[i]]-circleRadius/2, graphStructure.elementsYPosition[elementsToDraw[i]]-circleRadius/2, circleRadius, painter, i);
        }
    }
}
