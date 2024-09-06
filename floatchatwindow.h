#ifndef FLOATCHATWINDOW_H
#define FLOATCHATWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class FloatChatWindow;
}
QT_END_NAMESPACE

class FloatChatWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void colorSelected(const QColor &color);
    void colorSelected2(const QColor &color);
    void colorSelected3(const QColor &color);
    void fontselected(const QFont &font);

public:
    FloatChatWindow(QWidget *parent = nullptr);
    ~FloatChatWindow();
    Ui::FloatChatWindow *ui;
    bool isBold = false ;
    bool isItal = false ;
    bool underlined = false ;
    void choice_new();
    void choice_tabOpen(QString Path);
public slots:
    void on_tabWidget_tabCloseRequested(int index);

    void on_pushButton_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_13_clicked();
    void on_checkBox_checkStateChanged(const Qt::CheckState &arg1);
    void on_pushButton_tx_2_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_returnPressed();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_tx_clicked();
    void on_pushButton_tx_3_clicked();
private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);
};
#endif // FLOATCHATWINDOW_H
