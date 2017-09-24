#include "spring.h"

Spring::Spring(Rectangle rect)
    :DrawableObject(),
      rectangle(rect),
      rotateAngle(45.0),
      first(nullptr),
      second(nullptr)
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

void Spring::moveTo(Point point)
{

    this->rectangle.moveTo(point);

}

bool Spring::checkCursorInObject(Point point)
{

    return (point.x > this->rectangle.leftTopPoint.x) &&
            (point.x < (this->rectangle.leftTopPoint.x + this->rectangle.width)) &&
            (point.y < this->rectangle.leftTopPoint.y) &&
            (point.y > (this->rectangle.leftTopPoint.y - this->rectangle.height));

}

QVector<Point*> Spring::rotate(QVector<Point*> points)
{

    this->rotateAngle += 10;

    qDebug() << "Start points";
    for(int i = 0; i < points.length(); i++){
        qDebug() << "x = " << points[i]->x << " y = " << points[i]->y;
    }

    Point center = this->rectangle.getCenter();

    QMatrix4x4 transformationMatrix;
    QVector3D radiusVector = QVector3D(center.x, center.y, 0.0);

    transformationMatrix.rotate(this->rotateAngle, 0.0, 0.0, 1.0);

    for (int i = 0; i < points.length(); i++){

        QVector3D point = QVector3D(points[i]->x, points[i]->y, 0.0);

        point -= radiusVector;
        point = point * transformationMatrix;
        point += radiusVector;

        points[i]->x = point.x();
        points[i]->y = point.y();

    }

    qDebug() << "Changed points";
    for(int i = 0; i < points.length(); i++){
        qDebug() << "x = " << points[i]->x << " y = " << points[i]->y;
    }

    return points;

}

bool Spring::isModelIncompleted(){

    if (this->first == nullptr)
        return true;

//    if(this->second == nullptr)
//        return true;

    return false;

}

