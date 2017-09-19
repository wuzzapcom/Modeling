#ifndef SPRING_H
#define SPRING_H
#include "drawableobject.h"

class Spring: public DrawableObject
{
public:
    Spring(Rectangle rect);
    QVector<Point*> draw();
    void move(Point point);

private:

    Rectangle rectangle;

};

#endif // SPRING_H
