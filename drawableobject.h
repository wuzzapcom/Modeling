#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H
#include <QVector>
#include <QPoint>

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
    void moveTo(Point point);

};

class DrawableObject
{
public:
    DrawableObject();
    virtual QVector<Point*> draw() = 0;
    virtual void move(Point point) = 0;
    virtual void moveTo(Point point) = 0;
    virtual bool checkCursorInObject(Point point) = 0;

    void setSelected(bool selected){isSelected = selected;}
    bool getSelected(){return isSelected;}

private:

    bool isSelected = false;
};

#endif // DRAWABLEOBJECT_H
