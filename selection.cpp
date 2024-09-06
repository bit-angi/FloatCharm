#include "selection.h"
#include "qpainter.h"
#include "ui_selection.h"

#include <QPaintEvent>

Selection::Selection(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Selection)
{
    ui->setupUi(this);
}

Selection::~Selection()
{
    delete ui;
}

void Selection::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 绘制背景
    // painter.fillRect(rect(), Qt::white);
    event->accept();
}


