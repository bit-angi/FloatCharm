#ifndef CHARWIDGET_H
#define CHARWIDGET_H

#include <QPen>
#include <QWidget>

namespace Ui {
class CharWidget;
}

class CharWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CharWidget(QWidget *parent = nullptr);
    ~CharWidget();
    bool grinOn ;
public:
    Ui::CharWidget *ui;

    virtual void wheelEvent(QWheelEvent *event);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void setBackgroundColor();              // 设置窗口背景颜色
    void drawRowLines(QPainter *painter);   // 绘制横线
    void drawColLines(QPainter *painter);   // 绘制竖线

private:
    int minGap;                              // 最小线间隔
    int maxGap;                              // 最大线间隔
    float gap;                               // 当前线间隔
    float startX;                            // 竖线初始x坐标（从窗口中间开始）
    float startY;                            // 横线初始y坐标（从窗口中间开始）
    QPen lightPen;                           // 细一点的画笔
    QPen darkPen;                            // 粗一点的画笔

};

#endif // CHARWIDGET_H
