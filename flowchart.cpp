#include "additemcommand.h"
#include "flowchart.h"
#include "moveitemcommand.h"
#include "class_Charts/chart_base.h"
#include "qmenu.h"
#include <QSvgGenerator>
#include "class_Charts/chart_parallelogram.h"
#include "class_Charts/chart_diamond.h"
#include "class_Charts/chart_triangle.h"
#include "class_Charts/chart_capsule.h"
#include "class_Charts/chart_circle.h"
#include <class_Charts/chart_image.h>
#include <class_Charts/chart_subflort.h>
FlowChart::FlowChart(QWidget *parent, Qt::WindowFlags f) : QWidget(parent,f)
{
    initVar();
    this->select_widget = NULL;
    setMouseTracking(true);
    undostack = new QUndoStack(this) ;
    QAction *m_undoAction = undostack->createUndoAction(this,"Undo");
    m_undoAction->setShortcut(QKeySequence::Undo);

    QAction *m_redoAction = undostack->createRedoAction(this,"Redo");
    m_redoAction->setShortcut(QKeySequence::Redo);

    this->addAction(m_undoAction);
    this->addAction(m_redoAction);

    update();
    contextMenu = new QMenu(this);
    action1 = new QAction("删除", this);
    action2 = new QAction("复制", this);
    action5 = new QAction("粘贴", this);
    action3 = new QAction("垂直对齐", this);
    action4 = new QAction("水平对齐", this);

    // Add actions to the context menu
    contextMenu->addAction(action1);
    contextMenu->addAction(action2);
    contextMenu->addAction(action5);
    contextMenu->addAction(action3);
    contextMenu->addAction(action4);

    contextMenu->setStyleSheet("background-color:white;");
    // Connect actions to slots
    connect(action1, &QAction::triggered, [this]() {
        if (this->curSelecChart) {
            this->delChart(curSelecChart);
        }
    });
    connect(action2, &QAction::triggered, [this]() {
        if (curSelecChart) {
            if (curSelecChart->chartType == PaintChartType::ELLIPSE) {
                copy = new Chart_Ellipse(this);
                copy->w = curSelecChart->width();
                copy->h = curSelecChart->height();
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::RECT) {
                copy = new Chart_Rect(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::ROUNDRECT) {
                copy = new Chart_RoundRect(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::LINE) {
                copy = new Chart_Line(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::CAPSULE) {
                copy = new Chart_Capsule(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::CIRCLE) {
                copy = new Chart_Circle(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::PARALLELOGRAM) {
                copy = new Chart_Parallelogram(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::DIAMOND) {
                copy = new Chart_Diamond(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::SUBFLORT) {
                copy = new Chart_Subflort(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            copy->w = curSelecChart->width();
            copy->h = curSelecChart->height();
            copy->chartType = curSelecChart->chartType;

            // if (copy->chartText.textType1) copy->chartText.textType2->setText("fdfd");
            copy->chartText.textType2->setPlainText(curSelecChart->chartText.textType2->toPlainText());
            copy->chartText.textType2->move(curSelecChart->chartText.textType2->pos().x(),curSelecChart->chartText.textType2->pos().y());
            qDebug() <<"color"<< curSelecChart->color;
            // this->setcharcolor(copy,curSelecChart->color);
            if (curSelecChart->color.isValid())
                copy->paintChartFillPen.setColor(curSelecChart->color);
            copy->color = curSelecChart->color;
            // copy->update();
        }
    });
    //竖直对齐
    connect(action3, &QAction::triggered, [this]() {
        if(!curSelecCharts.isEmpty() && curSelecCharts.size() > 1) {
            int referenceX = (curSelecCharts[0]->widgetStart.x() + curSelecCharts[0]->widgetEnd.x()) / 2;
            for (int i = 1; i < curSelecCharts.size(); ++i) {
                int currentMidX = (curSelecCharts[i]->widgetStart.x() + curSelecCharts[i]->widgetEnd.x()) / 2;
                int dx = currentMidX - referenceX;
                curSelecCharts[i]->setXY(curSelecCharts[i]->widgetStart.x() - dx, curSelecCharts[i]->widgetStart.y());
            }
        }
    });
    //水平对齐
    connect(action4, &QAction::triggered, [this]() {
        if(!curSelecCharts.isEmpty() && curSelecCharts.size() > 1) {
            int referenceY = (curSelecCharts[0]->widgetStart.y() + curSelecCharts[0]->widgetEnd.y()) / 2;
            for (int i = 1; i < curSelecCharts.size(); ++i) {
                int currentMidY = (curSelecCharts[i]->widgetStart.y() + curSelecCharts[i]->widgetEnd.y()) / 2;
                int dy = currentMidY - referenceY;
                curSelecCharts[i]->setXY(curSelecCharts[i]->widgetStart.x(), curSelecCharts[i]->widgetStart.y() - dy);
            }
        }
    });
    // 粘贴
    connect(action5,&QAction::triggered,[this]() {
        if (!curSelecCharts.empty()) {
            if (!curSelecCharts.empty()) {
                while (!originDis.empty()) originDis.pop_back();
                int i = 0;
                auto localPos = QCursor::pos();
                int x = mapFromGlobal(localPos).x() - curSelecCharts[0]->width() / 2;
                int y = mapFromGlobal(localPos).y() - curSelecCharts[0]->height() / 2;
                for (Chart_Base* chart : curSelecCharts) {
                    originDis.push_back(QPair<int,int>(chart->x() - x + curSelecChartPos.x(),chart->y() - y + curSelecChartPos.y()));
                    if (chart) {
                        if (chart->chartType == PaintChartType::ELLIPSE) {
                            copy = new Chart_Ellipse(this);
                            copy->w = chart->width();
                            copy->h = chart->height();
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::RECT) {
                            copy = new Chart_Rect(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::ROUNDRECT) {
                            copy = new Chart_RoundRect(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::LINE) {
                            copy = new Chart_Line(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::CAPSULE) {
                            copy = new Chart_Capsule(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::CIRCLE) {
                            copy = new Chart_Circle(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::PARALLELOGRAM) {
                            copy = new Chart_Parallelogram(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::DIAMOND) {
                            copy = new Chart_Diamond(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::SUBFLORT) {
                            copy = new Chart_Subflort(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        copy->w = chart->width();
                        copy->h = chart->height();
                        copy->chartType = chart->chartType;

                        // if (copy->chartText.textType1) copy->chartText.textType2->setText("fdfd");
                        copy->chartText.textType2->setPlainText(chart->chartText.textType2->toPlainText());
                        copy->chartText.textType2->move(chart->chartText.textType2->pos().x(),chart->chartText.textType2->pos().y());
                        qDebug() <<"color"<< chart->color;
                        // this->setcharcolor(copy,chart->color);
                        if (chart->color.isValid())
                            copy->paintChartFillPen.setColor(chart->color);
                        copy->color = chart->color;

                        auto localPos = QCursor::pos();
                        if(copy) copy->hideMagSize();
                        // copy->setXY(0,0);
                        int x = mapFromGlobal(localPos).x() - copy->w / 2;
                        int y = mapFromGlobal(localPos).y() - copy->h / 2;
                        copy->widgetStart.setX(x);
                        copy->widgetStart.setY(y);
                        curSelecChart = copy;
                        curPaintChart = copy;
                        QPair<int,int> dis = originDis.at(i++);
                        copy->setXY(x - curSelecChartPos.x() + dis.first,y + dis.second - curSelecChartPos.y());
                        copy->setWidthHeight(copy->widgetStart.rx() + copy->w - 40,copy->widgetStart.ry()+copy->h-40);
                        // curPaintChart->setXY(localPos.x(),localPos.y());

                        if(curPaintChart->chartType == PaintChartType::LINE)
                        {
                            connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                            connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                            addLine(curPaintChart);
                            Chart_Line *cl = dynamic_cast<Chart_Line*>(curSelecChart);
                            emit sendLineStyle(cl->paintChartDrawPen,cl->getStartLineHeadType(),cl->getEndLineHeadType());
                        }else
                        {
                            connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                            connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                            connect(curPaintChart,SIGNAL(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)),this,SLOT(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)));
                            //connect(curPaintChart,SIGNAL(hideThisClass()),this,SLOT(resetSeletcChart()));
                            addChart(curPaintChart);
                            emit sendChartStyle(curSelecChart->paintChartDrawPen,curSelecChart->paintChartFillPen);
                        }
                        curPaintChart->update();
                        curPaintChart->show();
                    }
                }
            }
        }
        else if (copy && curSelecCharts.empty()) {
            auto localPos = QCursor::pos();
            if(copy) copy->hideMagSize();
            // copy->setXY(0,0);
            int x = mapFromGlobal(localPos).x() - copy->w / 2;
            int y = mapFromGlobal(localPos).y() - copy->h / 2;
            copy->widgetStart.setX(x);
            copy->widgetStart.setY(y);
            curSelecChart = copy;
            curPaintChart = copy;
            copy->setWidthHeight(copy->widgetStart.rx() + copy->w - 40,copy->widgetStart.ry()+copy->h-40);
            // curPaintChart->setXY(localPos.x(),localPos.y());

            if(curPaintChart->chartType == PaintChartType::LINE)
            {
                connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                addLine(curPaintChart);
                Chart_Line *cl = dynamic_cast<Chart_Line*>(curSelecChart);
                emit sendLineStyle(cl->paintChartDrawPen,cl->getStartLineHeadType(),cl->getEndLineHeadType());
            }else
            {
                connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                connect(curPaintChart,SIGNAL(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)),this,SLOT(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)));
                //connect(curPaintChart,SIGNAL(hideThisClass()),this,SLOT(resetSeletcChart()));
                addChart(curPaintChart);
                emit sendChartStyle(curSelecChart->paintChartDrawPen,curSelecChart->paintChartFillPen);
            }
            curPaintChart->update();
            curPaintChart->show();
            //mouseEventType = MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE;

            // int width = 10 ;
            // int height = 10 ;
            Chart_Base* newcopy;
            if (copy->chartType == PaintChartType::ELLIPSE) {
                newcopy = new Chart_Ellipse(this);
                qDebug() << "??";
            }
            else if (copy->chartType == PaintChartType::RECT) {
                newcopy = new Chart_Rect(this);
            }
            else if (copy->chartType == PaintChartType::ROUNDRECT) {
                newcopy = new Chart_RoundRect(this);
                newcopy->setWidthHeight(newcopy->width()-40,newcopy->height()-40);
            }
            else if (copy->chartType == PaintChartType::LINE) {
                newcopy = new Chart_Line(this);
                newcopy->setWidthHeight(newcopy->width()-40,newcopy->height()-40);
            }
            else if (copy->chartType == PaintChartType::CAPSULE) {
                newcopy = new Chart_Capsule(this);
                newcopy->setWidthHeight(newcopy->width()-40,newcopy->height()-40);
            }
            else if (copy->chartType == PaintChartType::CIRCLE) {
                newcopy = new Chart_Circle(this);
                newcopy->setWidthHeight(newcopy->width()-40,newcopy->height()-40);
            }
            else if (copy->chartType == PaintChartType::PARALLELOGRAM) {
                newcopy = new Chart_Parallelogram(this);
                newcopy->setWidthHeight(newcopy->width()-40,newcopy->height()-40);
            }
            else if (copy->chartType == PaintChartType::DIAMOND) {
                newcopy = new Chart_Diamond(this);
                newcopy->setWidthHeight(newcopy->width()-40,newcopy->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::SUBFLORT) {
                newcopy = new Chart_Subflort(this);
                newcopy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            newcopy->w = copy->width() ;
            newcopy->h = copy->height();
            newcopy->chartText.textType2->setPlainText(copy->chartText.textType2->toPlainText());
            newcopy->chartText.textType2->move(copy->chartText.textType2->pos().x(),copy->chartText.textType2->pos().y());
            qDebug() <<"color"<< copy->color;
            // this->setcharcolor(copy,curSelecChart->color);
            if (curSelecChart->color.isValid())
                copy->paintChartFillPen.setColor(curSelecChart->color);
            newcopy->color = copy->color;
            qDebug() << "newcopy -> w = " << copy->width();
            qDebug() << newcopy->w;
            copy = newcopy;
            qDebug() << "huihe";
        }

    });
}

void FlowChart::rotate(){
    if (!curSelecChart) return ;
    curSelecChart->rotationAngle -= 90;
    if (curSelecChart->rotationAngle % 360 == -270)  curSelecChart->rotationAngle -= 180;
    curSelecChart->rotationAngle = curSelecChart->rotationAngle % 360;

    curSelecChart->updateWidgetPosInof();
    curSelecChart->updateMagPointInfo();
    curSelecChart->updateSizePointInfo();

    update();

    if (curSelecChart->chartText.textType1) {
        // 获取文本框的大小
        QSize textSize = curSelecChart->chartText.textType1->sizeHint();

        // 计算居中的位置
        int x = (curSelecChart->width() - textSize.width()) / 2;
        int y = (curSelecChart->height() - textSize.height()) / 2;

        // // 设置文本框的位置
        curSelecChart->chartText.textType1->move(x, y);

        // // 设置文本框内容的对齐方式
        // curSelecChart->chartText.textType1->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);  // 垂直居中
    }

    if (curSelecChart->chartText.textType2) {
        //获取文本框的大小
        QSize textSize = curSelecChart->chartText.textType2->sizeHint();

        // 计算居中的位置
        int x = (curSelecChart->width() - textSize.width()) / 2;
        int y = (curSelecChart->height() - textSize.height()) / 2;

        // 设置文本框的位置
        curSelecChart->chartText.textType2->move(x, y);

        QTextOption option = curSelecChart->chartText.textType2->document()->defaultTextOption();
        option.setAlignment(Qt::AlignCenter);  // 设置文字水平和垂直居中
        curSelecChart->chartText.textType2->document()->setDefaultTextOption(option);
    }

    if (curSelecChart->chartText.tmpEdit1) {
        // 获取文本框的大小
        QSize textSize = curSelecChart->chartText.tmpEdit1->sizeHint();

        // 计算居中的位置
        int x = (curSelecChart->width() - textSize.width()) / 2;
        int y = (curSelecChart->height() - textSize.height()) / 2;

        // 设置文本框的位置
        curSelecChart->chartText.tmpEdit1->move(x, y);

        // 设置文本框内容的对齐方式
        // curSelecChart->chartText.tmpEdit1->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);  // 垂直居中
    }

    curSelecChart->sizePoint.i_point[0]->setX(0);
    curSelecChart->sizePoint.i_point[0]->setY(0);


    curSelecChart->sizePoint.i_point[1]->setX(curSelecChart->height());
    curSelecChart->sizePoint.i_point[1]->setY(0);
    curSelecChart->sizePoint.i_point[2]->setX(curSelecChart->height());
    curSelecChart->sizePoint.i_point[2]->setY(curSelecChart->width());


    curSelecChart->sizePoint.i_point[3]->setX(curSelecChart->width());
    curSelecChart->sizePoint.i_point[3]->setY(0);
}


void FlowChart::contextMenuEvent(QContextMenuEvent *event)
{
    // Show context menu at the cursor position
    contextMenu->exec(event->globalPos());
}
void FlowChart::initVar()
{
    mouseEventType = MOUSE_EVENT_TYPE::NONE;
    curPaintChart = nullptr;
    curSelecChart = nullptr;
    newLineChart = nullptr;
    newLineFromSelectChart = nullptr;
    newLineToSelectChart = nullptr;
    copy = nullptr;
}

void FlowChart::resetFlowChartPanel()
{
    Chart_Base::resetStaticVal();
    curPaintChart = nullptr;
    curPaintChartType = PaintChartType::NONE;
    curSelecChart = nullptr;
    curSelecChartPos = QPoint();
    newLineChart = nullptr;
    newLineToSelectChart = nullptr;
    newLineFromSelectChart = nullptr;
    magPointDirect = ORIENTION::NONE;
    magPointFromIndex = 0;
    magPointToIndex = 0;
    sizePointDirect = ORIENTION::NONE;
    clearChartsLine();
    charts.reserve(0);
    charts.resize(0);
    line.reserve(0);
    line.resize(0);
    mouseEventType = MOUSE_EVENT_TYPE::NONE;
    fileIsOpened = false;
    // fileIsSaved = true;
    filePath = "";
    setFileNameShow(fileIsSaved);

}
bool FlowChart::saveAsPNG(QString &filePath){
    if (filePath.isEmpty()) {
        return false;
    }

    // 创建一个 QPixmap，与 widget 的尺寸相同
    QPixmap pixmap(size());

    // 使用 QPainter 绘制 widget 内容到 QPixmap
    render(&pixmap);

    // 将 QPixmap 保存为 PNG 文件
    return pixmap.save(filePath, "PNG");


}



bool FlowChart::saveAsSVG(const QString &filePath)
{
    QSvgGenerator generator;
    generator.setFileName(filePath);
    generator.setSize(this->size());
    generator.setViewBox(this->rect());
    generator.setTitle(tr("Flow Chart"));
    generator.setDescription(tr("An SVG drawing created by the FlowChart widget."));

    QPainter painter;
    if (!painter.begin(&generator)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file for writing."));
        return false;
    }

    this->render(&painter);
    painter.end();
    return true;
}

void FlowChart::setFileSetSaved(bool isSaved)
{
    if(fileIsSaved != isSaved)
    {
        fileIsSaved = isSaved;
        setFileNameShow(fileIsSaved);
    }
}

void FlowChart::setFileNameShow(bool isSaved)
{
    QString tmp;
    if(fileIsOpened)
    {
        tmp = QString("%1%2").arg(filePath).arg((isSaved?"":" *"));
        emit updateWindowTitle(tmp);
    }else
    {
        tmp = QString("%1%2").arg("Untitle").arg((isSaved?"":" *"));
        emit updateWindowTitle(tmp);
    }
}

Chart_Base * FlowChart::getCurPaintChart()
{
    return curPaintChart;
}

void FlowChart::setSelChartLineColor(const QColor &color)
{
    if (curSelecChart == nullptr) return ;
    curSelecChart->paintChartDrawPen.setColor(color);
    curSelecChart->update();
}

void FlowChart::setSelChartFillColor(const QColor &color)
{
    if (curSelecChart == nullptr) return ;
    curSelecChart->color = color ;
    curSelecChart->paintChartFillPen.setColor(color);
    curSelecChart->update();
}

void FlowChart::setMousePressedFlag(MOUSE_EVENT_TYPE f)
{
    mouseEventType = f;
}

void FlowChart::setPaintChart()
{
    // bug : 这里我把delete curPaintChart 更改为了 curPaintChart = NULL; 免得程序崩溃
    if(curPaintChart != nullptr)
        // delete curPaintChart;
        curPaintChart = NULL;

    switch(curPaintChartType)
    {
    case PaintChartType::RECT:
    {
        curPaintChart = new Chart_Rect(this);
    }break;
    case PaintChartType::DIAMOND:
    {
        curPaintChart = new Chart_Diamond(this);
    }break;
    case PaintChartType::ROUNDRECT:
    {
        curPaintChart = new Chart_RoundRect(this);
    }break;
    case PaintChartType::ELLIPSE:
    {
        curPaintChart = new Chart_Ellipse(this);
    }break;
    case PaintChartType::LINE:
    {
        curPaintChart = new Chart_Line(this);
    }break;
    case PaintChartType::PARALLELOGRAM:
    {
        curPaintChart = new Chart_Parallelogram(this);
    }break;
    case PaintChartType::SUBFLORT:
    {
        curPaintChart = new Chart_Subflort(this);
    }break;
    case PaintChartType::TRIANGLE:
    {
        curPaintChart = new Chart_Triangle(this);
    }break;
    case PaintChartType::CIRCLE:
    {
        curPaintChart = new Chart_Circle(this);
    }break;
    case PaintChartType::CAPSULE:
    {
        curPaintChart = new Chart_Capsule(this);
    }break;
    case PaintChartType::TRAPEZOID:
    {
        curPaintChart = new Chart_Trapezoid(this);
    }break;
    default:case PaintChartType::NONE:{
        curPaintChart = nullptr;
    }break;
    }
    if(curPaintChart)
    {
        mouseEventType = MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE;
    }
}


/**
 * 设置单个选中目标
 * @brief FlowChart::setSelecChart
 * @param cb
 * @param x
 * @param y
 */
void FlowChart::setSelecChart(Chart_Base * cb, int x, int y)
{

    emit disableStyle();
    qDebug() << "niubi";
    // this->grabKeyboard();
    if(curSelecChart != nullptr) curSelecChart->hideMagSize();
    curSelecChart = cb;
    curSelecChart->showMagSize();
    if (!curSelecCharts.empty()) {
        for (Chart_Base* chart : curSelecCharts){
            chart->showMagSize();
        }
    }
    curSelecChartPos = QPoint(x,y);
    mouseEventType = MOUSE_EVENT_TYPE::RUNTIME_CHANGE_POS;
    this->undostack->push(new MoveItemCommand(cb,this,cb->x(),cb->y()));
    Chart_Line *cl = nullptr;
    if(nullptr == (cl = dynamic_cast<Chart_Line*>(cb)))
    {
        emit sendChartStyle(cb->paintChartDrawPen,cb->paintChartFillPen);
    }else
    {
        emit sendLineStyle(cl->paintChartDrawPen,cl->getStartLineHeadType(),cl->getEndLineHeadType());
    }
}

bool FlowChart::openChartFile()
{
    // if(!fileIsSaved)
    // {
    //     QMessageBox tmp(QMessageBox::Warning,tr("警告！"),tr("不保存文件就关闭？"),QMessageBox::NoButton,this->parentWidget());
    //     QPushButton *saveclose = tmp.addButton(tr("保存并关闭"),QMessageBox::ActionRole);
    //     QPushButton *nosaveclose = tmp.addButton(tr("不保存关闭"),QMessageBox::AcceptRole);
    //     QPushButton *cancel = tmp.addButton(tr("取消"),QMessageBox::RejectRole);
    //     tmp.exec();
    //     if(tmp.clickedButton() == saveclose)
    //     {
    //         if(saveChartFile())
    //         {
    //             resetFlowChartPanel();
    //         }else
    //             return false;
    //         //qDebug()<<"Save and Quit";
    //     }else if(tmp.clickedButton() == nosaveclose)
    //     {
    //         //qDebug()<<"Not Save and Quit";
    //         resetFlowChartPanel();
    //     }else if(tmp.clickedButton() == cancel)
    //     {
    //         return true;
    //         //qDebug()<<"cancel ";
    //     }
    // }
    resetFlowChartPanel();
    QString tmpFilePath = QFileDialog::getOpenFileName(this,tr("打开文件"),"F:",tr("FCT文件(*.fct)"));
    if(tmpFilePath == "") return false;

    if(loadFile(tmpFilePath) == false)
    {
        QMessageBox::critical(this->parentWidget(),tr("错误！"),tr("打开文件失败！\n文件损坏或类型不正确"),QMessageBox::Ok);
        return false;
    }else
    {
        fileIsOpened = true;
        this->filePath = tmpFilePath;
        setFileNameShow(fileIsSaved);
        qDebug()<<"Load File Success"<<fileIsSaved;
    }
    qDebug()<<"charts size:"<<charts.size()<<" line size::"<<line.size();
    return true;
}

bool FlowChart::saveChartFile()
{
    if (fileIsSaved) {
        return true;
    } else {
        if (fileIsOpened) {
            if (saveFile(filePath)) {
                filePath = "";
            } else {
                QMessageBox::critical(this->parentWidget(), tr("错误！"), tr("保存文件失败！\n文件已占用或者访问权限不足"), QMessageBox::Ok);
                return false;
            }
        } else {
            QString tmpFilePath = QFileDialog::getSaveFileName(nullptr, "保存文件", "", "FCT文件(*.fct);;PNG图片(*.png);;SVG文件(*.svg)");
            qDebug() << tmpFilePath;
            if (tmpFilePath.isEmpty()) return false;

            QFileInfo fileInfo(tmpFilePath);
            QString fileExtension = fileInfo.suffix().toLower();

            if (fileExtension == "fct") {
                if (saveFile(tmpFilePath)) {
                    filePath = tmpFilePath;
                    fileIsOpened = true;
                } else {
                    QMessageBox::critical(this->parentWidget(), tr("错误！"), tr("保存文件失败！\n文件已占用或者访问权限不足"), QMessageBox::Ok);
                    return false;
                }
            } else if (fileExtension == "png") {
                if (saveAsPNG(tmpFilePath)) {
                    filePath = tmpFilePath;
                    fileIsOpened = true;
                } else {
                    QMessageBox::critical(this->parentWidget(), tr("错误！"), tr("保存文件失败！\n文件已占用或者访问权限不足"), QMessageBox::Ok);
                    return false;
                }
            } else if (fileExtension == "svg") {
                if (saveAsSVG(tmpFilePath)) {
                    filePath = tmpFilePath;
                    fileIsOpened = true;
                } else {
                    QMessageBox::critical(this->parentWidget(), tr("错误！"), tr("保存文件失败！\n文件已占用或者访问权限不足"), QMessageBox::Ok);
                    return false;
                }
            } else {
                QMessageBox::critical(this->parentWidget(), tr("错误！"), tr("不支持的文件格式"), QMessageBox::Ok);
                return false;
            }
            qDebug() << "sca";
        }
        setFileSetSaved(true);
    }
    return true;
}


bool FlowChart::newChartFile()
{
    // if(!fileIsSaved)
    // {
    //     QMessageBox tmp(QMessageBox::Warning,tr("警告！"),tr("不保存文件就关闭？"),QMessageBox::NoButton,this->parentWidget());
    //     QPushButton *saveclose = tmp.addButton(tr("保存并关闭"),QMessageBox::ActionRole);
    //     QPushButton *nosaveclose = tmp.addButton(tr("不保存关闭"),QMessageBox::AcceptRole);
    //     QPushButton *cancel = tmp.addButton(tr("取消"),QMessageBox::RejectRole);
    //     tmp.exec();
    //     if(tmp.clickedButton() == saveclose)
    //     {
    //         if(saveChartFile())
    //         {
    //             resetFlowChartPanel();
    //         }else{
    //             return false;
    //         }
    //         //qDebug()<<"Save and Quit";

    //     }else if(tmp.clickedButton() == nosaveclose)
    //     {
    //         //qDebug()<<"Not Save and Quit";
    //         resetFlowChartPanel();
    //     }else if(tmp.clickedButton() == cancel)
    //     {
    //         //qDebug()<<"cancel ";
    //     }
    // }else{
    //     resetFlowChartPanel();
    // }
    resetFlowChartPanel(); // 这行是新加的

    return true;
}

//void FlowChart::resetSeletcChart()
//{
//    if(curSelecChart != nullptr) curSelecChart->hideMagSize();
//    curSelecChart = nullptr;
//}

Chart_Base * FlowChart::getCurSeleChart()
{
    return curSelecChart;
}


void FlowChart::addChart(Chart_Base *cb)
{
    charts.push_back(cb);
    connect(cb,&Chart_Base::doubleClick,this,[=]() {
        this->releaseKeyboard();
        emit doubleClick() ;
    });
    // connect(cb,&Chart_Base::changeText,this,[=]() {
    //     qDebug() << "changet";
    //     while(!this->curSelecCharts.empty()) this->curSelecCharts.pop_back();
    //     this->hideMagSizeAll();
    //     emit changeText();
    // });

    this->undostack->push(new AddItemCommand(cb,this));
}
bool FlowChart::delChart(Chart_Base *&cb)
{
    qDebug() << "delchart";
    for(auto it = charts.begin();it != charts.end();it++)
    {
        if(*it == cb)
        {
            Chart_Base *tmp = cb;
            cb = nullptr;
            charts.erase(it);
#if 1
            for(auto magit = tmp->magPoint.i_point.begin();magit!=tmp->magPoint.i_point.end();magit++)
            {
                for(auto magLineStIt = (*magit)->i_lineStart.begin();magLineStIt != (*magit)->i_lineStart.end();magLineStIt++)
                {
                    dynamic_cast<Chart_Line*>(*magLineStIt) ->resetEndChart();
                    if(!delLine(*magLineStIt))
                    {
                        qDebug()<<"Error";
                    }else{
                        qDebug()<<"Succeed.";
                    }
                }
                for(auto magLineEnIt = (*magit)->i_lineEnd.begin();magLineEnIt != (*magit)->i_lineEnd.end();magLineEnIt++)
                {
                    dynamic_cast<Chart_Line*>(*magLineEnIt) ->resetStartChart();
                    if(!delLine(*magLineEnIt))
                    {
                        qDebug()<<"Error";
                    }else{
                        qDebug()<<"Succeed.";
                    }
                }
            }
#endif
            delete tmp;

            return true;
        }
    }
    return false;
}
void FlowChart::addLine(Chart_Base *cb)
{
    line.push_back(cb);
    this->undostack->push(new AddItemCommand(cb,this));
    connect(cb,&Chart_Base::doubleClick,this,[=]() {
        this->releaseKeyboard();
        emit doubleClick() ;
    });
}
bool FlowChart::delLine(Chart_Base *&cb)
{
    for(auto it = line.begin();it != line.end();it++)
    {
        if(*it == cb)
        {
            Chart_Line *tmp = dynamic_cast<Chart_Line*>(*it);
            cb = nullptr;
            line.erase(it);
            qDebug()<<tmp->magPoint.i_point.size();


            tmp->resetEndChart();
            tmp->resetStartChart();
            delete tmp;
            return true;
        }
    }
    return false;
}

void FlowChart::hideMagSizeAll()
{
    for(auto it = charts.begin();it!=charts.end();it++)
    {
        (*it)->hideMagSize();
    }
    for(auto it = line.begin();it!=line.end();it++)
    {
        (*it)->hideMagSize();
    }
    curSelecChart = nullptr;
    mouseEventType = MOUSE_EVENT_TYPE::NONE;
    emit disableStyle();
}

bool FlowChart::saveFile(QString filePath)
{
    qDebug() << "svca0";
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    QDataStream fout(&file);
    qDebug() << "svca";
    Chart_Base::saveStaticValue(fout);
    unsigned long long i;
    i = charts.size();
    fout.writeRawData(reinterpret_cast<const char*>(&i),sizeof(unsigned long long));
    for(auto it = charts.begin(); it!=charts.end(); it++)
    {
        fout<<*(*it);
    }
    i = line.size();
    fout.writeRawData(reinterpret_cast<const char*>(&i),sizeof(unsigned long long));
    for(auto it = line.begin(); it!=line.end(); it++)
    {
        fout<<*(*it)<<*(reinterpret_cast<const Chart_Line*>(*it));
    }
    file.close();
    return true;
}

bool FlowChart::loadFile(QString filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QDataStream fin(&file);
    std::map<int,Chart_Base*> chartMap;

    Chart_Base::loadStaticValue(fin);
    unsigned long long cnt;
    fin.readRawData(reinterpret_cast<char*>(&cnt),sizeof(unsigned long long));
    qDebug()<<"图形个数："<<cnt;
    for(unsigned long long i = 0;i<cnt;i++)
    {
        PaintChartType tmp;
        Chart_Base *cb;
        fin.readRawData(reinterpret_cast<char*>(&tmp),sizeof(PaintChartType));
        switch(tmp)
        {
        case PaintChartType::RECT:
        {
            cb = new Chart_Rect(this);
        }break;
        case PaintChartType::DIAMOND:
        {
            cb = new Chart_Diamond(this);
        }break;
        case PaintChartType::ROUNDRECT:
        {
            cb = new Chart_RoundRect(this);
        }break;
        case PaintChartType::ELLIPSE:
        {
            cb = new Chart_Ellipse(this);
        }break;
        case PaintChartType::TRAPEZOID:
        {
            cb = new Chart_Trapezoid(this);
        }break;
        case PaintChartType::CAPSULE:
        {
            cb = new Chart_Capsule(this);
        }break;
        case PaintChartType::CIRCLE:
        {
            cb = new Chart_Circle(this);
        }break;
        case PaintChartType::PARALLELOGRAM:
        {
            cb = new Chart_Parallelogram(this);
        }break;
        case PaintChartType::SUBFLORT:
        {
            cb = new Chart_Subflort(this);
        }break;
        case PaintChartType::IMAGE:
        {
            cb = new Chart_Image(this);
        }break;
        default:case PaintChartType::NONE:{
            cb = nullptr;
        }break;
        }
        cb->chartType = tmp;
        fin>>(*cb);
        connect(cb,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
        connect(cb,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
        connect(cb,SIGNAL(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)),this,SLOT(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)));
        addChart(cb);
        cb->applyWidthHeight();
        cb->update();
        cb->show();
        chartMap[cb->getID()] = cb;
    }
    fin.readRawData(reinterpret_cast<char*>(&cnt),sizeof(unsigned long long));
    qDebug()<<"连线个数："<<cnt;
    for(unsigned long long i = 0;i<cnt;i++)
    {
        PaintChartType tmp;
        Chart_Base *cb;
        Chart_Line *cl;
        int id;
        fin.readRawData(reinterpret_cast<char*>(&tmp),sizeof(PaintChartType));
        cb = new Chart_Line(this);
        addLine(cb);
        if(nullptr == (cl = dynamic_cast<Chart_Line*>(cb))) qDebug()<<"error";
        fin>>(*cb)>>(*cl);
        try{
            fin.readRawData(reinterpret_cast<char*>(&id),sizeof(int));
            if(id>=0)
            {
                Chart_Base *cbs = chartMap.at(id);
                cbs->addMagiPointStartLine(cl->getStartMagIndex(),cl);
                cl->setStartChart(cbs);
            }
        }catch(std::out_of_range &oor){
            qDebug()<<oor.what()<<"Not Found Start chart.";
        }
        try{
            fin.readRawData(reinterpret_cast<char*>(&id),sizeof(int));
            if(id>=0)
            {
                Chart_Base *cbe = chartMap.at(id);
                cbe->addMagiPointEndLine(cl->getEndMagIndex(),cl);
                cl->setEndChart(cbe);
            }
        }catch(std::out_of_range &oor){
            qDebug()<<oor.what()<<"Not Found End chart.";
        }
        connect(cl,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
        connect(cl,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
        cl->applyWidthHeight();
        cl->update();
        cl->show();
    }
    hideMagSizeAll();
    return true;
}


void FlowChart::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(QColor(150,150,150));
    const int gap = 30;
    if (this->gridOn) {
        for(int i = 1;i * gap < width();i++)
        {
            if(i%5 == 0)
                p.drawLine(QLineF(i*gap,0,i*gap,height()));
        }
        for(int i = 1;i * gap < height();i++)
        {
            if(i%5 == 0)
                p.drawLine(QLineF(0,i*gap,width(),i*gap));
        }

        p.setPen(QColor(200,200,200,150));
        //p.setPen(Qt::DotLine);
        //p.setOpacity(200);
        for(int i = 1;i * gap < width();i++)
        {
            if(i%5 == 0) continue;
            p.drawLine(QLineF(i*gap,0,i*gap,height()));
        }
        for(int i = 1;i * gap < height();i++)
        {
            if(i%5 == 0) continue;
            p.drawLine(QLineF(0,i*gap,width(),i*gap));
        }
    }


    QStyleOption opt;
    opt.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);

    //event->accept();
}
void FlowChart::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
    this->grabKeyboard();
    switch(mouseEventType)
    {
    case MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE:{
        int x = event->pos().rx();
        int y = event->pos().ry();
        //curPaintChart->setObjectName(QStringLiteral("tttt"));
        if(curSelecChart) curSelecChart->hideMagSize();
        curSelecChart = curPaintChart;
        curPaintChart->setXY(x,y);
        //curPaintChart->setAttribute(Qt::WA_StyledBackground,true);
        //curPaintChart->setStyleSheet(QStringLiteral("background-color: rgb(100, 100, 100);"));
        if(curPaintChart->chartType == PaintChartType::LINE)
        {
            connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
            connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
            addLine(curPaintChart);
            Chart_Line *cl = dynamic_cast<Chart_Line*>(curSelecChart);
            emit sendLineStyle(cl->paintChartDrawPen,cl->getStartLineHeadType(),cl->getEndLineHeadType());
        }else
        {
            connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
            connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
            connect(curPaintChart,SIGNAL(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)),this,SLOT(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)));
            //connect(curPaintChart,SIGNAL(hideThisClass()),this,SLOT(resetSeletcChart()));
            addChart(curPaintChart);
            emit sendChartStyle(curSelecChart->paintChartDrawPen,curSelecChart->paintChartFillPen);
        }
        curPaintChart->update();
        curPaintChart->show();
        //mouseEventType = MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE;
        event->accept();
    }break;
    default:case MOUSE_EVENT_TYPE::NONE:{
        qDebug() << "noen";
        this->multi_start = event->pos();
        this->oking = true ;
        for(auto it = charts.begin();it!=charts.end();it++)
        {
            (*it)->overlapChartMousePressed(event);
            if(event->isAccepted()) return;
        }
        for(auto a:line)
        {
            a->overlapChartMousePressed(event);
            if(event->isAccepted()) return;
        }
        hideMagSizeAll();
    }break;
    }
}
void FlowChart::mouseMoveEvent(QMouseEvent *event)
{
    //if(event->isAccepted()) return;
    event->ignore();
    switch(mouseEventType)
    {
    default:case MOUSE_EVENT_TYPE::NONE:
    {
        if (oking) {
            // 图形选中功能
            select_widget = new QWidget(this);
            select_widget->setStyleSheet("background-color : rgba(0,0,170,0.3)");
            select_widget->setGeometry(0,0,0,0);
            oking = false ;
        }
        if (select_widget) {
            if ((event->pos().y() - this->multi_start.y() > 0) && (event->pos().x() - this->multi_start.x() > 0))
                select_widget->setGeometry(this->multi_start.x(),this->multi_start.y(),event->pos().x() - this->multi_start.x(),event->pos().y() - this->multi_start.y());
            else if ((event->pos().y() - this->multi_start.y() < 0) && (event->pos().x() - this->multi_start.x() < 0))
                select_widget->setGeometry(event->x(),event->y(),-event->pos().x() + this->multi_start.x(),-event->pos().y() + this->multi_start.y());
            else if ((event->pos().y() - this->multi_start.y() > 0) && (event->pos().x() - this->multi_start.x() < 0))
                select_widget->setGeometry(event->x(),multi_start.y(),-event->pos().x() + this->multi_start.x(),event->pos().y() - this->multi_start.y());
            else if ((event->pos().y() - this->multi_start.y() < 0) && (event->pos().x() - this->multi_start.x() > 0))
                select_widget->setGeometry(multi_start.x(),event->y(),event->pos().x() - this->multi_start.x(),-event->pos().y() + this->multi_start.y());
            this->select_widget->show();
            this->update();
        }
        for(auto it = charts.begin();it!=charts.end();it++)
        {
            (*it)->overlapChartMouseMove(event);
            if(event->isAccepted()) return;
        }
        for(auto it = line.begin();it!=line.end();it++)
        {
            (*it)->overlapChartMouseMove(event);
            if(event->isAccepted()) return;
        }
        if(curSelecChart == nullptr)
        {
            setCursor(QCursor(Qt::ArrowCursor));
            // bug : 这里为了实现多个选中注释掉了，不知道会导致什么问题
            // hideMagSizeAll();
        }
    }break;
    case MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE:
    {
        int x = event->pos().rx(),y = event->pos().ry();
        if(curSelecChart)
        {
            if(curSelecChart->chartType == PaintChartType::LINE)
            {
                for(auto it = charts.begin();it!=charts.end();it++)
                {
                    if((*it)->autoSetMagi(x,y,magPointIndex))
                    {
                        lineSelectChart = *it;
                        break;
                    }else{
                        lineSelectChart = nullptr;
                    }
                }
                //if(!lineSelectChart) reinterpret_cast<Chart_Line *>(curSelecChart)->resetEndChart();
            }
            curPaintChart->setWidthHeight(x,y);
        }
        event->accept();
    }break;
    case MOUSE_EVENT_TYPE::RUNTIME_CHANGE_SIZE:
    {
        int x = event->pos().rx(),y = event->pos().ry();

        if(curSelecChart->chartType == PaintChartType::LINE)
        {
            qDebug()<<"hehe";
            for(auto it = charts.begin();it!=charts.end();it++)
            {
                if((*it)->autoSetMagi(x,y,magPointIndex))
                {
                    lineSelectChart = *it;
                    break;
                }else{
                    lineSelectChart = nullptr;
                }
            }
            //if(!lineSelectChart) reinterpret_cast<Chart_Line *>(curSelecChart)->resetEndChart();
        }
        curSelecChart->setWidthHeight(x,y,sizePointDirect);
        event->accept();
    }break;
    case MOUSE_EVENT_TYPE::RUNTIME_CREATE_MAGPOINT:
    {
        if(newLineChart == nullptr)
        {
            newLineChart = new Chart_Line(this);
            if(curSelecChart)
                curSelecChart->hideMagSize();
            curSelecChart = newLineChart;
            addLine(newLineChart);
            //newLineChart->setAttribute(Qt::WA_StyledBackground,true);
            //newLineChart->setStyleSheet(QStringLiteral("background-color: rgb(100, 100, 100);"));
            connect(newLineChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
            connect(newLineChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
            newLineChart->setXY(newLineFromSelectChart->getMagiPointAbsX(magPointFromIndex),newLineFromSelectChart->getMagiPointAbsY(magPointFromIndex));
            newLineChart->setStartChart(newLineFromSelectChart);
            newLineChart->setStartMagIndex(magPointFromIndex);
            newLineChart->setStartDirect(magPointDirect);
            newLineChart->update();
            newLineChart->show();

            newLineFromSelectChart->addMagiPointStartLine(magPointFromIndex,newLineChart);
        }
        int x = event->pos().rx(),y = event->pos().ry();

        for(auto it = charts.begin();it!=charts.end();it++)
        {
            //if(*it == newLineFromSelectChart) continue;
            if((*it)->autoSetMagi(x,y,magPointToIndex))
            {
                newLineToSelectChart = *it;
                break;
            }else{
                newLineToSelectChart = nullptr;
            }
        }
        //if(!newLineToSelectChart) newLineChart->resetEndChart();
        newLineChart->setWidthHeight(x,y,ORIENTION::ENDPOINT);
        event->ignore();
    }break;
    case MOUSE_EVENT_TYPE::RUNTIME_CHANGE_POS:
    {
        if(curSelecChart->chartType != PaintChartType::LINE)
        {
            if (!curSelecCharts.empty() && curSelecCharts.contains(curSelecChart)) {
                if (!dragMultiSub) {
                    dragMultiSub = true ;
                    while (!originDis.empty()) originDis.pop_back();
                    for (Chart_Base* chart : curSelecCharts) {
                        originDis.push_back(QPair<int,int>(chart->x() - event->pos().x() + curSelecChartPos.x(),chart->y() - event->pos().y() + curSelecChartPos.y()));
                    }
                }
                int i = 0 ;
                for (Chart_Base* chart : curSelecCharts) {
                    QPair<int,int> dis = originDis.at(i++);
                    chart->setXY(event->pos().rx() - curSelecChartPos.x() + dis.first,event->pos().ry() + dis.second - curSelecChartPos.y());
                }
                event->accept();
            }
            else {
                curSelecChart->setXY(event->pos().rx() - curSelecChartPos.rx(),event->pos().ry() - curSelecChartPos.ry());
                event->accept();
            }
        }

    }break;
    }
}

void FlowChart::mouseReleaseEvent(QMouseEvent *event)
{
    dragMultiSub = false ;
    switch(mouseEventType)
    {
    case MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE:
    {
        //curPaintChart->updatePath();
        resetPaintChartType();
        if(curSelecChart->chartType == PaintChartType::LINE)
        {
            Chart_Line *cl = reinterpret_cast<Chart_Line *>(curSelecChart);

            if(lineSelectChart)
            {
                lineSelectChart->addMagiPointEndLine(magPointIndex,curSelecChart);
                lineSelectChart->hideMagOnly();
                cl->setEndChart(lineSelectChart);
                cl->setEndMagIndex(magPointIndex);
                cl->setEndDirect(lineSelectChart->getMagiPointDirect(magPointIndex));
                cl->update();
                lineSelectChart = nullptr;
            }
            else{
                cl->resetEndChart();
            }

        }


        curPaintChart = nullptr;
        mouseEventType = MOUSE_EVENT_TYPE::NONE;
        setFileSetSaved(false);
        event->accept();
    }break;
    case MOUSE_EVENT_TYPE::RUNTIME_CHANGE_SIZE:
    {
        if(curSelecChart->chartType == PaintChartType::LINE)
        {
            Chart_Line *cl = reinterpret_cast<Chart_Line *>(curSelecChart);
            if(lineSelectChart)
            {
                if(sizePointDirect == ORIENTION::STARTPOINT)
                {
                    cl->resetStartChart();
                    lineSelectChart->addMagiPointStartLine(magPointIndex,curSelecChart);
                    lineSelectChart->hideMagOnly();
                    cl->setStartChart(lineSelectChart);
                    cl->setStartMagIndex(magPointIndex);
                    cl->setStartDirect(lineSelectChart->getMagiPointDirect(magPointIndex));
                }else if(sizePointDirect == ORIENTION::ENDPOINT)
                {
                    cl->resetEndChart();
                    lineSelectChart->addMagiPointEndLine(magPointIndex,curSelecChart);
                    lineSelectChart->hideMagOnly();
                    cl->setEndChart(lineSelectChart);
                    cl->setEndMagIndex(magPointIndex);
                    cl->setEndDirect(lineSelectChart->getMagiPointDirect(magPointIndex));
                }else{
                    qDebug()<<"Error";
                }

                cl->update();
            }else
            {
                if(sizePointDirect == ORIENTION::STARTPOINT)
                {
                    cl->resetStartChart();
                }else if(sizePointDirect == ORIENTION::ENDPOINT)
                {
                    cl->resetEndChart();
                }else
                {
                    qDebug()<<"Error";
                }
            }
        }
        mouseEventType = MOUSE_EVENT_TYPE::NONE;
        lineSelectChart = nullptr;
        setFileSetSaved(false);
        event->accept();
    }break;
    case MOUSE_EVENT_TYPE::RUNTIME_CREATE_MAGPOINT:
    {
        if(newLineToSelectChart)
        {
            newLineToSelectChart->addMagiPointEndLine(magPointToIndex,newLineChart);
            newLineToSelectChart->hideMagOnly();
            newLineChart->setEndChart(newLineToSelectChart);
            newLineChart->setEndMagIndex(magPointToIndex);
            newLineChart->setEndDirect(newLineToSelectChart->getMagiPointDirect(magPointToIndex));
            newLineChart->update();
        }else
        {
            if(newLineChart)
                newLineChart->resetEndChart();
        }
        mouseEventType = MOUSE_EVENT_TYPE::NONE;
        newLineChart = nullptr;
        newLineFromSelectChart = nullptr;
        newLineToSelectChart = nullptr;
        setFileSetSaved(false);
        event->accept();
    }break;
    case MOUSE_EVENT_TYPE::RUNTIME_CHANGE_POS:
    {
        mouseEventType = MOUSE_EVENT_TYPE::NONE;
        setFileSetSaved(false);
        event->accept();
    }break;
    default:case MOUSE_EVENT_TYPE::NONE:
    {
        this->oking = false ;
        while(!this->curSelecCharts.empty()) this->curSelecCharts.pop_back();
        if (this->select_widget) {
            for (Chart_Base* chart : charts) {
                qDebug() << chart->width();
                qDebug() << select_widget->pos().x();
                qDebug() << select_widget->width();
                qDebug() << chart->x();
                // debug
                if (chart->widgetStart.x() > select_widget->x() && chart->widgetStart.y() > select_widget->y() && chart->widgetEnd.x() < select_widget->x() + select_widget->width() && chart->widgetEnd.y() < select_widget->y() + select_widget->height()){
                    chart->showMagSize();
                    this->curSelecCharts.push_back(chart);
                }
            }
            delete select_widget;
            select_widget = NULL ;
        }
        event->ignore();
    }break;
    }

}
void FlowChart::keyPressEvent(QKeyEvent *ev)
{
    // ev->ignore();
    qDebug() << "6666";
    // 复制粘贴功能

    if (ev->matches(QKeySequence::Copy)) {
        if (curSelecChart) {
            if (curSelecChart->chartType == PaintChartType::ELLIPSE) {
                copy = new Chart_Ellipse(this);
                copy->w = curSelecChart->width();
                copy->h = curSelecChart->height();
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::RECT) {
                copy = new Chart_Rect(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::ROUNDRECT) {
                copy = new Chart_RoundRect(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::LINE) {
                copy = new Chart_Line(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::CAPSULE) {
                copy = new Chart_Capsule(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::CIRCLE) {
                copy = new Chart_Circle(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::PARALLELOGRAM) {
                copy = new Chart_Parallelogram(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::DIAMOND) {
                copy = new Chart_Diamond(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::SUBFLORT) {
                copy = new Chart_Subflort(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            copy->w = curSelecChart->width();
            copy->h = curSelecChart->height();
            copy->chartType = curSelecChart->chartType;

            // if (copy->chartText.textType1) copy->chartText.textType2->setText("fdfd");
            copy->chartText.textType2->setPlainText(curSelecChart->chartText.textType2->toPlainText());
            copy->chartText.textType2->move(curSelecChart->chartText.textType2->pos().x(),curSelecChart->chartText.textType2->pos().y());
            qDebug() <<"color"<< curSelecChart->color;
            // this->setcharcolor(copy,curSelecChart->color);
            if (curSelecChart->color.isValid())
                copy->paintChartFillPen.setColor(curSelecChart->color);
            copy->color = curSelecChart->color;
            // copy->update();
        }
    }
    else if (ev->matches(QKeySequence::Cut)) {
        if (curSelecChart) {
            if (curSelecChart->chartType == PaintChartType::ELLIPSE) {
                copy = new Chart_Ellipse(this);
                copy->w = curSelecChart->width();
                copy->h = curSelecChart->height();
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::RECT) {
                copy = new Chart_Rect(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::ROUNDRECT) {
                copy = new Chart_RoundRect(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::LINE) {
                copy = new Chart_Line(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::CAPSULE) {
                copy = new Chart_Capsule(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::CIRCLE) {
                copy = new Chart_Circle(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::PARALLELOGRAM) {
                copy = new Chart_Parallelogram(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::DIAMOND) {
                copy = new Chart_Diamond(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::SUBFLORT) {
                copy = new Chart_Subflort(this);
                copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            copy->w = curSelecChart->width();
            copy->h = curSelecChart->height();
            copy->chartType = curSelecChart->chartType;

            // if (copy->chartText.textType1) copy->chartText.textType2->setText("fdfd");
            copy->chartText.textType2->setPlainText(curSelecChart->chartText.textType2->toPlainText());
            copy->chartText.textType2->move(curSelecChart->chartText.textType2->pos().x(),curSelecChart->chartText.textType2->pos().y());
            qDebug() <<"color"<< curSelecChart->color;
            // this->setcharcolor(copy,curSelecChart->color);
            if (curSelecChart->color.isValid())
                copy->paintChartFillPen.setColor(curSelecChart->color);
            copy->color = curSelecChart->color;
            // copy->update();
        }
        qDebug() << "del";
        if(curSelecChart)
        {
            if(curSelecChart->chartType == PaintChartType::LINE)
            {
                if(!delLine(curSelecChart))
                {
                    qDebug()<<"Error";
                }
            }else{
                if(!delChart(curSelecChart))
                {
                    qDebug()<<"Error";
                }
            }
            curSelecChart = nullptr;
        }
    }
    else if (ev->matches(QKeySequence::Save)) {
        this->saveChartFile();
    }
    else if (ev->matches(QKeySequence::Paste)) {
        if (!curSelecCharts.empty()) {
            if (!curSelecCharts.empty()) {
                while (!originDis.empty()) originDis.pop_back();
                int i = 0;
                auto localPos = QCursor::pos();
                int x = mapFromGlobal(localPos).x() - curSelecCharts[0]->width() / 2;
                int y = mapFromGlobal(localPos).y() - curSelecCharts[0]->height() / 2;
                for (Chart_Base* chart : curSelecCharts) {
                    originDis.push_back(QPair<int,int>(chart->x() - x + curSelecChartPos.x(),chart->y() - y + curSelecChartPos.y()));
                    if (chart) {
                        if (chart->chartType == PaintChartType::ELLIPSE) {
                            copy = new Chart_Ellipse(this);
                            copy->w = chart->width();
                            copy->h = chart->height();
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::RECT) {
                            copy = new Chart_Rect(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::ROUNDRECT) {
                            copy = new Chart_RoundRect(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::LINE) {
                            copy = new Chart_Line(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::CAPSULE) {
                            copy = new Chart_Capsule(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::CIRCLE) {
                            copy = new Chart_Circle(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::PARALLELOGRAM) {
                            copy = new Chart_Parallelogram(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::DIAMOND) {
                            copy = new Chart_Diamond(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        else if (chart->chartType == PaintChartType::SUBFLORT) {
                            copy = new Chart_Subflort(this);
                            copy->setWidthHeight(chart->width()-40,chart->height()-40);
                        }
                        copy->w = chart->width();
                        copy->h = chart->height();
                        copy->chartType = chart->chartType;

                        // if (copy->chartText.textType1) copy->chartText.textType2->setText("fdfd");
                        copy->chartText.textType2->setPlainText(chart->chartText.textType2->toPlainText());
                        copy->chartText.textType2->move(chart->chartText.textType2->pos().x(),chart->chartText.textType2->pos().y());
                        qDebug() <<"color"<< chart->color;
                        // this->setcharcolor(copy,chart->color);
                        if (chart->color.isValid())
                            copy->paintChartFillPen.setColor(chart->color);
                        copy->color = chart->color;

                        auto localPos = QCursor::pos();
                        if(copy) copy->hideMagSize();
                        // copy->setXY(0,0);
                        int x = mapFromGlobal(localPos).x() - copy->w / 2;
                        int y = mapFromGlobal(localPos).y() - copy->h / 2;
                        copy->widgetStart.setX(x);
                        copy->widgetStart.setY(y);
                        curSelecChart = copy;
                        curPaintChart = copy;
                        QPair<int,int> dis = originDis.at(i++);
                        copy->setXY(x - curSelecChartPos.x() + dis.first,y + dis.second - curSelecChartPos.y());
                        copy->setWidthHeight(copy->widgetStart.rx() + copy->w - 40,copy->widgetStart.ry()+copy->h-40);
                        // curPaintChart->setXY(localPos.x(),localPos.y());

                        if(curPaintChart->chartType == PaintChartType::LINE)
                        {
                            connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                            connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                            addLine(curPaintChart);
                            Chart_Line *cl = dynamic_cast<Chart_Line*>(curSelecChart);
                            emit sendLineStyle(cl->paintChartDrawPen,cl->getStartLineHeadType(),cl->getEndLineHeadType());
                        }else
                        {
                            connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                            connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                            connect(curPaintChart,SIGNAL(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)),this,SLOT(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)));
                            //connect(curPaintChart,SIGNAL(hideThisClass()),this,SLOT(resetSeletcChart()));
                            addChart(curPaintChart);
                            emit sendChartStyle(curSelecChart->paintChartDrawPen,curSelecChart->paintChartFillPen);
                        }
                        curPaintChart->update();
                        curPaintChart->show();
                    }
                }
            }
        }
        else if (copy && curSelecCharts.empty()) {
            auto localPos = QCursor::pos();
            if(copy) copy->hideMagSize();
            // copy->setXY(0,0);
            int x = mapFromGlobal(localPos).x() - copy->w / 2;
            int y = mapFromGlobal(localPos).y() - copy->h / 2;
            copy->widgetStart.setX(x);
            copy->widgetStart.setY(y);
            curSelecChart = copy;
            curPaintChart = copy;
            copy->setWidthHeight(copy->widgetStart.rx() + copy->w - 40,copy->widgetStart.ry()+copy->h-40);
            // curPaintChart->setXY(localPos.x(),localPos.y());

            if(curPaintChart->chartType == PaintChartType::LINE)
            {
                connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                addLine(curPaintChart);
                Chart_Line *cl = dynamic_cast<Chart_Line*>(curSelecChart);
                emit sendLineStyle(cl->paintChartDrawPen,cl->getStartLineHeadType(),cl->getEndLineHeadType());
            }else
            {
                connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                connect(curPaintChart,SIGNAL(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)),this,SLOT(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)));
                //connect(curPaintChart,SIGNAL(hideThisClass()),this,SLOT(resetSeletcChart()));
                addChart(curPaintChart);
                emit sendChartStyle(curSelecChart->paintChartDrawPen,curSelecChart->paintChartFillPen);
            }
            curPaintChart->update();
            curPaintChart->show();
            //mouseEventType = MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE;
            ev->accept();
            // int width = 10 ;
            // int height = 10 ;
            Chart_Base* newcopy;
            if (copy->chartType == PaintChartType::ELLIPSE) {
                newcopy = new Chart_Ellipse(this);
                qDebug() << "??";
            }
            else if (copy->chartType == PaintChartType::RECT) {
                newcopy = new Chart_Rect(this);
            }
            else if (copy->chartType == PaintChartType::ROUNDRECT) {
                newcopy = new Chart_RoundRect(this);
                newcopy->setWidthHeight(newcopy->width()-40,newcopy->height()-40);
            }
            else if (copy->chartType == PaintChartType::LINE) {
                newcopy = new Chart_Line(this);
                newcopy->setWidthHeight(newcopy->width()-40,newcopy->height()-40);
            }
            else if (copy->chartType == PaintChartType::CAPSULE) {
                newcopy = new Chart_Capsule(this);
                newcopy->setWidthHeight(newcopy->width()-40,newcopy->height()-40);
            }
            else if (copy->chartType == PaintChartType::CIRCLE) {
                newcopy = new Chart_Circle(this);
                newcopy->setWidthHeight(newcopy->width()-40,newcopy->height()-40);
            }
            else if (copy->chartType == PaintChartType::PARALLELOGRAM) {
                newcopy = new Chart_Parallelogram(this);
                newcopy->setWidthHeight(newcopy->width()-40,newcopy->height()-40);
            }
            else if (copy->chartType == PaintChartType::DIAMOND) {
                newcopy = new Chart_Diamond(this);
                newcopy->setWidthHeight(newcopy->width()-40,newcopy->height()-40);
            }
            else if (curSelecChart->chartType == PaintChartType::SUBFLORT) {
                newcopy = new Chart_Subflort(this);
                newcopy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
            }
            newcopy->w = copy->width() ;
            newcopy->h = copy->height();
            newcopy->chartText.textType2->setPlainText(copy->chartText.textType2->toPlainText());
            newcopy->chartText.textType2->move(copy->chartText.textType2->pos().x(),copy->chartText.textType2->pos().y());
            qDebug() <<"color"<< copy->color;
            // this->setcharcolor(copy,curSelecChart->color);
            if (curSelecChart->color.isValid())
                copy->paintChartFillPen.setColor(curSelecChart->color);
            newcopy->color = copy->color;
            qDebug() << "newcopy -> w = " << copy->width();
            qDebug() << newcopy->w;
            copy = newcopy;
            qDebug() << "huihe";
        }

    }
    switch(ev->key())
    {
    case Qt::Key_Escape:
    {
        if(curSelecChart)
        {
            curSelecChart->hideMagSize();
            curSelecChart = nullptr;
        }
    }break;
    case Qt::Key_Delete:
    case Qt::Key_Backspace:
    {
        qDebug() << "del";

        if(curSelecChart)
        {
            if(curSelecChart->chartType == PaintChartType::LINE)
            {
                if(!delLine(curSelecChart))
                {
                    qDebug()<<"Error";
                }
            }else{
                if(!delChart(curSelecChart))
                {
                    qDebug()<<"Error";
                }
            }
            curSelecChart = nullptr;
        }
        if (!this->curSelecCharts.empty()) {
            qDebug() << "!emp";
            for (Chart_Base* chart : this->curSelecCharts) {
                if(chart->chartType == PaintChartType::LINE)
                {
                    if(!delLine(chart))
                    {
                        qDebug()<<"Error";
                    }
                }else{
                    if(!delChart(chart))
                    {
                        qDebug()<<"Error";
                    }
                }
                chart = nullptr;
            }
        }
    }break;
#if 0
        case Qt::Key_Q:
        {
            qDebug()<<"总个数：charts:"<<charts.size()<<",lines:"<<line.size();
            for(auto it = charts.begin();it != charts.end();it++)
            {
                qDebug()<<"\t磁力点个数："<<(*it)->magPoint.i_point.size();
                for(auto magit = (*it)->magPoint.i_point.begin();magit!=(*it)->magPoint.i_point.end();magit++)
                {
                    qDebug()<<"\t\t线头个数："<<(*magit)->i_lineStart.size()<<"，线尾个数："<<(*magit)->i_lineEnd.size();
                    for(auto magLineStIt = (*magit)->i_lineStart.begin();magLineStIt != (*magit)->i_lineStart.end();magLineStIt++)
                    {
                        qDebug()<<"\t\t\t线头ID："<<(*magLineStIt)->getID();
                    }
                    for(auto magLineEnIt = (*magit)->i_lineEnd.begin();magLineEnIt != (*magit)->i_lineEnd.end();magLineEnIt++)
                    {
                        qDebug()<<"\t\t\t线尾ID："<<(*magLineEnIt)->getID();
                    }
                }
            }
            qDebug();
            for(auto it = line.begin();it != line.end();it++)
            {
                qDebug()<<"\t线头："<<((dynamic_cast<Chart_Line*>(*it)->getStartChart() == nullptr)?"-":"有")<<"，线尾："<<(((dynamic_cast<Chart_Line*>(*it)->getEndChart()) == nullptr)?"-":"有");
            }
        }break;
#endif
    default:{
        // ev->ignore();
    }
    }
}
void FlowChart::keyReleaseEvent(QKeyEvent *ev)
{
    // ev->ignore();
}

void FlowChart::wheelEvent(QWheelEvent *event)
{
    double rate = 0.001 /3;
    if ((event->modifiers() == Qt::ControlModifier))
    {
        qDebug() << event->angleDelta().y();
        for (Chart_Base* chart : charts) {
            chart->setWidthHeight(chart->widgetEnd.x() + rate*event->angleDelta().y() * chart->width(),chart->widgetEnd.y() +rate *  event->angleDelta().y() * chart->height() );
        }
        return ;
    }
    event->ignore();
}
void FlowChart::setcharcolor(const QColor &color) {
    if (!this->curSelecChart) return ;
    if (curSelecChart->chartText.textType1) {
        QPalette palette = curSelecChart->chartText.textType1->palette();
        palette.setColor(QPalette::WindowText, color);
        curSelecChart->chartText.textType1->setPalette(palette);
    }
    curSelecChart->color = color ;
    qDebug() << "setcolor" << color ;
    if (curSelecChart->chartText.textType2) {
        QTextCursor cursor(curSelecChart->chartText.textType2->textCursor());
        cursor.select(QTextCursor::Document);


        QTextCharFormat format = cursor.charFormat();

        format.setForeground(QBrush(color));

        cursor.setCharFormat(format);
    }


    if (curSelecChart->chartText.tmpEdit1) {
        QPalette palette = curSelecChart->chartText.tmpEdit1->palette();
        palette.setColor(QPalette::Text, color);
        curSelecChart->chartText.tmpEdit1->setPalette(palette);
    }

    if (curSelecChart->chartText.tmpEdit2) {
        QTextCursor cursor(curSelecChart->chartText.tmpEdit2->textCursor());
        cursor.select(QTextCursor::Document);


        QTextCharFormat format = cursor.charFormat();

        format.setForeground(QBrush(color));

        cursor.setCharFormat(format);
    }
}

void FlowChart::setcharcolor(Chart_Base* chart,QColor color) {

    if (chart->chartText.textType1) {
        QPalette palette = chart->chartText.textType1->palette();
        palette.setColor(QPalette::WindowText, color);
        chart->chartText.textType1->setPalette(palette);
    }
    chart->color = color ;
    if (chart->chartText.textType2) {
        QTextCursor cursor(chart->chartText.textType2->textCursor());
        cursor.select(QTextCursor::Document);


        QTextCharFormat format = cursor.charFormat();

        format.setForeground(QBrush(color));

        cursor.setCharFormat(format);
    }


    if (chart->chartText.tmpEdit1) {
        QPalette palette = chart->chartText.tmpEdit1->palette();
        palette.setColor(QPalette::Text, color);
        chart->chartText.tmpEdit1->setPalette(palette);
    }

    if (chart->chartText.tmpEdit2) {
        QTextCursor cursor(chart->chartText.tmpEdit2->textCursor());
        cursor.select(QTextCursor::Document);


        QTextCharFormat format = cursor.charFormat();

        format.setForeground(QBrush(color));

        cursor.setCharFormat(format);
    }
}

void FlowChart::setchartype(const QFont &font) {
    if (!curSelecChart) return ;
    if (curSelecChart->chartText.textType1) {
        QFont currentFont = curSelecChart->chartText.textType1->font();
        currentFont.setFamily(font.family());
        currentFont.setPointSize(font.pointSize());
        curSelecChart->chartText.textType1->setFont(currentFont);
    }

    if (curSelecChart->chartText.textType2) {
        QTextCursor cursor(curSelecChart->chartText.textType2->textCursor());
        cursor.select(QTextCursor::Document);
        QTextCharFormat format = cursor.charFormat();
        format.setFont(font);
        cursor.setCharFormat(format);
    }


    if (curSelecChart->chartText.tmpEdit1) {
        QFont currentFont = curSelecChart->chartText.tmpEdit1->font();
        currentFont.setFamily(font.family());
        currentFont.setPointSize(font.pointSize());
        curSelecChart->chartText.tmpEdit1->setFont(currentFont);
    }

    if (curSelecChart->chartText.tmpEdit2) {
        QTextCursor cursor(curSelecChart->chartText.tmpEdit2->textCursor());
        cursor.select(QTextCursor::Document);
        QTextCharFormat format = cursor.charFormat();
        format.setFont(font);
        cursor.setCharFormat(format);
    }
}

bool FlowChart::chooseChartFile(QString Path)
{
    resetFlowChartPanel();
    QString tmpFilePath = Path;
    if(tmpFilePath == "") return false;

    if(loadFile(tmpFilePath) == false)
    {
        QMessageBox::critical(this->parentWidget(),tr("错误！"),tr("打开文件失败！\n文件损坏或类型不正确"),QMessageBox::Ok);
        return false;
    }else
    {
        fileIsOpened = true;
        this->filePath = tmpFilePath;
        setFileNameShow(fileIsSaved);
        qDebug()<<"Load File Success"<<fileIsSaved;
    }
    qDebug()<<"charts size:"<<charts.size()<<" line size::"<<line.size();
    return true;
}
bool FlowChart::saveChartFile_new()
{
    if (0) {
        return true;
    } else {
        if (0) {
            if (saveFile(filePath)) {
                filePath = "";
            } else {
                QMessageBox::critical(this->parentWidget(), tr("错误！"), tr("保存文件失败！\n文件已占用或者访问权限不足"), QMessageBox::Ok);
                return false;
            }
        } else {
            QString tmpFilePath = QFileDialog::getSaveFileName(nullptr, "保存文件", "", "FCT文件(*.fct);;PNG图片(*.png);;SVG文件(*.svg)");
            qDebug() << tmpFilePath;
            if (tmpFilePath.isEmpty()) return false;

            QFileInfo fileInfo(tmpFilePath);
            QString fileExtension = fileInfo.suffix().toLower();

            if (fileExtension == "fct") {
                if (saveFile(tmpFilePath)) {
                    filePath = tmpFilePath;
                    fileIsOpened = true;
                } else {
                    QMessageBox::critical(this->parentWidget(), tr("错误！"), tr("保存文件失败！\n文件已占用或者访问权限不足"), QMessageBox::Ok);
                    return false;
                }
            } else if (fileExtension == "png") {
                if (saveAsPNG(tmpFilePath)) {
                    filePath = tmpFilePath;
                    fileIsOpened = true;
                } else {
                    QMessageBox::critical(this->parentWidget(), tr("错误！"), tr("保存文件失败！\n文件已占用或者访问权限不足"), QMessageBox::Ok);
                    return false;
                }
            } else if (fileExtension == "svg") {
                if (saveAsSVG(tmpFilePath)) {
                    filePath = tmpFilePath;
                    fileIsOpened = true;
                } else {
                    QMessageBox::critical(this->parentWidget(), tr("错误！"), tr("保存文件失败！\n文件已占用或者访问权限不足"), QMessageBox::Ok);
                    return false;
                }
            } else {
                QMessageBox::critical(this->parentWidget(), tr("错误！"), tr("不支持的文件格式"), QMessageBox::Ok);
                return false;
            }
            qDebug() << "sca";
        }
        setFileSetSaved(true);
    }
    return true;
}

