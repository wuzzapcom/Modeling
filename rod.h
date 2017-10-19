#ifndef ROD_H
#define ROD_H

#include "stationarypoint.h"

class Rod: public PointableObject
{
public:
    Rod(struct Rectangle rect);
    Rod();

    //DrawableObject methods
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point);
    bool checkCursorInObject(Point point);
    bool isModelIncompleted();
    void write(QJsonObject &json);
    void readHash(const QJsonObject &json);
    void read(const QJsonObject &json, QVector<DrawableObject*> objects);

private:

    /*
     * Fields from PointableObject:
     *
     * ConnectableObject *first;
     * ConnectableObject *second;
     * Point rotatedTopPoint;
     * Point rotatedBottomPoint;
     * float angle;
     * Rectangle rectangle;
    */


};

#endif // ROD_H
