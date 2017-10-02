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
    STATIONARY_POINT,
    NONE
};

class DrawableObject
{
public:
    DrawableObject();

    /*This methods allows an object to be drawn.
     * Returns QVector<Point*> based on internal presentation ob object.
     * Keep in mind that objects drew by GL_LINE_STRIP in OpenGL.
     * */
    virtual QVector<Point*> draw() = 0;

    /*
     * This method allows an object to be moved.
     * Semantics : this.point += point;
     * */
    virtual void move(Point point) = 0;

    /*
     * This method allows an object to be moved.
     * Semantics : this.point = point;
     * */
    virtual void moveTo(Point point, void *caller) = 0;

    /*
     * This method checks if the point is in object.
     * The method allows an object to be selected and to be moved.
     * */
    virtual bool checkCursorInObject(Point point) = 0;

    /*
     * This method checks if there are objects that are incomplete.
     * If there are such objects the model is wrong, user should fix and finish it.
     * For example, an spring should be connected to other object from both ends.
     * */
    virtual bool isModelIncompleted() = 0;

    void setSelected(bool selected){isSelected = selected;}
    bool getSelected(){return isSelected;}

    void setType(DrawableType t){type = t;}
    DrawableType getType(){return type;}

private:
    bool isSelected = false;

protected:
    DrawableType type = NONE;
};

#endif // DRAWABLEOBJECT_H
