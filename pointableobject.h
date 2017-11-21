#ifndef POINTABLEOBJECT_H
#define POINTABLEOBJECT_H
#include "drawableobject.h"
#include <math.h>
#include <QMatrix4x4>
#include <QVector3D>

class ConnectableObject;
class MaterialPoint;

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
     * updateLength() - stretches or squeezes PointableObject when
     * ConnectableObjects move away or come together.
     * Updates stored rectangle value.
     * SHOULD BE CALLED AFTER updateAngle()!
     * */
    void updateLength();

    /*
     * Updates all PointableObject parameters:
     *  1) angle
     *  2) length
     *  3) position
     * */
    void update(bool isMovedByUser);

    /*
     * rotate() - rotates given points around rectagle.getCenter() point for
     * stored angle value.
     * */
    QVector<Point*> rotate(QVector<Point*> points);

    /*
     * Getters
     * */
    ConnectableObject *getFirstConnectable(){return first;}
    ConnectableObject *getSecondConnectable(){return second;}

    /*
     * Setters
     * */
    void setFirstConnectable(ConnectableObject *f);
    void setSecondConnectable(ConnectableObject *s);
    void setDefaultLength(float l0){rectangle.height = l0;}//{defaultLength = l0;}
    float getDefaultLength(){return rectangle.height;}//{return defaultLength;}
    void setRestingLength(float l0){restingLength = l0;}
    float getRestingLength(){return restingLength;}

protected:

    ConnectableObject *first;
    ConnectableObject *second;

    /*
     * These 2 points need for connecting spring to Connacteble objects. They are used in splitWith method.
     * Filled in rotate method. It is FIRST AND LAST ELEMENTS OF ARRAY.
     * */
    Point rotatedTopPoint;
    Point rotatedBottomPoint;

    float angle;
    float defaultLength;
    float restingLength = 0.0f;

    Rectangle rectangle;

};

#endif // POINTABLEOBJECT_H
