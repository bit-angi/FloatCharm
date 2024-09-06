#include "chart_parallelogram.h"

void Chart_Parallelogram::paintChart(QPainter &p)
{
    QPen tmp = p.pen(); // 保存当前的笔
    p.setPen(paintChartDrawPen); // 设置新的笔用于绘制

    // 获取起始点和结束点坐标
    int sx = paintStart.rx(), sy = paintStart.ry();
    int ex = paintEnd.rx(), ey = paintEnd.ry();

    // 计算平行四边形的顶点坐标
    int dx = (ex - sx) *0.7; // x 方向的距离
    int dy = (ey - sy) ; // y 方向的距离
    int offsetX = (ex - sx) *0.3; // 平行四边形的偏移量（可以根据需要调整）
    int offsetY = 0; // 平行四边形的偏移量（可以根据需要调整）

    if (graphPath) delete graphPath; // 删除旧的 QPainterPath
    graphPath = new QPainterPath;

    // 创建平行四边形的路径
    graphPath->moveTo(sx, sy); // 起点
    graphPath->lineTo(sx + dx, sy ); // 上右点
    graphPath->lineTo(sx + dx + offsetX, sy + dy); // 下右点
    graphPath->lineTo(sx + offsetX, sy + dy); // 下左点
    graphPath->closeSubpath(); // 关闭路径

    // 填充平行四边形
    p.fillPath(*graphPath, paintChartFillPen);
    // 绘制平行四边形的边框
    p.drawPath(*graphPath);

    p.setPen(tmp); // 恢复原来的笔
}

void Chart_Parallelogram::updateMagPointInfo()
{
    int x1 = paintStart.rx(), y1 = paintStart.ry();
    int x2 = paintEnd.rx(), y2 = paintEnd.ry();


    int dx = (x2 - x1) *0.7; // x 方向的距离
    int dy = (y2-y1) ; // y 方向的距离
    int offsetX = (x2 - x1) *0.3; // 平行四边形的偏移量（可以根据需要调整）
    int offsetY = 0; // 平行四边形的偏移量（可以根据需要调整）

    // 设置磁力点的位置和方向
    magPoint.i_point[0]->setX(x1);
    magPoint.i_point[0]->setY(y1);
    magPoint.i_point[0]->setRotate(ORIENTION::NORTHWEST);

    magPoint.i_point[1]->setX(x1 + dx);
    magPoint.i_point[1]->setY(y1);
    magPoint.i_point[1]->setRotate(ORIENTION::NORTHEAST);

    magPoint.i_point[2]->setX(x2);
    magPoint.i_point[2]->setY(y2);
    magPoint.i_point[2]->setRotate(ORIENTION::SOUTHEAST);

    magPoint.i_point[3]->setX(x2-dx);
    magPoint.i_point[3]->setY(y2);
    magPoint.i_point[3]->setRotate(ORIENTION::SOUTHWEST);
}


