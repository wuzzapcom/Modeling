#ifndef MATERIALPOINT_H
#define MATERIALPOINT_H
//#include "drawableobject.h"
#include <math.h>
//#include "spring.h"
#include "stationarypoint.h"
#include <QDebug>
//#include "springableobject.h"

class MaterialPoint: public DrawableObject, public SpringableObject
{
public:
    MaterialPoint(Point c, float r);

    //DrawableObject methods
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point, void *caller);
    bool checkCursorInObject(Point point);
    bool isModelIncompleted(){return false;}

    //SpringableObject methods
    void moveContactPoint(Point point, void *caller);
    float getAngle();
    Point getContactPoint();

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

    QVector<Spring*> connectedSprings;

    int precision = 30;
};

#endif // MATERIALPOINT_H
