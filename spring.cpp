#include "common.h"
//#include "spring.h"

Spring::Spring(Rectangle rect)
    :PointableObject(rect)
{

    this->type = SPRING;

}

// make translation by matrixes
QVector<Point*> Spring::draw()
{

    qInfo("Spring::draw()");

    QVector<Point*> points = QVector<Point*>(10);

    points[0] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
                this->rectangle.leftTopPoint.y
                );

    points[1] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
                this->rectangle.leftTopPoint.y - this->rectangle.height / 10
                );

    for (int i = 2; i < 8; i++){

        float x;

        if (i % 2)
            x = this->rectangle.leftTopPoint.x;
        else
            x = this->rectangle.leftTopPoint.x + this->rectangle.width;

        points[i] = new Point(
                    x,
                    this->rectangle.leftTopPoint.y - i * this->rectangle.height / 10
                    );

    }

    points[8] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
                this->rectangle.leftTopPoint.y - 8 * this->rectangle.height / 10
                );


    points[9] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
                this->rectangle.leftTopPoint.y - this->rectangle.height
                );

    //return points;
    return rotate(points);

}

void Spring::move(Point point)
{

    this->rectangle.move(point);

}

void Spring::moveTo(Point point, void *caller)
{

    this->rectangle.moveTo(point);

//    if (first != nullptr && caller == nullptr && (caller != ((void*) first)))
//        first->moveContactPoint(Point(
//                                    this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
//                                    this->rectangle.leftTopPoint.y
//                                    ), this);


}

bool Spring::checkCursorInObject(Point point)
{

    return (point.x > this->rectangle.leftTopPoint.x) &&
            (point.x < (this->rectangle.leftTopPoint.x + this->rectangle.width)) &&
            (point.y < this->rectangle.leftTopPoint.y) &&
            (point.y > (this->rectangle.leftTopPoint.y - this->rectangle.height));

}

bool Spring::isModelIncompleted(){

    if (this->first == nullptr)
        return true;

//    if(this->second == nullptr)
//        return true;

    return false;

}

void Spring::splitWith(MaterialPoint *materialPoint)
{

    MaterialPoint *mp = new MaterialPoint(Point(0.0f, 0.0f), 0.3f);


    Point contactPoint = materialPoint->getContactPoint(mp);
    qDebug() << "Contact point : x = " << contactPoint.x << ", y = " << contactPoint.y;
    this->moveTo(
                Point(
                    contactPoint.x,// - this->rectangle.width / 2,
                    contactPoint.y - this->rectangle.height / 2), materialPoint);

}

