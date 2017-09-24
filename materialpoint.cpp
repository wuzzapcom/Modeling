#include "materialpoint.h"

MaterialPoint::MaterialPoint(Point c, float r)
    :DrawableObject(),
      center(c),
      radius(r),
      connectedSprings(QVector<Spring*>()){

    this->type = MATERIAL_POINT;

}

QVector<Point*> MaterialPoint::draw()
{
    qInfo("MaterialPoint::draw()");
    QVector<Point*> points = QVector<Point*>(this->precision + 1);
    Point *point;
    float angle = 0.0f;
    float deltaAngle = 2 * M_PI / this->precision;

    for(int i = 0; i < precision + 1; i++){

        point = new Point(

                    this->center.x + this->radius * sin(angle),
                    this->center.y + this->radius * cos(angle)

                    );

        points[i] = point;

        angle += deltaAngle;

    }

    return points;
}

void MaterialPoint::move(Point point)
{

    this->center.x += point.x;
    this->center.y += point.y;

}

void MaterialPoint::moveTo(Point point)
{

    this->center.x = point.x;
    this->center.y = point.y;

}

void MaterialPoint::addConnectedSpring(Spring *spring)
{

    this->connectedSprings.append(spring);

}

QVector<Spring*> MaterialPoint::getConnectedSprings()
{

    return this->connectedSprings;

}

bool MaterialPoint::checkCursorInObject(Point point)
{

    return (point.x - center.x) * (point.x - center.x) +
            (point.y - center.y) * (point.y - center.y) < radius * radius;

}


Point MaterialPoint::getContactPoint()
{

    return Point(
                this->center.x,
                this->center.y - this->radius
                );

}

float MaterialPoint::getAngle(){

    return 0.0;

}
