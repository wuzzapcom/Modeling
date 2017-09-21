#ifndef SPRING_H
#define SPRING_H
#include "drawableobject.h"

class Spring: public DrawableObject
{
public:
    Spring(Rectangle rect);
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point);
    bool checkCursorInObject(Point point);

private:

    Rectangle rectangle;
    // add new abstract type springable, matPoint and anchoredPoint are subclasses of it
    // add Springable* first; Springalbe* second;

};

#endif // SPRING_H
