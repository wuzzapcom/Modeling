#ifndef PENDULUM_H
#define PENDULUM_H

#include "stationarypoint.h"

class Pendulum: public DrawableObject
{
public:
    Pendulum(Rectangle rect);

    //DrawableObject methods
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point, void *caller);
    bool checkCursorInObject(Point point);
    bool isModelIncompleted();

    void setSpringableObject(SpringableObject *springable);

private:

    StationaryPoint statPoint;

    SpringableObject *springableObject;

};

#endif // PENDULUM_H
