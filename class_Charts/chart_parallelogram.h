#ifndef CHART_PARALLELOGRAM_H
#define CHART_PARALLELOGRAM_H

#include "chart_base.h"

/**
 * @class chart_parallelogram
 * @brief Represents a parallelogram shape for drawing.
 */
class Chart_Parallelogram : public Chart_Base
{
public:
    Chart_Parallelogram(QWidget *parent = nullptr, PaintChartType type = PaintChartType::PARALLELOGRAM) : Chart_Base(parent,type,false,true){}
    Chart_Parallelogram(Chart_Parallelogram &cr):Chart_Base(cr){}
    Chart_Parallelogram( int x1, int y1, int x2, int y2, QWidget *parent = nullptr,PaintChartType type = PaintChartType::PARALLELOGRAM) : Chart_Base(x1,y1,x2,y2,parent,type){}
    ~Chart_Parallelogram(){}

private:
    /**
     * @brief Paints the parallelogram on the provided QPainter.
     * @param p The QPainter used for drawing.
     */
    virtual void paintChart(QPainter &p) ;
    virtual void updateMagPointInfo();
};

#endif // CHART_PARALLELOGRAM_H
