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
    void moveTo(Point point);
    bool checkCursorInObject(Point point);
    void addConnectedSpring(Spring *spring);
    QVector<Spring*> getConnectedSprings();
    void setRadius(float r){radius = r;}
    void setWeight(int w){weight = w;}

private:
    Point center;
    float radius;
    int speedX;
    int speedY;
    int weight;

    QVector<Spring*> connectedSprings; //add to constructor

    int precision = 30;
};

#endif // MATERIALPOINT_H
