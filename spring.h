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

    //DrawableObject methods
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point, void *caller);
    bool checkCursorInObject(Point point);
    bool isModelIncompleted();

    void splitWith(MaterialPoint *materialPoint);

private:

};

#endif // SPRING_H
