#include "charwidget.h"
#include "floatchatwindow.h"
#include "ui_charwidget.h"
#include "ui_floatchatwindow.h"
#include <QFontDialog>
#include <QSpinBox>
#include <class_Charts/chart_capsule.h>
#include <class_Charts/chart_circle.h>
#include <class_Charts/chart_image.h>
#include <class_Charts/chart_parallelogram.h>
#include <class_Charts/chart_subflort.h>

FloatChatWindow::FloatChatWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FloatChatWindow)
{
    // setWindowState(Qt::WindowFullScreen);

    showMaximized();
    ui->setupUi(this);
    this->ui->checkBox->setCheckState(Qt::Checked);
    setWindowTitle(tr("TabWidget"));//设置标题
    ui->tabWidget->clear();//清空选项卡
    ui->tabWidget->setTabsClosable(true);
    CharWidget* widget = new CharWidget(this);
    // connect(widget->ui->widget,&FlowChart::changeText,this,[=]() {
    //     QFont font = widget->ui->widget->getCurSeleChart()->chartText.textType2->font();
    //     qDebug() <<"font"<< font.family();
    // })  ;
    ui->lineEdit->setPlaceholderText("搜索文本");
    ui->lineEdit_2->setPlaceholderText("替换文本");
    ui->tabWidget->addTab(widget,tr("new"));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    connect(ui->pushButton,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Ellipse()));
    connect(ui->pushButton_jx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Rect()));
    connect(ui->pushButton_yjjx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_RoundRect()));
    connect(ui->pushButton_line,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Line()));
    connect(ui->pushButton_pxsbx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_parallelogram()));
    connect(ui->pushButton_sjx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_triangle()));
    connect(ui->pushButton_lx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Diamond()));
    connect(ui->pushButton_tx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_trapezoid()));
    connect(ui->pushButton_yx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_circle()));
    connect(ui->pushButton_jnjx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_capsule()));
    connect(ui->pushButton_tx_2,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_subflort()));
    connect(widget->ui->widget,&FlowChart::doubleClick,this,[=]() {
        qDebug() << "double";
        if (!widget->ui->widget->curSelecChart) return ;
        QFont font = widget->ui->widget->curSelecChart->font();
        int val = font.pointSize();
        qDebug() << "val: " << val ;
        this->ui->spinBox->setValue(val);
    });
//    connect(ui->spinBox,&QSpinBox::valueChanged,this,[=](int val) {

//    });
    ui->tabWidget->addTab(widget, "New Tab");
    // 新建流程图
    connect(this->ui->actionnew_2,&QAction::triggered,this,[=](){
        CharWidget* widget = new CharWidget(this);
        ui->tabWidget->addTab(widget,tr("new"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
        connect(ui->pushButton,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Ellipse()));
        connect(ui->pushButton_jx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Rect()));
        connect(ui->pushButton_yjjx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_RoundRect()));
        connect(ui->pushButton_line,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Line()));
        connect(ui->pushButton_pxsbx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_parallelogram()));
        connect(ui->pushButton_sjx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_triangle()));
        connect(ui->pushButton_lx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Diamond()));
        connect(ui->pushButton_tx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_trapezoid()));
        connect(ui->pushButton_yx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_circle()));
        connect(ui->pushButton_jnjx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_capsule()));
        connect(ui->pushButton_tx_2,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_subflort()));
    });
    // 保存文件
    connect(ui->actionsave,&QAction::triggered,this,[=]() {
        FlowChart *chart = (qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget()))->ui->widget;
        chart->saveChartFile();
    });

    connect(ui->action,&QAction::triggered,this,[=]() {
        CharWidget* widget = new CharWidget(this);
        ui->tabWidget->addTab(widget,tr("new"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
        connect(ui->pushButton,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Ellipse()));
        connect(ui->pushButton_jx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Rect()));
        connect(ui->pushButton_yjjx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_RoundRect()));
        connect(ui->pushButton_line,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Line()));
        connect(ui->pushButton_pxsbx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_parallelogram()));
        connect(ui->pushButton_sjx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_triangle()));
        connect(ui->pushButton_lx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Diamond()));
        connect(ui->pushButton_tx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_trapezoid()));
        connect(ui->pushButton_yx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_circle()));
        connect(ui->pushButton_jnjx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_capsule()));
        connect(ui->pushButton_tx_2,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_subflort()));
        CharWidget *currentWidget = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget());

        if (currentWidget && currentWidget->ui && currentWidget->ui->widget) {
            FlowChart *chart = currentWidget->ui->widget;
            chart->openChartFile();
        } else {
            qDebug() << "Failed to cast current widget to CharWidget or CharWidget's UI is not properly initialized.";
        }
    });
    //颜色填充
    connect(this, &FloatChatWindow::colorSelected, this, [=](QColor color) {
        // 动态转换 currentWidget() 为 CharWidget 类型
        CharWidget *currentWidget = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget());

        if (currentWidget && currentWidget->ui && currentWidget->ui->widget) {
            FlowChart *chart = currentWidget->ui->widget;
            chart->setSelChartFillColor(color);
        } else {
            qDebug() << "Failed to cast current widget to CharWidget or CharWidget's UI is not properly initialized.";
        }
    });
    //线条颜色变化

    connect(this,&FloatChatWindow::colorSelected2,this,[=](QColor color){
        CharWidget *currentWidget = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget());
        if (currentWidget && currentWidget->ui && currentWidget->ui->widget) {
            FlowChart *chart = currentWidget->ui->widget;
            chart->setSelChartLineColor(color);
        } else {
            qDebug() << "Failed to cast current widget to CharWidget or CharWidget's UI is not properly initialized.";
        }
    });

    //字体颜色变化

    connect(this,&FloatChatWindow::colorSelected3,this,[=](QColor color){
        CharWidget *currentWidget = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget());
        if (currentWidget && currentWidget->ui && currentWidget->ui->widget) {
            FlowChart *chart = currentWidget->ui->widget;
            chart->setcharcolor(color);
        } else {
            qDebug() << "Failed to cast current widget to CharWidget or CharWidget's UI is not properly initialized.";
        }
    });

    //字体类型变化

    connect(this,&FloatChatWindow::fontselected,this,[=](QFont font){
        CharWidget *currentWidget = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget());
        if (currentWidget && currentWidget->ui && currentWidget->ui->widget) {
            FlowChart *chart = currentWidget->ui->widget;
            chart->setchartype(font);
        } else {
            qDebug() << "Failed to cast current widget to CharWidget or CharWidget's UI is not properly initialized.";
        }
    });




}

FloatChatWindow::~FloatChatWindow()
{
    delete ui;
}

void FloatChatWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}


void FloatChatWindow::on_pushButton_clicked()
{

}


void FloatChatWindow::on_pushButton_9_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,tr("设置填充颜色"));
    if (color.isValid()) { // 检查颜色是否有效
        emit colorSelected(color); // 发出信号
    }
    // ui->tabWidget->setSelChartFillColor(color);
    // ui->FillColorButton->setStyleSheet(QString("QPushButton\
    //                                            {\
    //                                                    background-color:rgb(%1,%2,%3);\
    //                                                    opacity:1;\
    //                                            };"
    //                                            ).arg(color.red()).arg(color.green()).arg(color.blue()));

}


void FloatChatWindow::on_pushButton_11_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,tr("设置填充颜色"));
    if (color.isValid()) { // 检查颜色是否有效
        emit colorSelected3(color); // 发出信号
    }
}


void FloatChatWindow::on_pushButton_10_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,tr("设置线条颜色"));
    emit colorSelected2(color);
}


void FloatChatWindow::on_pushButton_12_clicked()
{
    QFontDialog fontDialog(this);
    fontDialog.setWindowTitle(tr("选择字体"));
    if (fontDialog.exec() == QDialog::Accepted) {
        QFont font = fontDialog.selectedFont();
        emit fontselected(font);
    }
}




void FloatChatWindow::on_pushButton_2_clicked()
{
    Chart_Base* curSelecChart = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget())->ui->widget->getCurSeleChart();
    FlowChart* chart = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget())->ui->widget;
    if (curSelecChart) {
        if (curSelecChart->chartType == PaintChartType::ELLIPSE) {
            chart->copy = new Chart_Ellipse(chart);
            chart->copy->w = curSelecChart->width();
            chart->copy->h = curSelecChart->height();
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::RECT) {
            chart->copy = new Chart_Rect(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::ROUNDRECT) {
            chart->copy = new Chart_RoundRect(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::LINE) {
            chart->copy = new Chart_Line(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::CAPSULE) {
            chart->copy = new Chart_Capsule(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::CIRCLE) {
            chart->copy = new Chart_Circle(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::PARALLELOGRAM) {
            chart->copy = new Chart_Parallelogram(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::DIAMOND) {
            chart->copy = new Chart_Diamond(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::SUBFLORT) {
            chart->copy = new Chart_Subflort(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        chart->copy->w = curSelecChart->width();
        chart->copy->h = curSelecChart->height();
        chart->copy->chartType = curSelecChart->chartType;

        // if (chart->copy->chartText.textType1) chart->copy->chartText.textType2->setText("fdfd");
        chart->copy->chartText.textType2->setPlainText(curSelecChart->chartText.textType2->toPlainText());
        chart->copy->chartText.textType2->move(curSelecChart->chartText.textType2->pos().x(),curSelecChart->chartText.textType2->pos().y());
        qDebug() <<"color"<< curSelecChart->color;
        // this->setcharcolor(chart->copy,curSelecChart->color);
        if (curSelecChart->color.isValid())
            chart->copy->paintChartFillPen.setColor(curSelecChart->color);
        chart->copy->color = curSelecChart->color;
        // chart->copy->update();
    }
    qDebug() << "del";
    if(curSelecChart)
    {
        if(curSelecChart->chartType == PaintChartType::LINE)
        {
            if(!chart->delLine(curSelecChart))
            {
                qDebug()<<"Error";
            }
        }else{
            if(!chart->delChart(curSelecChart))
            {
                qDebug()<<"Error";
            }
        }
        curSelecChart = nullptr;
    }
}


void FloatChatWindow::on_pushButton_4_clicked()
{
    FlowChart *chart = (qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget()))->ui->widget;
    chart->saveChartFile();
}


void FloatChatWindow::on_pushButton_5_clicked()
{
    FlowChart *chart = (qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget()))->ui->widget;
    for (Chart_Base * _chart : chart->charts) {
        chart->delChart(_chart);
    }
}


void FloatChatWindow::on_pushButton_3_clicked()
{
    Chart_Base* curSelecChart = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget())->ui->widget->getCurSeleChart();
    FlowChart* chart = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget())->ui->widget;
    if (curSelecChart) {
        if (curSelecChart->chartType == PaintChartType::ELLIPSE) {
            chart->copy = new Chart_Ellipse(chart);
            chart->copy->w = curSelecChart->width();
            chart->copy->h = curSelecChart->height();
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::RECT) {
            chart->copy = new Chart_Rect(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::ROUNDRECT) {
            chart->copy = new Chart_RoundRect(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::LINE) {
            chart->copy = new Chart_Line(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::CAPSULE) {
            chart->copy = new Chart_Capsule(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::CIRCLE) {
            chart->copy = new Chart_Circle(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::PARALLELOGRAM) {
            chart->copy = new Chart_Parallelogram(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::DIAMOND) {
            chart->copy = new Chart_Diamond(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        else if (curSelecChart->chartType == PaintChartType::SUBFLORT) {
            chart->copy = new Chart_Subflort(chart);
            chart->copy->setWidthHeight(curSelecChart->width()-40,curSelecChart->height()-40);
        }
        chart->copy->w = curSelecChart->width();
        chart->copy->h = curSelecChart->height();
        chart->copy->chartType = curSelecChart->chartType;

        // if (chart->copy->chartText.textType1) chart->copy->chartText.textType2->setText("fdfd");
        chart->copy->chartText.textType2->setPlainText(curSelecChart->chartText.textType2->toPlainText());
        chart->copy->chartText.textType2->move(curSelecChart->chartText.textType2->pos().x(),curSelecChart->chartText.textType2->pos().y());
        qDebug() <<"color"<< curSelecChart->color;
        // this->setcharcolor(chart->copy,curSelecChart->color);
        if (curSelecChart->color.isValid())
            chart->copy->paintChartFillPen.setColor(curSelecChart->color);
        chart->copy->color = curSelecChart->color;
        // chart->copy->update();
    }
}


void FloatChatWindow::on_pushButton_6_clicked()
{
    FlowChart* chart = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget())->ui->widget;
    if (!chart->curSelecChart) return ;
    QFont font = chart->curSelecChart->chartText.textType1->font();
    if (isBold) {
        font.setWeight(QFont::Normal);
        isBold = false ;
    }
    else {
        font.setWeight(QFont::Bold);
        isBold = true ;
    }
    chart->setchartype(font);
    chart->curSelecChart->chartText.textType2->setFont(font);
}


void FloatChatWindow::on_pushButton_7_clicked()
{
    FlowChart* chart = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget())->ui->widget;
    if (!chart->curSelecChart) return ;
    QFont font = chart->curSelecChart->chartText.textType1->font();
    font.setItalic(!isItal);
    isItal = !isItal;
    chart->setchartype(font);
    chart->curSelecChart->chartText.textType2->setFont(font);
}

void FloatChatWindow::on_pushButton_8_clicked()
{
    FlowChart* chart = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget())->ui->widget;
    if (!chart->curSelecChart) return ;
    QFont font = chart->curSelecChart->chartText.textType1->font();
    font.setUnderline(!underlined);
    underlined = !underlined;
    chart->setchartype(font);
    chart->curSelecChart->chartText.textType2->setFont(font);
}



void FloatChatWindow::on_pushButton_13_clicked()
{
    CharWidget *currentWidget = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget());
    if (currentWidget && currentWidget->ui && currentWidget->ui->widget) {
        FlowChart *chart = currentWidget->ui->widget;
        chart->rotate();
    }

}


void FloatChatWindow::on_checkBox_checkStateChanged(const Qt::CheckState &arg1)
{
    CharWidget *currentWidget = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget());
    if (!currentWidget) return ;
    qDebug() << arg1;
    if (arg1 == Qt::Checked) {
        currentWidget->grinOn = true  ;
        currentWidget->ui->widget->gridOn = true ;
        currentWidget->update();
        currentWidget->ui->widget->update();
    }
    else{
        qDebug() << "false ";
        currentWidget->grinOn = false ;
        currentWidget->ui->widget->gridOn = false ;
        currentWidget->update();
        currentWidget->ui->widget->update();
    }
}


void FloatChatWindow::on_pushButton_tx_2_clicked()
{

}


void FloatChatWindow::on_lineEdit_textChanged(const QString &arg1)
{
    CharWidget *currentWidget = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget());
    this->ui->lineEdit->grabKeyboard();
    for (Chart_Base* chart : currentWidget->ui->widget->charts) {
        QString text = chart->chartText.textType2->toPlainText();
        if (text.contains(arg1)) {
            chart->chartText.textType2->setHtml(text.left(text.indexOf(arg1)) + "<span style='background-color: yellow;'>"+ arg1 +"</span>" + text.right(text.length() -text.indexOf(arg1) - arg1.length()));
        }
    }
}


void FloatChatWindow::on_lineEdit_returnPressed()
{

}


void FloatChatWindow::on_pushButton_14_clicked()
{
    QString arg1 = ui->lineEdit->text();
    CharWidget *currentWidget = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget());
    this->ui->lineEdit->grabKeyboard();
    for (Chart_Base* chart : currentWidget->ui->widget->charts) {
        QString text = chart->chartText.textType2->toPlainText();
        if (text.contains(arg1)) {
            chart->chartText.textType2->setHtml(text.left(text.indexOf(arg1)) + this->ui->lineEdit_2->text() + text.right(text.length() -text.indexOf(arg1) - arg1.length()));
        }
    }
}


void FloatChatWindow::on_pushButton_15_clicked()
{
    CharWidget *currentWidget = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget());
    QString tmpFilePath = QFileDialog::getOpenFileName(this,tr("打开文件"),"F:",tr("PNG文件(*.png)"));
    if(tmpFilePath == "") return ;

    Chart_Image *chartImage = new Chart_Image(currentWidget->ui->widget);
    chartImage->image = QImage(tmpFilePath);
    currentWidget->ui->widget->curPaintChart = chartImage;
    currentWidget->ui->widget->mouseEventType = MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE;
}


void FloatChatWindow::on_pushButton_tx_clicked()
{

}


void FloatChatWindow::on_pushButton_tx_3_clicked()
{
    CharWidget *currentWidget = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget());
    QString tmpFilePath = QFileDialog::getOpenFileName(this,tr("打开文件"),"F:",tr("PNG文件(*.png)"));
    if(tmpFilePath == "") return ;

    Chart_Image *chartImage = new Chart_Image(currentWidget->ui->widget);
    chartImage->image = QImage(tmpFilePath);
    currentWidget->ui->widget->curPaintChart = chartImage;
    currentWidget->ui->widget->mouseEventType = MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE;
}
void FloatChatWindow::choice_tabOpen(QString Path)
{
    CharWidget* widget = new CharWidget(this);
    this->ui->tabWidget->addTab(widget,tr("new"));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    connect(ui->pushButton,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Ellipse()));
    connect(ui->pushButton_jx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Rect()));
    connect(ui->pushButton_yjjx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_RoundRect()));
    connect(ui->pushButton_line,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Line()));
    connect(ui->pushButton_pxsbx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_parallelogram()));
    connect(ui->pushButton_sjx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_triangle()));
    connect(ui->pushButton_lx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_Diamond()));
    connect(ui->pushButton_tx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_trapezoid()));
    connect(ui->pushButton_yx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_circle()));
    connect(ui->pushButton_jnjx,SIGNAL(clicked()),widget->ui->widget,SLOT(setPaintChart_capsule()));
    CharWidget *currentWidget = qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget());

    if (currentWidget && currentWidget->ui && currentWidget->ui->widget) {
        FlowChart *chart = currentWidget->ui->widget;
        chart->chooseChartFile(Path);
    } else {
        qDebug() << "Failed to cast current widget to CharWidget or CharWidget's UI is not properly initialized.";
    }
}

void FloatChatWindow::choice_new()
{
    FlowChart *chart = (qobject_cast<CharWidget*>(this->ui->tabWidget->currentWidget()))->ui->widget;
    chart->saveChartFile_new();
}

void FloatChatWindow::on_spinBox_valueChanged(int val)
{
    CharWidget* widget = qobject_cast<CharWidget*>(ui->tabWidget->currentWidget());
    qDebug() << "val2" << val ;
    if (!widget->ui->widget->curSelecChart) return ;
    QFont font = widget->ui->widget->curSelecChart->font();
    font.setPointSize(val);
    widget->ui->widget->curSelecChart->chartText.textType2->setFont(font);
    if (widget->ui->widget->curSelecChart->chartText.tmpEdit1) widget->ui->widget->curSelecChart->chartText.tmpEdit1->setFont(font);
    if (widget->ui->widget->curSelecChart->chartText.tmpEdit2) widget->ui->widget->curSelecChart->chartText.tmpEdit2->setFont(font);
}


void FloatChatWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    this->ui->lineEdit->grabKeyboard();
}

