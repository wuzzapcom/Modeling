#ifndef MATERIALPOINT_H
#define MATERIALPOINT_H
//#include "drawableobject.h"
#include <math.h>
//#include "spring.h"
#include "rod.h"
#include <QDebug>
//#include "springableobject.h"
#include "rod.h"

class MaterialPoint: public ConnectableObject
{
public:
    MaterialPoint(Point c, float r);
    MaterialPoint();

    //DrawableObject methods
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point);
    bool checkCursorInObject(Point point);
    bool isModelIncompleted(){return false;}
    void write(QJsonObject &json);
    void readHash(const QJsonObject &json);
    void read(const QJsonObject &json, QVector<DrawableObject*> objects);

    //ConnactableObject methods
    Point getCenter();
    Point getContactPoint(ConnectableObject *connectable);

    //for drawing Arrow
    Point getContactPoint(Point connCenter);

    void setRadius(float r){radius = r;}
    void setWeight(int w){weight = w;}

private:

    Point center;
    float radius;
    int weight;


    int precision = 30;
};

#endif // MATERIALPOINT_H
