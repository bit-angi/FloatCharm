#include "chart_triangle.h"

void Chart_Triangle::paintChart(QPainter &p)
{
    QPen tmp = p.pen(); // 保存当前的笔
    p.setPen(paintChartDrawPen); // 设置新的笔用于绘制

    // 获取起始点和结束点坐标
    int sx = paintStart.rx(), sy = paintStart.ry();
    int ex = paintEnd.rx(), ey = paintEnd.ry();

    // 计算平行四边形的顶点坐标
    int dx = (ex - sx) ; // x 方向的距离

    if (graphPath) delete graphPath; // 删除旧的 QPainterPath
    graphPath = new QPainterPath;

    // 创建平行四边形的路径
    graphPath->moveTo(sx+(dx>>1), sy); // 起点
    graphPath->lineTo(ex,ey); // 上右点
    graphPath->lineTo(sx,ey); // 下右点
    graphPath->closeSubpath(); // 关闭路径

    p.fillPath(*graphPath, paintChartFillPen);
    p.drawPath(*graphPath);
    p.setPen(tmp);
}

void Chart_Triangle::updateMagPointInfo()
{
    // 获取起始点和结束点坐标
    int sx = paintStart.rx(), sy = paintStart.ry();
    int ex = paintEnd.rx(), ey = paintEnd.ry();

    int dx = (ex - sx) ; // x 方向的距离

    // 设置磁力点的位置和方向
    magPoint.i_point[0]->setX(sx+(dx>>1));
    magPoint.i_point[0]->setY(sy);
    magPoint.i_point[0]->setRotate(ORIENTION::NORTHEAST);



    magPoint.i_point[1]->setX(ex);
    magPoint.i_point[1]->setY(ey);
    magPoint.i_point[1]->setRotate(ORIENTION::SOUTHEAST);

    magPoint.i_point[2]->setX(sx);
    magPoint.i_point[2]->setY(ey);
    magPoint.i_point[2]->setRotate(ORIENTION::SOUTHWEST);

    magPoint.i_point[3]->setX(sx+(dx>>1));
    magPoint.i_point[3]->setY(sy);
    magPoint.i_point[3]->setRotate(ORIENTION::NORTHWEST);

}

