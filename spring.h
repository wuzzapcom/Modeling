#ifndef SPRING_H
#define SPRING_H
//#include "drawableobject.h"
#include <QMatrix>
#include <QMatrix4x4>
#include <math.h>
#include <QDebug>
#include <QVector3D>
#include "drawableinheritor.h"

class MaterialPoint;

class Spring: public PointableObject
{
public:
    Spring(Rectangle rect);
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point, void *caller);
    bool checkCursorInObject(Point point);
    QVector<Point*> rotate(QVector<Point*> points);
    ConnectableObject *getFirstSpringable(){return first;}
    ConnectableObject *getSecongSpringable(){return second;}
    bool isModelIncompleted();
    void splitWith(MaterialPoint *materialPoint);
    void setFirstObject(ConnectableObject *f){first = f;}
    void setSecondObject(ConnectableObject *s){second = s;}

private:

    Rectangle rectangle;
    float rotateAngle;
    ConnectableObject *first;
    ConnectableObject *second;

};

#endif // SPRING_H
