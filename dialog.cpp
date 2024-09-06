#include "dialog.h"
#include "ui_dialog.h"
#include "floatchatwindow.h"
#include <QGraphicsDropShadowEffect>
#include "flowchart.h"
#include <QTabWidget>
#include "charwidget.h"
#include "ui_charwidget.h"
#include "ui_floatchatwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QScreen>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QString style =
            "QPushButton{"
            "background-color: rgba(223, 223, 223,0);"
            "}"
            "QPushButton:pressed {"
            "background-color: darkgray;"
            "}"
            "QPushButton:hover {"
            "background-color: rgba(223, 223, 223,0.5);"
            "}";

    ui->mode1->setStyleSheet(style);
    ui->mode2->setStyleSheet(style);
    ui->mode3->setStyleSheet(style);
    ui->mode4->setStyleSheet(style);
    ui->mode5->setStyleSheet(style);
    ui->add_mode->setStyleSheet(style);
    ui->nothing->setStyleSheet(style);//设置悬浮样式

    QGraphicsDropShadowEffect *effect[5];
    for (int i=0;i<5;i++)
    {
        effect[i] = new QGraphicsDropShadowEffect();
        effect[i]->setBlurRadius(15);
        effect[i]->setOffset(5, 5);
        effect[i]->setColor(QColor(0, 0, 0, 10));
    }//构建阴影特效

    ui->frame_1->setGraphicsEffect(effect[0]);
    ui->frame_2->setGraphicsEffect(effect[1]);
    ui->frame_3->setGraphicsEffect(effect[2]);
    ui->frame_4->setGraphicsEffect(effect[3]);
    ui->frame_5->setGraphicsEffect(effect[4]);//设置阴影效果

    connect(ui->mode1,SIGNAL(clicked()),this,SLOT(choice1()));
    connect(ui->mode2,SIGNAL(clicked()),this,SLOT(choice2()));
    connect(ui->mode3,SIGNAL(clicked()),this,SLOT(choice3()));
    connect(ui->mode4,SIGNAL(clicked()),this,SLOT(choice4()));
    connect(ui->mode5,SIGNAL(clicked()),this,SLOT(choice5()));
    connect(ui->nothing,SIGNAL(clicked()),this,SLOT(choice_nothing()));
    connect(ui->add_mode,SIGNAL(clicked()),this,SLOT(add_mode()));

}



Dialog::~Dialog()
{
    delete ui;
}

void Dialog::choice1()
{
    FloatChatWindow *f = new FloatChatWindow(this);
    // 假设 FloatChatWindow 的构造函数或某个初始化函数中已经向 tabWidget 添加了 CharWidget
    CharWidget *currentWidget = qobject_cast<CharWidget*>(f->ui->tabWidget->currentWidget());
     QString filePath = ":/mode/mode6.fct";
    // 检查 currentWidget 是否成功获取，并且内部的 widget 是否有效
    if (currentWidget && currentWidget->ui && currentWidget->ui->widget) {
        FlowChart *chart = currentWidget->ui->widget;
        chart->chooseChartFile(filePath);
    } else {
        qDebug() << "Failed to cast current widget to CharWidget or CharWidget's UI is not properly initialized.";
    }
    f->choice_new();//根据模板新建一个文件
    f->on_tabWidget_tabCloseRequested(0);//自动删除模板文件子页面
    f->choice_tabOpen(filePath);
    this->close();
}

void Dialog::choice2()
{

    FloatChatWindow *f = new FloatChatWindow(this);
    // 假设 FloatChatWindow 的构造函数或某个初始化函数中已经向 tabWidget 添加了 CharWidget
    CharWidget *currentWidget = qobject_cast<CharWidget*>(f->ui->tabWidget->currentWidget());
    QString filePath = ":/mode/mode5.fct";

    // 检查 currentWidget 是否成功获取，并且内部的 widget 是否有效
    if (currentWidget && currentWidget->ui && currentWidget->ui->widget) {
        FlowChart *chart = currentWidget->ui->widget;
        chart->chooseChartFile(filePath);
    } else {
        qDebug() << "Failed to cast current widget to CharWidget or CharWidget's UI is not properly initialized.";
    }
    f->choice_new();//根据模板新建一个文件
    f->on_tabWidget_tabCloseRequested(0);//自动删除模板文件子页面
    f->choice_tabOpen(filePath);

    this->close();

}

void Dialog::choice3()
{
    FloatChatWindow *f = new FloatChatWindow(this);
    // 假设 FloatChatWindow 的构造函数或某个初始化函数中已经向 tabWidget 添加了 CharWidget
    CharWidget *currentWidget = qobject_cast<CharWidget*>(f->ui->tabWidget->currentWidget());
    QString filePath = ":/mode/mode3.fct";
    // 检查 currentWidget 是否成功获取，并且内部的 widget 是否有效
    if (currentWidget && currentWidget->ui && currentWidget->ui->widget) {
        FlowChart *chart = currentWidget->ui->widget;
        chart->chooseChartFile(filePath);
    } else {
        qDebug() << "Failed to cast current widget to CharWidget or CharWidget's UI is not properly initialized.";
    }
    f->choice_new();//根据模板新建一个文件
    f->on_tabWidget_tabCloseRequested(0);//自动删除模板文件子页面
    f->choice_tabOpen(filePath);
    this->close();
}

void Dialog::choice4()
{
    FloatChatWindow *f = new FloatChatWindow(this);
    // 假设 FloatChatWindow 的构造函数或某个初始化函数中已经向 tabWidget 添加了 CharWidget
    CharWidget *currentWidget = qobject_cast<CharWidget*>(f->ui->tabWidget->currentWidget());
    QString filePath = ":/mode/mode4.fct";
    // 检查 currentWidget 是否成功获取，并且内部的 widget 是否有效
    if (currentWidget && currentWidget->ui && currentWidget->ui->widget) {
        FlowChart *chart = currentWidget->ui->widget;
        chart->chooseChartFile(filePath);
    } else {
        qDebug() << "Failed to cast current widget to CharWidget or CharWidget's UI is not properly initialized.";
    }
    f->choice_new();//根据模板新建一个文件
    f->on_tabWidget_tabCloseRequested(0);//自动删除模板文件子页面
    f->choice_tabOpen(filePath);

    this->close();
}

void Dialog::choice5()
{
    FloatChatWindow *f = new FloatChatWindow(this);
    // 假设 FloatChatWindow 的构造函数或某个初始化函数中已经向 tabWidget 添加了 CharWidget
    CharWidget *currentWidget = qobject_cast<CharWidget*>(f->ui->tabWidget->currentWidget());
    QString filePath = ":/mode/mode5.fct";
    // 检查 currentWidget 是否成功获取，并且内部的 widget 是否有效
    if (currentWidget && currentWidget->ui && currentWidget->ui->widget) {
        FlowChart *chart = currentWidget->ui->widget;
        chart->chooseChartFile(filePath);
    } else {
        qDebug() << "Failed to cast current widget to CharWidget or CharWidget's UI is not properly initialized.";
    }
    f->choice_new();//根据模板新建一个文件
    // f->on_tabWidget_tabCloseRequested(0);//自动删除模板文件子页面
    // f->choice_tabOpen(filePath);

    this->close();
}

void Dialog::choice_nothing()
{
    this->close();
    FloatChatWindow *f = new FloatChatWindow(this);

    // 获取主屏幕的几何属性
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    // 计算屏幕中心的位置
    int x = (screenGeometry.width() - f->width()) / 2;
    int y = (screenGeometry.height() - f->height()) / 2;

    // 移动窗口到屏幕中心
    f->move(x, y);

    f->show();
}

void Dialog::add_mode()
{
    //将文件中的mode5修改为新导入的文件
    // 打开文件选择对话框
    QString sourceFilePath = QFileDialog::getOpenFileName(nullptr, "选择文件","F:",tr("FCT文件(*.fct)"));
    if (sourceFilePath.isEmpty()) {
        QMessageBox::warning(nullptr, "警告", "没有选择文件！");
        return;
    }

    // 设置目标文件路径
    QString targetFilePath = ":/mode/mode5.fct";
    // 检查目标文件是否存在
    QFile targetFile(targetFilePath);
    if (targetFile.exists()) {
        // 如果存在，可以选择是否覆盖
        int ret = QMessageBox::warning(nullptr, "注意", "目标文件已存在，是否覆盖？",
                                       QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::No) {
            return;
        }
    }

    // 复制文件
    QFile sourceFile(sourceFilePath);
    if (!sourceFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "错误", "无法打开源文件！");
    }

    QFile targetFile2(targetFilePath);
    if (!targetFile2.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(nullptr, "错误", "无法打开目标文件！");
    }

    // 进行文件复制
    targetFile2.write(sourceFile.readAll());
    sourceFile.close();
    targetFile2.close();

    QMessageBox::information(nullptr, "成功", "文件复制成功！");
}



void Dialog::on_mode1_clicked()
{

}

