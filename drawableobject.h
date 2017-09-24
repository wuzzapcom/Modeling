#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H
#include <QVector>
#include <QPoint>
#include "spring.h"
#include "materialpoint.h"

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
    int angle;

    Rectangle(Point leftTop, float width, float height);
    Rectangle();

    void move(Point point);
    void moveTo(Point point);
    Point getCenter();

};

enum DrawableType{
    MATERIAL_POINT,
    SPRING,
    NONE
};

class DrawableObject
{
public:
    DrawableObject();
    virtual QVector<Point*> draw() = 0;
    virtual void move(Point point) = 0;
    virtual void moveTo(Point point) = 0;
    virtual bool checkCursorInObject(Point point) = 0;
    virtual bool isModelIncompleted() = 0;

    void setSelected(bool selected){isSelected = selected;}
    bool getSelected(){return isSelected;}

    void setType(DrawableType t){type = t;}
    DrawableType getType(){return type;}

    static bool connectObjects(DrawableObject *first, DrawableObject *second);



private:
    bool isSelected = false;

protected:
    DrawableType type = NONE;
};

#endif // DRAWABLEOBJECT_H
