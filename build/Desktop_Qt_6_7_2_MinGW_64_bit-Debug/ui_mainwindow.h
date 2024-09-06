/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *widget;
    QPushButton *pushButton_3;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(110, 200, 180, 180));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton:hover {\n"
"    background-color: rgb(170, 170, 170);\n"
"    box-shadow: 0px 4px 10px rgba(0, 0, 0, 0.2);\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icons/baocun.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(200, 180));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(480, 200, 180, 180));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton:hover {\n"
"    background-color: rgb(170, 170, 170);\n"
"    box-shadow: 0px 4px 10px rgba(0, 0, 0, 0.2);\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icons/jiahao.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_2->setIcon(icon1);
        pushButton_2->setIconSize(QSize(160, 160));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(150, 420, 101, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 14pt \"Microsoft YaHei UI\";"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(530, 420, 101, 31));
        label_3->setStyleSheet(QString::fromUtf8("font: 14pt \"Microsoft YaHei UI\";"));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(-10, 0, 871, 80));
        widget->setStyleSheet(QString::fromUtf8("background-color:rgb(70,70,70)"));
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(750, 20, 51, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color:rgb(240,240,240)"));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 5, 281, 71));
        label->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Microsoft YaHei UI\";\n"
"color :white;"));
        MainWindow->setCentralWidget(centralwidget);
        widget->raise();
        pushButton->raise();
        pushButton_2->raise();
        label_2->raise();
        label_3->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\265\201\347\250\213\345\233\276", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\346\265\201\347\250\213\345\233\276", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\254\242\350\277\216\344\275\277\347\224\250\346\265\201\347\250\213\345\233\276\347\274\226\350\276\221\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
