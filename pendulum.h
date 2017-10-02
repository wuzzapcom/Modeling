#ifndef PENDULUM_H
#define PENDULUM_H

#include "stationarypoint.h"

class Pendulum: public DrawableObject
{
public:
    Pendulum();

    //DrawableObject methods
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point, void *caller);
    bool checkCursorInObject(Point point);
    bool isModelIncompleted();

private:

    StationaryPoint statPoint;

};

#endif // PENDULUM_H
