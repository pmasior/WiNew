#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("WiNew");
    a.setApplicationVersion("0.00");
    MainWindow w;
    w.show();
    return a.exec();
}
