#ifndef MATERIALPOINT_H
#define MATERIALPOINT_H
#include "drawableobject.h"
#include <math.h>

class MaterialPoint: public DrawableObject
{
public:
    MaterialPoint(Point c, float r);
    QVector<Point*> draw();
    void move(Point *point);

private:
    Point center;
    float radius;
    int speedX;
    int speedY;

    int precision = 30;
};

#endif // MATERIALPOINT_H
