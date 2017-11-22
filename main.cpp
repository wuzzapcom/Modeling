#include "mainwindow.h"
#include <QApplication>

void clearLogsFile();

int main(int argc, char *argv[])
{
//    clearLogsFile();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

void clearLogsFile()
{
    QFile csv("logs.csv");
    csv.open(QFile::WriteOnly);
    csv.close();
}
