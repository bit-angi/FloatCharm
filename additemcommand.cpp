#include "additemcommand.h"

AddItemCommand::AddItemCommand(Chart_Base *chartBase,FlowChart* flowchart)
{
    this->chartBase = chartBase;
    this->flowchart = flowchart;
}

void AddItemCommand::undo() {
    this->chartBase->hide();
}

void AddItemCommand::redo() {
    this->chartBase->show();
}
