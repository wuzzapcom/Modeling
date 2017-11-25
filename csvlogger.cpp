#include "csvlogger.h"

CsvLogger::CsvLogger()
{
}

void CsvLogger::startLogging(int numberOfMatPoints)
{
    time_t timestamp = time(NULL);
    currentOpenedFile.setFileName(QString::number((uintmax_t)timestamp).append(".csv"));
    currentOpenedFile.open(QFile::Append | QFile::Text);

    QTextStream writeStream(&currentOpenedFile);

    for (int i = 0; i < numberOfMatPoints; i++)
    {
        QString varNumber = QString::number(i);
        writeStream << "x_" << varNumber << ", ";
        writeStream << "vx_" << varNumber << ", ";
        writeStream << "y_" << varNumber << ", ";
        writeStream << "vy_" << varNumber << ", ";
        writeStream << "phi_" << varNumber << ", ";
        writeStream << "vphi_" << varNumber << ", ";
    }

    writeStream << "Kinetic energy, PotentionalEnergy\r\n";
}

void CsvLogger::log(std::valarray<float> values, float W, float E)
{
    QTextStream writeStream(&currentOpenedFile);
    for (int i = 0; i < values.size(); i++)
    {
        writeStream << values[i] << ",";
    }
    writeStream << W << ",";
    writeStream << E << "\r\n";
}

void CsvLogger::stopLogging()
{
    currentOpenedFile.close();//close();
}

void CsvLogger::close()
{
    currentOpenedFile.close();
}

void CsvLogger::logLengths(float L0, float x1, float y1, float x2, float y2)
{
    QFile file("lengths.csv");
    file.open(QFile::Append | QFile::Text);

    QTextStream stream(&file);

    stream << L0 << ", ";
    stream << x1 << ", ";
    stream << y1 << ", ";
    stream << x2 << ", ";
    stream << y2 << "\r\n";

    file.close();
}

CsvLogger::~CsvLogger()
{
//    if (currentOpenedFile != nullptr)
//    {
//        close();
//    }
}
