#include "mainwindow.h"
#include <QApplication>

void clearLogsFile();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
