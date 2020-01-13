#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(800, 600);
    w.setObjectName("LW2");
    w.show();
    return a.exec();
}
