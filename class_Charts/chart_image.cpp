#include "chart_image.h"


void Chart_Image::paintChart(QPainter &p)
{
    QPen tmp = p.pen();
    QSize windowSize = QSize(this->size().width()-40, this->size().height()-40);  // 获取窗口的大小
    QImage scaledImage = this->image.scaled(windowSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 缩放图片
    // p.setPen(paintChartDrawPen);
    p.drawImage(20, 20, scaledImage);  // 绘制缩放后的图片
    this->chartText.textType2->hide();

    int sx = paintStart.rx(),sy = paintStart.ry(),ex = paintEnd.rx(),ey = paintEnd.ry();

    if(graphPath) delete graphPath;
    graphPath = new QPainterPath;
    graphPath->addRect(sx,sy,ex-sx,ey-sy);

    // p.fillPath(*graphPath,paintChartFillPen);
    p.drawPath(*graphPath);
    p.setPen(tmp);
}


void Chart_Image::updateMagPointInfo()
{
    int x1 = paintStart.rx(),y1 = paintStart.ry();
    int x2 = paintEnd.rx(),y2 = paintEnd.ry();
    int midx = ((paintStart.rx() + paintEnd.rx())>>1);
    int midy = ((paintStart.ry() + paintEnd.ry())>>1);

    magPoint.i_point[0]->setX(x1);
    magPoint.i_point[0]->setY(y1);
    magPoint.i_point[0]->setRotate(ORIENTION::NORTHWEST);
    magPoint.i_point[1]->setX(midx);
    magPoint.i_point[1]->setY(y1);
    magPoint.i_point[1]->setRotate(ORIENTION::NORTH);
    magPoint.i_point[2]->setX(x2);
    magPoint.i_point[2]->setY(y1);
    magPoint.i_point[2]->setRotate(ORIENTION::NORTHEAST);
    magPoint.i_point[3]->setX(x2);
    magPoint.i_point[3]->setY(midy);
    magPoint.i_point[3]->setRotate(ORIENTION::EAST);
    magPoint.i_point[4]->setX(x2);
    magPoint.i_point[4]->setY(y2);
    magPoint.i_point[4]->setRotate(ORIENTION::SOUTHEAST);
    magPoint.i_point[5]->setX(midx);
    magPoint.i_point[5]->setY(y2);
    magPoint.i_point[5]->setRotate(ORIENTION::SOUTH);
    magPoint.i_point[6]->setX(x1);
    magPoint.i_point[6]->setY(y2);
    magPoint.i_point[6]->setRotate(ORIENTION::SOUTHWEST);
    magPoint.i_point[7]->setX(x1);
    magPoint.i_point[7]->setY(midy);
    magPoint.i_point[7]->setRotate(ORIENTION::WEST);

}
