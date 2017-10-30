#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H
#include <QVector>
#include <QPoint>
#include <QJsonObject>
#include <QJsonArray>
#include "rectangle.h"
#include <valarray>

enum DrawableType{
    MATERIAL_POINT,
    SPRING,
    STATIONARY_POINT,
    ROD,
    ARROW,
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
    virtual void moveTo(Point point) = 0;

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

    /*
     * This method writes object to QJsonObject.
     * */
    virtual void write(QJsonObject &json) = 0;

    /*
     * Reading is performed in 2 steps :
     *  1) Init all objects, read hashes.
     *  2) Fill all other fields, like coordinates or pointers.
     * */

    /*
     * First step of reading.
     * */
    virtual void readHash(const QJsonObject &json) = 0;

    /*
     * Second step of reading.
     * */
    virtual void read(const QJsonObject &json, QVector<DrawableObject*> objects) = 0;

    void setSelected(bool selected){isSelected = selected;}
    bool getSelected(){return isSelected;}

    void setType(DrawableType t){type = t;}
    DrawableType getType(){return type;}

    long getHash(){return hash;}
    static long getNextID(){return ID_COUNTER++;}
    static long getCurrentID(){return ID_COUNTER;}
    static long setCurrentID(long id){ID_COUNTER = id;}

private:
    bool isSelected = false;
    static long ID_COUNTER;

protected:
    DrawableType type = NONE;
    long hash = 0;
};

#endif // DRAWABLEOBJECT_H
