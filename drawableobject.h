#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H
#include <QVector>

struct Point{

    float x;
    float y;

    Point(float new_x, float new_y);
    Point();

};

struct Rectangle{

    Point leftTopPoint;
    float width;
    float height;

    Rectangle(Point leftTop, float width, float height);
    Rectangle();

    void move(Point point);

};

class DrawableObject
{
public:
    DrawableObject();
    virtual QVector<Point*> draw() = 0;
    virtual void move(Point point) = 0;

    DrawableObject *next;
};

#endif // DRAWABLEOBJECT_H