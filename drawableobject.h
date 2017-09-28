#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H
#include <QVector>
#include <QPoint>
//#include "spring.h"
//#include "materialpoint.h"
#include "rectangle.h"

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
