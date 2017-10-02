#ifndef SPRINGABLEOBJECT_H
#define SPRINGABLEOBJECT_H

//#include "drawableobject.h"
#include "rectangle.h"

class SpringableObject
{
public:
    SpringableObject();

    virtual float getAngle() = 0;
    virtual Point getContactPoint() = 0;
    virtual void moveContactPoint(Point point, void *caller) = 0;

};

#endif // SPRINGABLEOBJECT_H
