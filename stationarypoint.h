#ifndef STATIONARYPOINT_H
#define STATIONARYPOINT_H

#include "spring.h"

class StationaryPoint: public DrawableObject
{
public:
    StationaryPoint(Rectangle rect);

    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point, void *caller);
    bool checkCursorInObject(Point point);
    bool isModelIncompleted();

private:

    Rectangle rectangle;

};

#endif // STATIONARYPOINT_H
