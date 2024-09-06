#include "floatchatwindow.h"

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    MainWindow m;
    m.show();
    return a.exec();
}
