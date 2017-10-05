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

    //qInfo("Spring::draw()");

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
    this->second = mp;

    Point contactPoint = materialPoint->getContactPoint(mp);
    this->updateAngle();

    qDebug() << "Angle =" << this->angle << "sin(x) =" << sinf(this->angle) << "cos(x) =" << cosf(this->angle);

    qDebug() << "Contact point : x =" << contactPoint.x << "y =" << contactPoint.y;

    float sinus = fabs(sinf(180-this->angle));
    float cosinus = fabs(cosf(180-this->angle));

    if (this->angle > 270 && this->angle < 360)
    {
        sinus *= -1;
    }
    else if (this->angle > 90 && this->angle < 180)
    {
        cosinus *= -1;
    }
    else if (this->angle > 180 && this->angle < 270)
    {
        sinus *= -1;
        cosinus *= -1;
    }

    this->moveTo(
                Point(
                    -(this->rectangle.width * sinus - 2 * contactPoint.x) / 2,
                    -(this->rectangle.width * cosinus - 2 * contactPoint.y) / 2
                    //contactPoint.x, //+ cosf(this->angle) * this->rectangle.width / 2,
                    //contactPoint.y - this->rectangle.height / 2
                    ),
                materialPoint
                );

    this->second = nullptr;

}

