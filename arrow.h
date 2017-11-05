#ifndef ARROW_H
#define ARROW_H

#include "spring.h"

class Arrow: public DrawableObject
{
public:
    Arrow();

    //DrawableObject methods
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point);
    bool checkCursorInObject(Point point);
    bool isModelIncompleted();
    void write(QJsonObject &json);
    void readHash(const QJsonObject &json);
    void read(const QJsonObject &json, QVector<DrawableObject*> objects);
//    std::function<double(std::valarray<double>)> getXAcceleration(const ModelingModel &model){return nullptr;}

    void updateAngle();
    QVector<Point*> rotate(QVector<Point*> points);
    void updateLength();

    void setConnected(MaterialPoint *c){connected = c;}
    void setCursor(Point c){cursor = c;}

    void setIsVisible(bool v){isVisible = v;}
    bool getIsVisible(){return isVisible;}

    std::valarray<float> updateState(bool isVis, Point curs);

private:
    MaterialPoint *connected;
    Point cursor;
    Rectangle rectangle;
    float angle;
    bool isVisible;
    Point rotatedTopPoint;
    Point rotatedBottomPoint;
};

#endif // ARROW_H
