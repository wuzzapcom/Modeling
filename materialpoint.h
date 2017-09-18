#ifndef MATERIALPOINT_H
#define MATERIALPOINT_H
#include "drawableobject.h"

class MaterialPoint: public DrawableObject
{
public:
    MaterialPoint(Point c, float r);
    QVector<Point*> draw();

private:
    Point center;
    float radius;
    int speedX;
    int speedY;
};

#endif // MATERIALPOINT_H
