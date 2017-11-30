#ifndef SPRING_H
#define SPRING_H
#include <QDebug>

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
    double getCurrentLength(){return this->rectangle.height;}
    double getDefaultLength();
    void setRigidity(double r){rigidity = r;}
    double getRigidity(){return rigidity;}

private:

    double rigidity;

    /*
     * Fields from PointableObject:
     *
     * ConnectableObject *first;
     * ConnectableObject *second;
     * Point rotatedTopPoint;
     * Point rotatedBottomPoint;
     * double angle;
     * Rectangle rectangle;
    */

};

#endif // SPRING_H
