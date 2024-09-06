#ifndef CHART_TRIANGLE_H
#define CHART_TRIANGLE_H

#include "chart_base.h"

class Chart_Triangle:public Chart_Base
{
public:
    Chart_Triangle(QWidget *parent = nullptr, PaintChartType type = PaintChartType::TRIANGLE) : Chart_Base(parent,type,false,true){}
    Chart_Triangle(Chart_Triangle &cr):Chart_Base(cr){}
    Chart_Triangle( int x1, int y1, int x2, int y2, QWidget *parent = nullptr,PaintChartType type = PaintChartType::TRIANGLE) : Chart_Base(x1,y1,x2,y2,parent,type){}
    ~Chart_Triangle(){}

private:

    virtual void paintChart(QPainter &p) ;
    virtual void updateMagPointInfo();
};

#endif // CHART_PARALLELOGRAM_H
