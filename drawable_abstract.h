#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H
#include <QVector>
#include <QPoint>
#include <QJsonObject>
#include <QJsonArray>
#include "primitives.h"
#include <valarray>
#include <QMatrix4x4>
#include <QVector3D>

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
    static void setCurrentID(long id){ID_COUNTER = id;}

private:
    bool isSelected = false;
    static long ID_COUNTER;

protected:
    DrawableType type = NONE;
    long hash = 0;
};

class PointableObject;

class ConnectableObject: public DrawableObject
{
public:
    ConnectableObject();

    /*
     * Methods which depends from inheritor
     * */
    /*
     * Material point will overload this methods, stationary point will not do this.
     * */
    double getSpeedX(){return 0.0;}
    double getSpeedY(){return 0.0;}

    /*
     * getCenter() - should return center Point of ConnectableObject.
     * For StationaryPoint it will be always the bottom triangle point.
     * For MaterialPoint - center of circle, obviously.
     * Used for counting rotating angle of PointableObject.
     * */
    virtual Point getCenter() = 0;

    /*
     * getContactPoint() - should return connection point of this connectable
     * and and PointableObject.
     * */
    virtual Point getContactPoint(ConnectableObject *connectable) = 0;

    /*
     * Common methods for every inheritor
     * */

    void addPointable(PointableObject *p);

    QVector<PointableObject*> getPointableObjects(){return pointableObjects;}

    void removeFromPointableObjects(PointableObject *p){pointableObjects.removeOne(p);}

protected:

    QVector<PointableObject*> pointableObjects;

};

class PointableObject: public DrawableObject
{
public:
    PointableObject(Rectangle rect);

    /*
     * Methods which depends from inheritor
     * */

    virtual double getDefaultLength() = 0;


    /*
     * Common methods for every inheritor
     * */

    /*
     * Counts angle for two connectable object, stored in pointers
     * and updates stored value.
     * SHOULD BE CALLED BEFORE updateLength()!
     * */
    void updateAngle();

    /*
     * updateLength() - stretches or squeezes PointableObject when
     * ConnectableObjects move away or come together.
     * Updates stored rectangle value.
     * SHOULD BE CALLED AFTER updateAngle()!
     * */
    void updateLength();

    /*
     * Updates all PointableObject parameters:
     *  1) angle
     *  2) length
     *  3) position
     * */
    void update(bool isMovedByUser);

    /*
     * rotate() - rotates given points around rectagle.getCenter() point for
     * stored angle value.
     * */
    QVector<Point*> rotate(QVector<Point*> points);

    /*
     * Getters
     * */
    ConnectableObject *getFirstConnectable(){return first;}
    ConnectableObject *getSecondConnectable(){return second;}
    double getRestingLength(){return restingLength;}

    /*
     * Setters
     * */
    void setFirstConnectable(ConnectableObject *f);
    void setSecondConnectable(ConnectableObject *s);
    void setRestingLength(double l0){restingLength = l0;}

protected:

    ConnectableObject *first;
    ConnectableObject *second;

    /*
     * These 2 points need for connecting spring to Connacteble objects. They are used in splitWith method.
     * Filled in rotate method. It is FIRST AND LAST ELEMENTS OF ARRAY.
     * */
    Point rotatedTopPoint;
    Point rotatedBottomPoint;

    double angle;
    double restingLength = 0.0;

    Rectangle rectangle;

};


#endif // DRAWABLEOBJECT_H
