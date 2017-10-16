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

    void setRadius(float r){radius = r;}
    void setWeight(int w){weight = w;}
    void setSpeed(float v_x, float v_y){speedX = v_x; speedY = v_y;}

private:

    Point center;
    float radius;
    int weight;

    float speedX;
    float speedY;

    int precision = 30;
};

#endif // MATERIALPOINT_H
