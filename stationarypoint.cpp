//#include "stationarypoint.h"
#include "common.h"
StationaryPoint::StationaryPoint(Rectangle rect)
    :ConnectableObject(),
      rectangle(rect)
{

    this->type = STATIONARY_POINT;

}

QVector<Point*> StationaryPoint::draw(){

    QVector<Point*> points = QVector<Point*>(4);

    points[0] = new Point(
                this->rectangle.leftTopPoint.x,
                this->rectangle.leftTopPoint.y
                );
    points[1] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width,
                this->rectangle.leftTopPoint.y
                );
    points[2] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
                this->rectangle.leftTopPoint.y - this->rectangle.height
                );
    points[3] = new Point(
                this->rectangle.leftTopPoint.x,
                this->rectangle.leftTopPoint.y
                );

    return points;

}

void StationaryPoint::move(Point point){

    this->rectangle.move(point);

}

void StationaryPoint::moveTo(Point point, void *caller){

    this->rectangle.moveTo(point);

}

bool StationaryPoint::checkCursorInObject(Point point){

    return (point.x > this->rectangle.leftTopPoint.x) &&
            (point.x < (this->rectangle.leftTopPoint.x + this->rectangle.width)) &&
            (point.y < this->rectangle.leftTopPoint.y) &&
            (point.y > (this->rectangle.leftTopPoint.y - this->rectangle.height));

}

bool StationaryPoint::isModelIncompleted()
{

    return false;

}
