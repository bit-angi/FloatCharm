#ifndef MOVEITEMCOMMAND_H
#define MOVEITEMCOMMAND_H

#include "flowchart.h"

#include <QPushButton>
#include <QUndoCommand>
#include <QVBoxLayout>
#include <class_Charts/chart_base.h>
class MoveItemCommand : public QUndoCommand
{
public:
    MoveItemCommand(Chart_Base *chartBase,FlowChart* flowchart,int x , int y );

    void undo() override;
    void redo() override;

public :
    Chart_Base* chartBase ;
    int oldX , oldY;
    int newX, newY;
    FlowChart* flowchart;
};

#endif // MOVEITEMCOMMAND_H
