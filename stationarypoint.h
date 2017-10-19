#ifndef STATIONARYPOINT_H
#define STATIONARYPOINT_H

#include "arrow.h"

class StationaryPoint: public ConnectableObject
{
public:
    StationaryPoint(struct Rectangle rect);
    StationaryPoint();

    //DrawableObject methods
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point);
    bool checkCursorInObject(Point point);
    bool isModelIncompleted();
    void write(QJsonObject &json);
    void readHash(const QJsonObject &json);
    void read(const QJsonObject &json, QVector<DrawableObject*> objects);

    //ConnectableObject methods
    Point getCenter();
    Point getContactPoint(ConnectableObject *connectable);

private:

    struct Rectangle rectangle;

};

#endif // STATIONARYPOINT_H
