#include "charwidget.h"
#include "flowchart.h"
#include "ui_charwidget.h"
#include "QScrollBar"
#include <QGraphicsView>
#include <QPalette>
CharWidget::CharWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CharWidget)
{
    ui->setupUi(this);
    this->minGap = 4;
    this->grinOn = true;
    this->maxGap = 14;
    this->gap = (this->minGap + this->maxGap) / 2;
    this->startX = this->width() / 2;
    this->startY = this->height() / 2;
    this->lightPen = QPen(QColor(222, 222, 222));
    this->darkPen = QPen(QColor(222, 222, 222));
    this->darkPen.setWidth(2);

    this->setBackgroundColor();
}

CharWidget::~CharWidget()
{
    delete ui;
}

void CharWidget::wheelEvent(QWheelEvent *event)
{
    QScrollBar *scrollBar;
    int scrollAmount = 0 ;
    if ((event->modifiers() == Qt::ShiftModifier)) {
        scrollBar = ui->scrollArea->horizontalScrollBar();
        qDebug() << "shiftmod";
        scrollAmount = event->angleDelta().y() / 8;
    }
    else {
        scrollBar = ui->scrollArea->verticalScrollBar();
        scrollAmount = event->angleDelta().y() / 8;
    }
    scrollBar->setValue(scrollBar->value() - scrollAmount);
    event->accept();
}

void CharWidget::setBackgroundColor() {
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(250, 250, 250));
    this->setPalette(palette);
    this->setAutoFillBackground(true);
}

void CharWidget::drawRowLines(QPainter *painter) {
    int lineCount = 0;
    float biggerY = this->startY;
    float smallerY = this->startY;

    painter->setPen(this->darkPen);

    while (true) {
        painter->drawLine(QPointF(0.0, biggerY), QPointF(this->width(), biggerY));
        painter->drawLine(QPointF(0.0, smallerY), QPointF(this->width(), smallerY));

        biggerY += this->gap;
        smallerY -= this->gap;
        if (smallerY <= 0 || biggerY >= this->height()) {
            break;
        }

        // 每间隔一定数量的线，就画一条粗一点的横线
        lineCount += 1;
        if (lineCount == 10) {
            painter->setPen(this->darkPen);
            lineCount = 0;
        }
        else {
            painter->setPen(this->lightPen);
        }
    }

}

void CharWidget::drawColLines(QPainter *painter) {
    int lineCount = 0;
    float biggerX = this->startX;
    float smallerX = this->startX;

    painter->setPen(this->darkPen);

    while (true) {
        painter->drawLine(QPointF(biggerX, 0.0), QPointF(biggerX, this->height()));
        painter->drawLine(QPointF(smallerX, 0.0), QPointF(smallerX, this->height()));

        biggerX += this->gap;
        smallerX -= this->gap;
        if (smallerX <= 0 || biggerX >= this->width()) {
            break;
        }

        // 每间隔一定数量的线，就画一条粗一点的竖线
        lineCount += 1;
        if (lineCount == 10) {
            painter->setPen(this->darkPen);
            lineCount = 0;
        }
        else {
            painter->setPen(this->lightPen);
        }
    }

}

void CharWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    if (this->grinOn) {
        this->drawRowLines(&painter);
        this->drawColLines(&painter);
        update();
        this->ui->widget->update();
    }
}

void CharWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    this->startX = this->width() / 2;
    this->startY = this->height() / 2;
    this->update();
}
