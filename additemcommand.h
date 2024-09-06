#ifndef ADDITEMCOMMAND_H
#define ADDITEMCOMMAND_H

#include "flowchart.h"

#include <QPushButton>
#include <QUndoCommand>
#include <QVBoxLayout>
#include <class_Charts/chart_base.h>
class AddItemCommand : public QUndoCommand
{
public:
    AddItemCommand(Chart_Base *chartBase,FlowChart* flowchart);

    void undo() override;
    void redo() override;

private:
    Chart_Base* chartBase ;
    FlowChart* flowchart;
};

#endif // ADDITEMCOMMAND_H
