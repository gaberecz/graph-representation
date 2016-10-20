#include "drawer.h"

Drawer::Drawer(QWidget *parent) :
    QWidget(parent)
{
    installEventFilter(this);
    setMouseTracking(true);
    insert_man = "insert_man";
    insert_woman = "insert_woman";
    operationState = "";

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(5);

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    radius = 40;
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
    painter.drawRect(radius/2,radius/2,this->width()-radius,this->height()-radius);

    painter.setBrush(QBrush("#2BB9FF"));

    for (int i=0; i< graphStructure.men.length();i++) {
        DrawEll(graphStructure.elementsXPosition[graphStructure.men[i]]-radius/2, graphStructure.elementsYPosition[graphStructure.men[i]]-radius/2, radius, &painter, i);
    }

    painter.setBrush(QBrush("#E41818"));

    for (int i=0; i< graphStructure.women.length();i++) {
        DrawEll(graphStructure.elementsXPosition[graphStructure.women[i]]-radius/2, graphStructure.elementsYPosition[graphStructure.women[i]]-radius/2, radius, &painter, i);
    }
}

bool Drawer::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QMouseEvent::MouseMove)
    {
        cursorPosition = this->mapFromGlobal(QCursor::pos());
    } else {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                if (cursorpositionInBorder(cursorPosition)) {
                    qDebug() << "cliecked inside the border";
                    if (operationState == insert_man) {
                        graphStructure.addMan(Knocking(cursorPosition));
                    } else if (operationState == insert_woman) {
                        graphStructure.addWoman(Knocking(cursorPosition));
                    }
                }
            }
        }
    }
}

bool Drawer::cursorpositionInBorder(QPoint CursorPosition) {
    return CursorPosition.x() > radius/2 && CursorPosition.y() > radius/2 && CursorPosition.x() < (this->width() - radius/2) && CursorPosition.y() < (this->height() - radius/2);
}

void Drawer::DrawEll(double x, double y, double radius, QPainter* painter, int i) {
    QRectF rectangle(x, y, radius, radius);
    painter->drawEllipse(rectangle);

    if (i < 9) {
        painter->drawText(QPoint(x + radius / 40 * 13, y + radius / 4 * 3), QString::number(i + 1));
    } else {
        if (i<99)
        painter->drawText(QPoint(x + radius / 40 * 7, y + radius / 4 * 3), QString::number(i + 1));
        else {
            QFont font = painter->font();
            font.setPointSize(16);
            painter->setFont(font);
            painter->drawText(QPoint(x + radius / 13, y + radius / 4 * 3), QString::number(i + 1));
            font.setPointSize(18);
            painter->setFont(font);
        }
    }
}

QPoint Drawer::Knocking(QPoint point) {
    QList<int> engagedXPositions = graphStructure.elementsXPosition;
    QList<int> engagedYPositions = graphStructure.elementsYPosition;

    int actualXPosition = point.x();
    int actualYPosition = point.y();
    QString tryThisDirection = "";
    int Good = 0;

    if (engagedXPositions.length() == 0) {
        return point;
    }

    while (Good <= (engagedXPositions.length())) {
        for (int i=0; i<engagedXPositions.length() ;i++) {
            if (actualXPosition >= engagedXPositions[i] - radius && actualXPosition <= engagedXPositions[i] + radius && actualYPosition >= engagedYPositions[i] - radius && actualYPosition <= engagedYPositions[i] + radius) {
                while (qPow(engagedXPositions[i] - actualXPosition, 2) + qPow(engagedYPositions[i] - actualYPosition, 2) <= qPow( 1.5 * radius ,2)) {

                    if (randInt(0,2) != 2) {
                        if (randInt(0,1) == 0) {
                            if (tryThisDirection != "move_right") {
                                actualXPosition -= 25;
                                tryThisDirection = "move_left";

                            }

                        } else {
                            if (tryThisDirection != "move_left") {
                                actualXPosition += 25;
                                tryThisDirection = "move_right";
                            }

                        }
                    } else {
                        if (randInt(0,1) == 0) {
                            if (tryThisDirection != "move_down") {
                                actualYPosition -= 25;
                                tryThisDirection = "move_up";
                            }

                        } else {
                            if (tryThisDirection != "move_up") {
                                actualYPosition += 25;
                                tryThisDirection = "move_down";
                            }

                        }
                    }
                }

                Good = 0;
            } else {
                Good++;
            }
        }
    }

    return QPoint(actualXPosition, actualYPosition);
}

int Drawer::randInt(int low, int high) {
    return qrand() % ((high + 1) - low) + low;
}
