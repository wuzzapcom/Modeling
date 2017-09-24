#ifndef SPRING_H
#define SPRING_H
#include "drawableobject.h"
#include <QMatrix>
#include <QMatrix4x4>
#include <math.h>
#include <QDebug>
#include <QVector3D>
#include <springableobject.h>

class Spring: public DrawableObject
{
public:
    Spring(Rectangle rect);
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point);
    bool checkCursorInObject(Point point);
    QVector<Point*> rotate(QVector<Point*> points);
    SpringableObject *getFirstSpringable(){return first;}
    SpringableObject *getSecongSpringable(){return second;}
    bool isModelIncompleted();

private:

    Rectangle rectangle;
    float rotateAngle;
    SpringableObject *first;
    SpringableObject *second;
    // add new abstract type springable, matPoint and anchoredPoint are subclasses of it
    // add Springable* first; Springalbe* second;

};

#endif // SPRING_H
