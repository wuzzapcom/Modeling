#include "drawableinheritor.h"

PointableObject::PointableObject(Rectangle rect)
    :DrawableObject(),
      first(nullptr),
      second(nullptr),
      rectangle(rect),
      angle(0.0f)
{

}

void PointableObject::updateAngle()
{

    this->angle = 0.0f;

}

QVector<Point*> PointableObject::rotate(QVector<Point *> points)
{

    Point center = this->rectangle.getCenter();

    QMatrix4x4 transformationMatrix;
    QVector3D radiusVector = QVector3D(center.x, center.y, 0.0);

    transformationMatrix.rotate(this->angle, 0.0, 0.0, 1.0);

    for (int i = 0; i < points.length(); i++){

        QVector3D point = QVector3D(points[i]->x, points[i]->y, 0.0);

        point -= radiusVector;
        point = point * transformationMatrix;
        point += radiusVector;

        points[i]->x = point.x();
        points[i]->y = point.y();

    }

    return points;

}

void PointableObject::updateLength()
{

    if (this->first == nullptr || this->second == nullptr)
        return;

    Point firstContactPoint = this->first->getContactPoint(this->second);
    Point secondContactPoint = this->second->getContactPoint(this->first);

    float hypotenuse = sqrtf(
               pow(firstContactPoint.x - secondContactPoint.x, 2.0) +
                pow(firstContactPoint.y - secondContactPoint.y, 2.0)
                );

    this->rectangle.height = hypotenuse;

}










