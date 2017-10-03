#ifndef POINTABLEOBJECT_H
#define POINTABLEOBJECT_H
#include "drawableobject.h"
#include <math.h>

class ConnectableObject;

class PointableObject: public DrawableObject
{
public:
    PointableObject(Rectangle rect);

    /*
     * Methods which depends from inheritor
     * */



    /*
     * Common methods for every inheritor
     * */

    /*
     * Counts angle for two connectable object, stored in pointers
     * and updates stored value.
     * SHOULD BE CALLED BEFORE updateLength()!
     * */
    void updateAngle();

    /*
     * rotate() - rotates given points around rectagle.getCenter() point for
     * stored angle value.
     * */
    QVector<Point*> rotate(QVector<Point*> points);

    /*
     * updateLength() - stretches or squeezes PointableObject when
     * ConnectableObjects move away or come together.
     * Updates stored rectangle value.
     * SHOULD BE CALLED AFTER updateAngle()!
     * */
    void updateLength();


private:

    ConnectableObject *first;
    ConnectableObject *second;

    float angle;

    Rectangle rectangle;

};

#endif // POINTABLEOBJECT_H
