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

    void logLengths(float L0, float x1, float y1, float x2, float y2);

    void startLogging(int numberOfMatPoints);
    void log(std::valarray<float> values, float W, float E);
    void stopLogging();

private:
    void close();

    QFile currentOpenedFile;
};

#endif // CSVLOGGER_H
