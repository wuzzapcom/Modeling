#ifndef MATERIALPOINT_H
#define MATERIALPOINT_H
#include <QDebug>

class MaterialPoint: public ConnectableObject
{
public:
    MaterialPoint(Point c, double r);
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
    double getSpeedX(){return speedX;}
    double getSpeedY(){return speedY;}
    double getRadius(){return radius;}
    void setSpeedX(double ux){speedX = ux;}
    void setSpeedY(double uy){speedY = uy;}
    void setX(double x){center.x = x;}
    void setY(double y){center.y = y;}

    void setRadius(double r){radius = r;}
    void setWeight(int w){weight = w;}
    int getWeight(){return weight;}
    void setSpeed(double v_x, double v_y){speedX = v_x; speedY = v_y;}

    double getAngularSpeed(){return angularSpeed;}
    void setAngularSpeed(double speed){angularSpeed = speed;}

    //External logic methods
    bool isConnectedToRods();
    //Assume that there is just one rod, so return first;
    PointableObject *getRod();

private:

    Point center;
    double radius;
    int weight;

    double speedX;
    double speedY;
    double angularSpeed;

    int precision = 30;
};

#endif // MATERIALPOINT_H
