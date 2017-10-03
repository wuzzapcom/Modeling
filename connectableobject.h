#ifndef CONNECTABLEOBJECT_H
#define CONNECTABLEOBJECT_H

#include "drawableobject.h"

class PointableObject;

class ConnectableObject: public DrawableObject
{
public:
    ConnectableObject();

    /*
     * Methods which depends from inheritor
     * */

    /*
     * getCenter() - should return center Point of ConnectableObject.
     * For StationaryPoint it will be always the bottom triangle point.
     * For MaterialPoint - center of circle, obviously.
     * Used for counting rotating angle of PointableObject.
     * */
    virtual Point getCenter() = 0;

    /*
     * getContactPoint() - should return connection point of this connectable
     * and and PointableObject.
     * */
    virtual Point getContactPoint() = 0;


    /*
     * Common methods for every inheritor
     * */
    void addPointable(PointableObject *p);

private:

    QVector<PointableObject*> pointableObjects;

};

#endif // CONNECTABLEOBJECT_H
