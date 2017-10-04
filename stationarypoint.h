#ifndef STATIONARYPOINT_H
#define STATIONARYPOINT_H

#include "spring.h"

class StationaryPoint: public ConnectableObject
{
public:
    StationaryPoint(Rectangle rect);

    //DrawableObject methods
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point, void *caller);
    bool checkCursorInObject(Point point);
    bool isModelIncompleted();

    //ConnectableObject methods
    Point getCenter();
    Point getContactPoint(ConnectableObject *connectable);

private:

    Rectangle rectangle;

};

#endif // STATIONARYPOINT_H
