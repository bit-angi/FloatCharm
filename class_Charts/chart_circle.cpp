#include"chart_circle.h"


void Chart_Circle::paintChart(QPainter &p)
{
    QPen tmp = p.pen();  // 保存当前的画笔
    p.setPen(paintChartDrawPen);  // 设置用于绘制的画笔

    int sx = paintStart.rx(), sy = paintStart.ry();
    int ex = paintEnd.rx(), ey = paintEnd.ry();

    // 计算圆形的中心点和半径
    int midx = (sx + ex) >> 1;
    int midy = (sy + ey) >> 1;
    int radius = qMin(abs(ex - sx), abs(ey - sy)) >> 1;  // 半径取宽和高的最小值的一半

    if (graphPath) delete graphPath;  // 删除旧的 QPainterPath
    graphPath = new QPainterPath;

    // 创建圆形的路径
    graphPath->addEllipse(midx - radius, midy - radius, radius * 2, radius * 2);

    // 填充圆形
    p.fillPath(*graphPath, paintChartFillPen);
    // 绘制圆形的边框
    p.drawPath(*graphPath);

    p.setPen(tmp);  // 恢复原来的画笔
}

void Chart_Circle::updateMagPointInfo()
{
    int sx = paintStart.rx(), sy = paintStart.ry();
    int ex = paintEnd.rx(), ey = paintEnd.ry();

    // 计算圆形的中心点和半径
    int midx = (sx + ex) >> 1;
    int midy = (sy + ey) >> 1;
    int radius = qMin(abs(ex - sx), abs(ey - sy)) >> 1;  // 半径取宽和高的最小值的一半

    // 设置磁力点的位置和方向
    magPoint.i_point[0]->setX(midx);  // 北（上）方
    magPoint.i_point[0]->setY(midy - radius);
    magPoint.i_point[0]->setRotate(ORIENTION::NORTH);

    magPoint.i_point[1]->setX(midx + radius);  // 东（右）方
    magPoint.i_point[1]->setY(midy);
    magPoint.i_point[1]->setRotate(ORIENTION::EAST);

    magPoint.i_point[2]->setX(midx);  // 南（下）方
    magPoint.i_point[2]->setY(midy + radius);
    magPoint.i_point[2]->setRotate(ORIENTION::SOUTH);

    magPoint.i_point[3]->setX(midx - radius);  // 西（左）方
    magPoint.i_point[3]->setY(midy);
    magPoint.i_point[3]->setRotate(ORIENTION::WEST);
}



