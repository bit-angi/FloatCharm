#include "chart_capsule.h"

void Chart_Capsule::paintChart(QPainter &p)
{
    QPen tmp = p.pen();  // 保存当前的画笔
    p.setPen(paintChartDrawPen);  // 设置用于绘制的画笔

    int sx = paintStart.rx(), sy = paintStart.ry();
    int ex = paintEnd.rx(), ey = paintEnd.ry();

    int width = abs(ex - sx);
    int height = abs(ey - sy);
    int radius = height / 2;  // 半径取高的一半

    if (graphPath) delete graphPath;  // 删除旧的 QPainterPath
    graphPath = new QPainterPath;

    // 创建胶囊矩形的路径
    graphPath->moveTo(sx + radius, sy);
    graphPath->lineTo(ex - radius, sy);  // 上边线
    graphPath->arcTo(ex - height, sy, height, height, 90, -180);  // 右半圆
    graphPath->lineTo(sx + radius, ey);  // 下边线
    graphPath->arcTo(sx, sy, height, height, 270, -180);  // 左半圆

    // 填充胶囊矩形
    p.fillPath(*graphPath, paintChartFillPen);
    // 绘制胶囊矩形的边框
    p.drawPath(*graphPath);

    p.setPen(tmp);  // 恢复原来的画笔
}

void Chart_Capsule::updateMagPointInfo()
{
    int sx = paintStart.rx(), sy = paintStart.ry();
    int ex = paintEnd.rx(), ey = paintEnd.ry();

    int width = abs(ex - sx);
    int height = abs(ey - sy);
    int radius = height / 2;  // 半径取高的一半

    // 计算胶囊矩形的中心点和边缘点
    int midx = (sx + ex) >> 1;
    int midy = (sy + ey) >> 1;

    // 计算顶部、底部和两侧的位置
    int top = sy;
    int bottom = ey;
    int left = sx;
    int right = ex;

    // 设置磁力点的位置和方向
    magPoint.i_point[0]->setX(midx);         // 顶部中心
    magPoint.i_point[0]->setY(top);
    magPoint.i_point[0]->setRotate(ORIENTION::NORTH);

    magPoint.i_point[1]->setX(right);        // 右侧中心
    magPoint.i_point[1]->setY(midy);
    magPoint.i_point[1]->setRotate(ORIENTION::EAST);

    magPoint.i_point[2]->setX(midx);         // 底部中心
    magPoint.i_point[2]->setY(bottom);
    magPoint.i_point[2]->setRotate(ORIENTION::SOUTH);

    magPoint.i_point[3]->setX(left);         // 左侧中心
    magPoint.i_point[3]->setY(midy);
    magPoint.i_point[3]->setRotate(ORIENTION::WEST);
}



