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

//GraphStructure graphStructure = new GraphStructure();

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
        CursorPosition = this->mapFromGlobal(QCursor::pos());
    } else {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                if (cursorpositionInBorder(CursorPosition)) {
                    qDebug() << "cliecked inside the border";
                    if (operationState == insert_man) {
                        graphStructure.addMan(CursorPosition.x(), CursorPosition.y());
                    } else if (operationState == insert_woman) {
                        graphStructure.addWoman(CursorPosition.x(), CursorPosition.y());
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
