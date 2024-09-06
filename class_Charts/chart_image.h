#ifndef CHART_IMAGE_H
#define CHART_IMAGE_H
#include "chart_base.h"

class Chart_Image : public Chart_Base
{
private:
    virtual void paintChart(QPainter & p);
    virtual void updateMagPointInfo();

public:
    Chart_Image(QWidget *parent = nullptr, PaintChartType type = PaintChartType::RECT) : Chart_Base(parent,type,false,true,8){}
    Chart_Image(Chart_Image &cr):Chart_Base(cr){}
    Chart_Image( int x1, int y1, int x2, int y2, QWidget *parent = nullptr,PaintChartType type = PaintChartType::RECT) : Chart_Base(x1,y1,x2,y2,parent,type){}
    ~Chart_Image(){}
    QImage image;

};

#endif // CHART_RECT_H
