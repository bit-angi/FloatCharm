#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <qguiapplication.h>
#include "dialog.h"
#include "floatchatwindow.h"
#include "charwidget.h"
#include "ui_floatchatwindow.h"
#include "flowchart.h"
#include <QGraphicsDropShadowEffect>
#include "ui_charwidget.h"
#include <QScreen>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    // QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    // shadowEffect->setBlurRadius(20);  // 增加模糊半径
    // shadowEffect->setOffset(5, 5);    // 增加偏移量
    // shadowEffect->setColor(QColor(0, 0, 0, 200));  // 增加不透明度（颜色更深）

    // // 将阴影效果应用到按钮
    // ui->pushButton->setGraphicsEffect(shadowEffect);
    // ui->pushButton_2->setGraphicsEffect(shadowEffect);  // 如果有多个按钮，可以重复使用
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_clicked()
{
    // 创建并显示 FloatChatWindow 对象
    FloatChatWindow *f = new FloatChatWindow(this);
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    // 计算屏幕中心的位置
    int x = (screenGeometry.width() - f->width()) / 2;
    int y = (screenGeometry.height() - f->height()) / 2;

    // 移动窗口到屏幕中心
    f->move(x, y);

    f->show();


    // 假设 FloatChatWindow 的构造函数或某个初始化函数中已经向 tabWidget 添加了 CharWidget
    CharWidget *currentWidget = qobject_cast<CharWidget*>(f->ui->tabWidget->currentWidget());

    // 检查 currentWidget 是否成功获取，并且内部的 widget 是否有效
    if (currentWidget && currentWidget->ui && currentWidget->ui->widget) {
        FlowChart *chart = currentWidget->ui->widget;
        chart->openChartFile();
    } else {
        qDebug() << "Failed to cast current widget to CharWidget or CharWidget's UI is not properly initialized.";
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    Dialog *myDialog = new Dialog(this);
    myDialog->show();//显示对话
    //创建并显示 FloatChatWindow 对象
}

void MainWindow::on_pushButton_3_clicked()
{
    this->close();
}

