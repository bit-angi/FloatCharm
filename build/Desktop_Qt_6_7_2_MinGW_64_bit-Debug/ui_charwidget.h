/********************************************************************************
** Form generated from reading UI file 'charwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARWIDGET_H
#define UI_CHARWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include <flowchart.h>

QT_BEGIN_NAMESPACE

class Ui_CharWidget
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_10;
    FlowChart *widget;

    void setupUi(QWidget *CharWidget)
    {
        if (CharWidget->objectName().isEmpty())
            CharWidget->setObjectName("CharWidget");
        CharWidget->resize(1000, 500);
        CharWidget->setStyleSheet(QString::fromUtf8("background-color:white"));
        gridLayout = new QGridLayout(CharWidget);
        gridLayout->setObjectName("gridLayout");
        scrollArea = new QScrollArea(CharWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setStyleSheet(QString::fromUtf8("QScrollBar:vertical {\n"
"    width: 8px;\n"
"    background: transparent;\n"
"    margin: 0px;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"QScrollBar::handle:vertical {\n"
"    width: 8px;\n"
"    background: rgba(69, 178, 255, 90%);\n"
"    border-radius: 4px;\n"
"    min-height: 20px;\n"
"}\n"
"QScrollBar::handle:vertical:hover {\n"
"    width: 8px;\n"
"    background: rgba(69, 178, 255, 100%);\n"
"    border-radius: 4px;\n"
"    min-height: 20px;\n"
"}\n"
"QScrollBar::add-line:vertical {\n"
"    height: 0px;\n"
"    width: 8px;\n"
"    subcontrol-position: bottom;\n"
"}\n"
"QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"    width: 8px;\n"
"    subcontrol-position: top;\n"
"}\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"    background: #E8EAEF;\n"
"    border-radius: 4px;\n"
"}\n"
"QScrollBar:horizontal {\n"
"    height: 8px;\n"
"    background: transparent;\n"
"    margin: 0px;\n"
"    padding-left: 0px;\n"
"    padding-right: 0px;\n"
"}\n"
"QScrollB"
                        "ar::handle:horizontal {\n"
"    height: 8px;\n"
"    background: rgba(69, 178, 255, 90%);\n"
"    border-radius: 4px;\n"
"    min-width: 20px;\n"
"}\n"
"QScrollBar::handle:horizontal:hover {\n"
"    height: 8px;\n"
"    background: rgba(69, 178, 255, 100%);\n"
"    border-radius: 4px;\n"
"    min-width: 20px;\n"
"}\n"
"QScrollBar::add-line:horizontal {\n"
"    width: 0px;\n"
"    height: 8px;\n"
"    subcontrol-position: right;\n"
"}\n"
"QScrollBar::sub-line:horizontal {\n"
"    width: 0px;\n"
"    height: 8px;\n"
"    subcontrol-position: left;\n"
"}\n"
"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {\n"
"    background: #E8EAEF;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
""));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents_10 = new QWidget();
        scrollAreaWidgetContents_10->setObjectName("scrollAreaWidgetContents_10");
        scrollAreaWidgetContents_10->setGeometry(QRect(0, 0, 1550, 1550));
        widget = new FlowChart(scrollAreaWidgetContents_10);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 1550, 1550));
        widget->setStyleSheet(QString::fromUtf8("background-color:white"));
        scrollArea->setWidget(scrollAreaWidgetContents_10);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(CharWidget);

        QMetaObject::connectSlotsByName(CharWidget);
    } // setupUi

    void retranslateUi(QWidget *CharWidget)
    {
        CharWidget->setWindowTitle(QCoreApplication::translate("CharWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CharWidget: public Ui_CharWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARWIDGET_H
