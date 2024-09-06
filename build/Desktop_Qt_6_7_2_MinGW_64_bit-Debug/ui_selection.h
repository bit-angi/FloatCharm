/********************************************************************************
** Form generated from reading UI file 'selection.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTION_H
#define UI_SELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Selection
{
public:

    void setupUi(QWidget *Selection)
    {
        if (Selection->objectName().isEmpty())
            Selection->setObjectName("Selection");
        Selection->resize(369, 193);
        Selection->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);"));

        retranslateUi(Selection);

        QMetaObject::connectSlotsByName(Selection);
    } // setupUi

    void retranslateUi(QWidget *Selection)
    {
        Selection->setWindowTitle(QCoreApplication::translate("Selection", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Selection: public Ui_Selection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTION_H
