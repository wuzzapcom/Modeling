#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"

struct Rectangle{

    Point leftTopPoint;
    float width;
    float height;
    int angle;

    Rectangle(Point leftTop, float width, float height);
    Rectangle();

    void move(Point point);
    void moveTo(Point point);
    Point getCenter();

};

#endif // RECTANGLE_H
