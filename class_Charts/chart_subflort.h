#ifndef CHART_SUBFLORT_H
#define CHART_SUBFLORT_H

#include "chart_base.h"


class Chart_Subflort : public Chart_Base
{
private:
    virtual void paintChart(QPainter & p);

public:
    Chart_Subflort(QWidget *parent = nullptr, PaintChartType type = PaintChartType::SUBFLORT) : Chart_Base(parent,type,false,true){}
    Chart_Subflort(Chart_Subflort &cr):Chart_Base(cr){}
    Chart_Subflort(int x1, int y1, int x2, int y2, QWidget *parent = nullptr, PaintChartType type = PaintChartType::SUBFLORT) : Chart_Base(x1,y1,x2,y2,parent,type){}
    ~Chart_Subflort(){}
};

#endif // CHART_SUBFLORT_H
