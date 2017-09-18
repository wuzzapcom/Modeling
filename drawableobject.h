#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H
#include <QVector>

struct Point{

    float x;
    float y;

};

class DrawableObject
{
public:
    DrawableObject();
    virtual QVector<Point*> draw() = 0;
};

#endif // DRAWABLEOBJECT_H
