#ifndef MATERIALPOINT_H
#define MATERIALPOINT_H
#include "drawableobject.h"
#include <math.h>
#include "spring.h"
#include <QDebug>

class MaterialPoint: public DrawableObject
{
public:
    MaterialPoint(Point c, float r);
    QVector<Point*> draw();
    void move(Point point);
    bool checkCursorInObject(Point point);
    void addConnectedSpring(Spring *spring);
    QVector<Spring*> getConnectedSprings();

private:
    Point center;
    float radius;
    int speedX;
    int speedY;

    QVector<Spring*> connectedSprings; //add to constructor

    int precision = 30;
};

#endif // MATERIALPOINT_H
