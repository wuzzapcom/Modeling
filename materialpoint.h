#ifndef MATERIALPOINT_H
#define MATERIALPOINT_H
//#include "drawableobject.h"
#include <math.h>
//#include "spring.h"
#include "rod.h"
#include <QDebug>
//#include "springableobject.h"
#include "rod.h"

class MaterialPoint: public ConnectableObject
{
public:
    MaterialPoint(Point c, float r);

    //DrawableObject methods
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point, void *caller);
    bool checkCursorInObject(Point point);
    bool isModelIncompleted(){return false;}

    //ConnactableObject methods
    Point getCenter();
    Point getContactPoint(ConnectableObject *connectable);

    void setRadius(float r){radius = r;}
    void setWeight(int w){weight = w;}



private:

    Point center;
    float radius;
    int weight;


    int precision = 30;
};

#endif // MATERIALPOINT_H
