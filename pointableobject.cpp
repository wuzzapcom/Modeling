#include "drawableinheritor.h"

PointableObject::PointableObject(Rectangle rect)
    :DrawableObject(),
      first(nullptr),
      second(nullptr),
      rectangle(rect),
      angle(0.0f),
      rotatedTopPoint(Point()),
      rotatedBottomPoint(Point()),
      defaultLength(2.0f)
{

}

void PointableObject::updateAngle()
{
    Point p1 = first->getCenter();
    Point p2 = second->getCenter();

    if(fabs(p1.x - p2.x) < std::numeric_limits<float>::epsilon())
    {
        if (p1.y > p2.y)
        {
            this->angle = 0.0f;
            return;
        }else
        {
            this->angle = 180.0f;
            return;
        }
    }else if(fabs(p1.y - p2.y) < std::numeric_limits<float>::epsilon())
    {
        if (p1.x > p2.x)
        {
            this->angle = 90.0f;
            return;
        }else{
            this->angle = 270.0f;
            return;
        }
    }else
    {
        float hypo = hypotf(
                    p1.x - p2.x,
                    p1.y - p2.y
                    );

//        defaultLength = hypo;
//        qInfo() << "Default length of spring: ";
//        qInfo() << defaultLength;

        if (p1.y > p2.y)
            this->angle = 90.0f - acosf((p1.x - p2.x) / hypo) / M_PI * 180;
        else
            this->angle = 90.0f + acosf((p1.x - p2.x) / hypo) / M_PI * 180;
    }

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

    rotatedTopPoint = *points[0];
    rotatedBottomPoint = *points[points.size() - 1];

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

    if (hypotenuse < std::numeric_limits<float>::epsilon())
        return;

    this->rectangle.height = hypotenuse;

}

void PointableObject::update()
{
    if (this->first == nullptr || this->second == nullptr)
        return;

    Point contactPoint = first->getContactPoint(second);

    this->updateAngle();
    this->updateLength();
    this->draw();

    this->moveTo(
                Point(
                    contactPoint.x - (this->rotatedTopPoint.x - this->rectangle.getCenter().x),
                    contactPoint.y - (this->rotatedTopPoint.y - this->rectangle.getCenter().y)
                     )
                );
}

void PointableObject::setFirstConnectable(ConnectableObject *f)
{
    this->first = f;
}

void PointableObject::setSecondConnectable(ConnectableObject *s)
{
    this->second = s;
}









