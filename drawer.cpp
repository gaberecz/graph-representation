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
    state_solution_step_by_step = "solution_step_by_step";
    currentState = "";
    secondLeftArrowButtonPush = false;

    QTimer* redrawTimer = new QTimer(this);
    connect(redrawTimer, SIGNAL(timeout()), this, SLOT(update()));
    redrawTimer->start(5);

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    circleRadius = 40;
}

void Drawer::paintEvent(QPaintEvent *event) {

    QPen pen;
    pen.setWidth(2);
    QPainter painter(this);
    painter.setPen(pen);
    QFont font = painter.font();
    font.setPointSize(18);
    painter.setFont(font);

    painter.setBrush(QBrush("#cccbc9"));
    painter.drawRect(0, 0, this->width(), this->height());

    linkGraphElements(&painter);
    drawManElements(&painter);
    drawWomanElements(&painter);
    drawPrioritySelecterElementAndPrioritizedElements(&painter);
}

bool Drawer::eventFilter(QObject *obj, QEvent *event)
{

    if (event->type() == QMouseEvent::MouseMove) {
        cursorPosition = this->mapFromGlobal(QCursor::pos());
    } else {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                if (cursorpositionInBorder(cursorPosition)) {
                    if (currentState == state_insert_man) {
                        graphStructure.addMan(Knocking(cursorPosition));
                    } else if (currentState == state_insert_woman) {
                        graphStructure.addWoman(Knocking(cursorPosition));
                    } else if (currentState == state_set_priorities) {
                        if (clickedOnElement(cursorPosition.x(), cursorPosition.y())) {
                            graphStructure.setPriorityselectorDatasToDefault();
                            graphStructure.setPrioritiesForElement(indexOfClickedElement(cursorPosition));
                        }
                    }
                }
            } else if (mouseEvent->button() == Qt::RightButton) {
                if (currentState.contains(state_set_priorities)) {
                    currentState = state_set_priorities;
                    graphStructure.setPriorityselectorDatasToDefault();
                }
            }
        }
    }

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Right) {
            if (solver->sbsNextMan != -2) {
                if (currentState == state_solution_step_by_step) {
                    if (secondLeftArrowButtonPush) {
                        graphStructure.setPriorityselectorDatasToDefault();
                        solver->solvePairingProblemNextStep();
                        if (solver->sbsNextMan != -2) {
                            while (solver->manWomanPairSolution[solver->sbsNextMan] > -1) {
                                solver->sbsNextMan++;
                                if (solver->sbsNextMan == graphStructure.manList.size()) {
                                    solver->sbsNextMan = 0;
                                }
                                qDebug() <<solver->sbsNextMan;
                            }

                            qDebug() <<solver->sbsNextMan;
                        }

                        secondLeftArrowButtonPush = false;
                    } else {
                        if (solver->sbsNextMan != solver->manWomanPairSolution.size()) {
                            graphStructure.actualSelecterGender = "man";
                            graphStructure.prioritizerPoint = solver->sbsNextMan;
                            graphStructure.actualSelecterPosition = graphStructure.positionOfXthElementInGenderbasedList(solver->sbsNextMan, "man");
                            for (int i=0; i < graphStructure.manPrioritiesList[solver->sbsNextMan].size(); i++) {
                                graphStructure.actualPriorityPositions << graphStructure.womanList[graphStructure.manPrioritiesList[solver->sbsNextMan][i]];
                            }

                            secondLeftArrowButtonPush = true;
                        }
                    }
                }
            } else {
                solver->cleanWomanPrioritiesAfterWorkDone();
            }
        }
    }
}

bool Drawer::cursorpositionInBorder(QPoint CursorPosition) {
    return CursorPosition.x() > circleRadius/2 && CursorPosition.y() > circleRadius/2 && CursorPosition.x() < (this->width() - circleRadius/2) && CursorPosition.y() < (this->height() - circleRadius/2);
}

void Drawer::DrawEll(double x, double y, double circleRadius, QPainter* painter, int i) {
    DrawEll(x, y, circleRadius, painter);

    if (i < 9) {
        painter->drawText(QPoint(x + circleRadius / 40 * 13, y + circleRadius / 4 * 3), QString::number(i + 1));
    } else {
        if (i<99)
        painter->drawText(QPoint(x + circleRadius / 40 * 7, y + circleRadius / 4 * 3), QString::number(i + 1));
        else {
            QFont font = painter->font();
            font.setPointSize(16);
            painter->setFont(font);
            painter->drawText(QPoint(x + circleRadius / 13, y + circleRadius / 4 * 3), QString::number(i + 1));
            font.setPointSize(18);
            painter->setFont(font);
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
            if (actualXPosition >= engagedXPositions[i] - circleRadius && actualXPosition <= engagedXPositions[i] + circleRadius && actualYPosition >= engagedYPositions[i] - circleRadius && actualYPosition <= engagedYPositions[i] + circleRadius) {
                return true;
            } else {
                notDisturbedElementsNumber++;
            }
        }
    }

    return false;
}

int Drawer::indexOfClickedElement(QPoint actualPosition) {
    int actualXPosition = actualPosition.x();
    int actualYPosition = actualPosition.y();
    QList<int> engagedXPositions = graphStructure.elementsXPosition;
    QList<int> engagedYPositions = graphStructure.elementsYPosition;
    int positionOfPoint = -1;

    for (int i=0; i<engagedXPositions.length() ;i++) {
        if (actualXPosition >= engagedXPositions[i] - circleRadius && actualXPosition <= engagedXPositions[i] + circleRadius && actualYPosition >= engagedYPositions[i] - circleRadius && actualYPosition <= engagedYPositions[i] + circleRadius) {
            return i;
        }
    }
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
    graphStructure.setPriorityselectorDatasToDefault();
    solver->sbsNextMan = 0;
}

void Drawer::linkGraphElements(QPainter* painter) {
    if (!graphStructure.neighbours.empty()) {
        for (int i=0; i<graphStructure.neighbours.size(); i++) {
            for (int j=0; j<graphStructure.neighbours.size(); j++) {
                if (graphStructure.neighbours[i][j]) {
                    painter->drawLine(QPoint(graphStructure.elementsXPosition[i], graphStructure.elementsYPosition[i]),QPoint(graphStructure.elementsXPosition[j], graphStructure.elementsYPosition[j]));
                }
            }
        }
    }
}

void Drawer::drawManElements(QPainter* painter) {
    for (int i=0; i< graphStructure.manList.length();i++) {
        if (currentState == state_solution_step_by_step && solver->manWomanPairSolution[i] == -2) {
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
        DrawEll(graphStructure.elementsXPosition[graphStructure.womanList[i]]-circleRadius/2, graphStructure.elementsYPosition[graphStructure.womanList[i]]-circleRadius/2, circleRadius, painter, i);
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

void Drawer::solveTheProblemStepByStep() {
    currentState = state_solution_step_by_step;
    solver->initManWomanPairSolution();
}
