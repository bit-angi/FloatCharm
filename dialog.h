#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void choice1();

    void choice2();

    void choice3();

    void choice4();

    void choice5();


    void choice_nothing();

    void add_mode();


    void on_mode1_clicked();

private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
