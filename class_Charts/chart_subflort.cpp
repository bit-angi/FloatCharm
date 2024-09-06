#include "chart_subflort.h"

void Chart_Subflort::paintChart(QPainter &p)
{
    QPen tmp = p.pen();  // 保存当前的画笔
    p.setPen(paintChartDrawPen);  // 设置用于绘制的画笔

    int sx = paintStart.rx(), sy = paintStart.ry();
    int ex = paintEnd.rx(), ey = paintEnd.ry();

    int width = abs(ex - sx);
    int height = abs(ey - sy);
    int radius = qMin(width, height) / 2;  // 半径取宽和高中较小的一半


    if (graphPath) delete graphPath;  // 删除旧的 QPainterPath
    graphPath = new QPainterPath;

    graphPath->moveTo(sx,sy);
    graphPath->lineTo(sx,ey);
    graphPath->lineTo(sx+width*0.1,ey);
    graphPath->lineTo(sx+width*0.1,sy);
    graphPath->lineTo(sx,sy);

    graphPath->moveTo(sx+width*0.1,sy);
    graphPath->lineTo(sx+width*0.9,sy);
    graphPath->lineTo(sx+width*0.9,ey);
    graphPath->lineTo(sx+width*0.1,ey);


    graphPath->moveTo(sx+width*0.9,ey);
    graphPath->lineTo(ex,ey);
    graphPath->lineTo(ex,sy);
    graphPath->lineTo(sx+width*0.9,sy);
    // 填充胶囊矩形
    p.fillPath(*graphPath, paintChartFillPen);
    // 绘制胶囊矩形的边框
    p.drawPath(*graphPath);
}
