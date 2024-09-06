#include "moveitemcommand.h"
#include "class_Charts/chart_base.h"

MoveItemCommand::MoveItemCommand(Chart_Base *chartBase,FlowChart* flowchart,int x, int y) {
    this->chartBase = chartBase;
    this->flowchart = flowchart;
    this->oldX = x ;
    this->oldY = y ;
    this->newX = chartBase->pos().x();
    this->newY = chartBase->pos().y();
}

void MoveItemCommand::undo()
{
    this->newX = chartBase->pos().x();
    this->newY = chartBase->pos().y();
    this->chartBase->move(QPoint(oldX,oldY));
    // chartBase->updateWidgetPosInof();
    chartBase->updateMagPointLine();
}

void MoveItemCommand::redo() {
    this->chartBase->move(QPoint(newX,newY));
    // chartBase->updateWidgetPosInof();
    chartBase->updateMagPointLine();
}
