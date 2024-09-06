/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *add_mode;
    QPushButton *nothing;
    QLabel *label;
    QPushButton *mode1;
    QPushButton *mode2;
    QPushButton *mode3;
    QPushButton *mode4;
    QPushButton *mode5;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *frame_1;
    QLabel *frame_2;
    QLabel *frame_3;
    QLabel *frame_4;
    QLabel *frame_5;
    QLabel *icon_1;
    QLabel *icon_2;
    QLabel *icon_3;
    QLabel *icon_4;
    QLabel *icon_5;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(560, 459);
        Dialog->setStyleSheet(QString::fromUtf8("/*font: 290 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221 Light\";*/"));
        add_mode = new QPushButton(Dialog);
        add_mode->setObjectName("add_mode");
        add_mode->setGeometry(QRect(400, 350, 111, 41));
        add_mode->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"background-color: rgb(0,0,0);\n"
"color:white;\n"
"font: 700 9pt \"Microsoft YaHei UI\";"));
        nothing = new QPushButton(Dialog);
        nothing->setObjectName("nothing");
        nothing->setGeometry(QRect(400, 250, 111, 41));
        nothing->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"background-color: rgb(0,0,0);\n"
"color:white;\n"
"font: 700 9pt \"Microsoft YaHei UI\";"));
        label = new QLabel(Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 10, 161, 51));
        label->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,0);\n"
"font: 290 8pt \"\345\276\256\350\275\257\351\233\205\351\273\221 Light\";"));
        mode1 = new QPushButton(Dialog);
        mode1->setObjectName("mode1");
        mode1->setGeometry(QRect(40, 100, 121, 101));
        mode1->setStyleSheet(QString::fromUtf8("background-color: rgba(223, 223, 223,0.1);"));
        mode2 = new QPushButton(Dialog);
        mode2->setObjectName("mode2");
        mode2->setGeometry(QRect(220, 100, 121, 101));
        mode2->setStyleSheet(QString::fromUtf8(""));
        mode3 = new QPushButton(Dialog);
        mode3->setObjectName("mode3");
        mode3->setGeometry(QRect(400, 100, 121, 101));
        mode3->setStyleSheet(QString::fromUtf8(""));
        mode4 = new QPushButton(Dialog);
        mode4->setObjectName("mode4");
        mode4->setGeometry(QRect(40, 260, 121, 101));
        mode4->setStyleSheet(QString::fromUtf8(""));
        mode5 = new QPushButton(Dialog);
        mode5->setObjectName("mode5");
        mode5->setGeometry(QRect(220, 260, 121, 101));
        mode5->setStyleSheet(QString::fromUtf8("background-color:transparent"));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 200, 121, 31));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(220, 200, 121, 31));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(400, 200, 121, 31));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(40, 360, 121, 31));
        label_6 = new QLabel(Dialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(220, 360, 121, 31));
        frame_1 = new QLabel(Dialog);
        frame_1->setObjectName("frame_1");
        frame_1->setGeometry(QRect(30, 90, 141, 141));
        frame_1->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,1);\n"
"border-radius: 10px;"));
        frame_2 = new QLabel(Dialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(210, 90, 141, 141));
        frame_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-color: rgba(255, 255, 255,1);\n"
"border-radius: 15px;\n"
"}\n"
"QLabel::hover {\n"
"background-color: rgb(240,240,240);\n"
"border-radius: 15px;\n"
"}"));
        frame_3 = new QLabel(Dialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(390, 90, 141, 141));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,1);\n"
"border-radius: 15px;"));
        frame_4 = new QLabel(Dialog);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(30, 250, 141, 141));
        frame_4->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,1);\n"
"border-radius: 15px;"));
        frame_5 = new QLabel(Dialog);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(210, 250, 141, 141));
        frame_5->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,1);\n"
"border-radius: 15px;"));
        icon_1 = new QLabel(Dialog);
        icon_1->setObjectName("icon_1");
        icon_1->setGeometry(QRect(40, 100, 121, 101));
        icon_1->setStyleSheet(QString::fromUtf8("image: url(:/icon/icons/circulate.png);"));
        icon_2 = new QLabel(Dialog);
        icon_2->setObjectName("icon_2");
        icon_2->setGeometry(QRect(220, 100, 121, 101));
        icon_2->setStyleSheet(QString::fromUtf8("image: url(:/icon/icons/constructure.png);"));
        icon_3 = new QLabel(Dialog);
        icon_3->setObjectName("icon_3");
        icon_3->setGeometry(QRect(400, 100, 121, 101));
        icon_3->setStyleSheet(QString::fromUtf8("image: url(:/icon/icons/ER.png);"));
        icon_4 = new QLabel(Dialog);
        icon_4->setObjectName("icon_4");
        icon_4->setGeometry(QRect(40, 260, 121, 101));
        icon_4->setStyleSheet(QString::fromUtf8("image: url(:/icon/icons/time.png);"));
        icon_5 = new QLabel(Dialog);
        icon_5->setObjectName("icon_5");
        icon_5->setGeometry(QRect(220, 260, 121, 101));
        icon_5->setStyleSheet(QString::fromUtf8("image: url(:/icon/icons/zdy.png)"));
        frame_5->raise();
        icon_5->raise();
        frame_4->raise();
        frame_3->raise();
        frame_2->raise();
        frame_1->raise();
        add_mode->raise();
        nothing->raise();
        label->raise();
        mode5->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        label_6->raise();
        icon_1->raise();
        icon_2->raise();
        icon_3->raise();
        icon_4->raise();
        mode1->raise();
        mode2->raise();
        mode3->raise();
        mode4->raise();

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        add_mode->setText(QCoreApplication::translate("Dialog", "\345\257\274\345\205\245\346\250\241\346\235\277", nullptr));
        nothing->setText(QCoreApplication::translate("Dialog", "\346\226\260\345\273\272\347\251\272\347\231\275\346\265\201\347\250\213\345\233\276", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700;\">\350\257\267\351\200\211\346\213\251\346\250\241\346\235\277</span></p></body></html>", nullptr));
        mode1->setText(QString());
        mode2->setText(QString());
        mode3->setText(QString());
        mode4->setText(QString());
        mode5->setText(QString());
        label_2->setText(QCoreApplication::translate("Dialog", "\345\276\252\347\216\257\351\200\273\350\276\221", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "\347\273\223\346\236\204\345\233\276", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "ER\345\233\276", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", "\346\227\266\351\227\264\350\247\204\345\210\222\350\241\250", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog", "\350\207\252\345\256\232\344\271\211\346\250\241\346\235\277", nullptr));
        frame_1->setText(QString());
        frame_2->setText(QString());
        frame_3->setText(QString());
        frame_4->setText(QString());
        frame_5->setText(QString());
        icon_1->setText(QString());
        icon_2->setText(QString());
        icon_3->setText(QString());
        icon_4->setText(QString());
        icon_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
