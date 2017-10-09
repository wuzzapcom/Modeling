#ifndef SPRING_H
#define SPRING_H
//#include "drawableobject.h"
#include <QMatrix>
#include <QMatrix4x4>
#include <math.h>
#include <QDebug>
#include <QVector3D>
#include "drawableinheritor.h"

class MaterialPoint;

class Spring: public PointableObject
{
public:
    Spring(Rectangle rect);
    Spring();

    //DrawableObject methods
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point);
    bool checkCursorInObject(Point point);
    bool isModelIncompleted();
    void write(QJsonObject &json);
    void readHash(const QJsonObject &json);
    void read(const QJsonObject &json, QVector<DrawableObject*> objects);

private:

    float rigidity;

    /*
     * Fields from PointableObject:
     *
     * ConnectableObject *first;
     * ConnectableObject *second;
     * float angle;
     * Rectangle rectangle;
    */

};

#endif // SPRING_H
