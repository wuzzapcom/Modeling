#ifndef CSVLOGGER_H
#define CSVLOGGER_H

#include <valarray>
#include <QDebug>
#include <QFile>
#include <QDateTime>

class CsvLogger
{
public:
    CsvLogger();
    ~CsvLogger();

    void logLengths(double L0, double x1, double y1, double x2, double y2);

    void startLogging(int numberOfMatPoints);
    void log(std::valarray<double> values, double W, double E);
    void stopLogging();

private:
    void close();

    QFile currentOpenedFile;
};

#endif // CSVLOGGER_H
