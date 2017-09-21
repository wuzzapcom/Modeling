#include "spring.h"

Spring::Spring(Rectangle rect)
    :DrawableObject(),
      rectangle(rect)
{
}

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

    return points;

}

void Spring::move(Point point)
{

    this->rectangle.move(point);

}

bool Spring::checkCursorInObject(Point point){

    return point.x > this->rectangle.leftTopPoint.x &&
            point.x < this->rectangle.leftTopPoint.x + this->rectangle.width &&
            point.y > this->rectangle.leftTopPoint.y &&
            point.y < this->rectangle.leftTopPoint.y + this->rectangle.height;

}
