#ifndef SPRING_H
#define SPRING_H
#include "drawableobject.h"
#include <QMatrix>
#include <QMatrix4x4>
#include <math.h>
#include <QDebug>
#include <QVector3D>
#include <springableobject.h>

class MaterialPoint;
class DrawableObject;

class Spring: public DrawableObject
{
public:
    Spring(Rectangle rect);
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point, void *caller);
    bool checkCursorInObject(Point point);
    QVector<Point*> rotate(QVector<Point*> points);
    SpringableObject *getFirstSpringable(){return first;}
    SpringableObject *getSecongSpringable(){return second;}
    bool isModelIncompleted();
    void splitWith(MaterialPoint *materialPoint);
    void setFirstObject(SpringableObject *f){first = f;}
    void setSecondObject(SpringableObject *s){second = s;}

private:

    Rectangle rectangle;
    float rotateAngle;
    SpringableObject *first;
    SpringableObject *second;

};

#endif // SPRING_H
