#include "materialpoint.h"

MaterialPoint::MaterialPoint(Point c, float r)
    :DrawableObject(),
      center(c),
      radius(r){}

QVector<Point*> MaterialPoint::draw()
{
    qInfo("draw()");
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

void MaterialPoint::move(Point *point)
{

    this->center.x += point->x;
    this->center.y += point->y;

}
