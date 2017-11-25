#include "drawable_abstract.h"

PointableObject::PointableObject(Rectangle rect)
    :DrawableObject(),
      first(nullptr),
      second(nullptr),
      rotatedTopPoint(Point()),
      rotatedBottomPoint(Point()),
      angle(0.0),
      defaultLength(0.5f),
      rectangle(rect)
{

}

void PointableObject::updateAngle()
{
    Point p1 = first->getCenter();
    Point p2 = second->getCenter();

    if(fabs(p1.x - p2.x) < std::numeric_limits<double>::epsilon())
    {
        if (p1.y > p2.y)
        {
            this->angle = 0.0;
            return;
        }else
        {
            this->angle = 180.0;
            return;
        }
    }else if(fabs(p1.y - p2.y) < std::numeric_limits<double>::epsilon())
    {
        if (p1.x > p2.x)
        {
            this->angle = 90.0;
            return;
        }else{
            this->angle = 270.0;
            return;
        }
    }else
    {
        double hypo = hypotf(
                    p1.x - p2.x,
                    p1.y - p2.y
                    );

//        if (this->type == ROD)
//            defaultLength = hypo;
//        qInfo() << "Default length of spring: ";
//        qInfo() << defaultLength;

//        if (p1.y > p2.y)
//            this->angle = astd::sin((p1.x - p2.x) / hypo) / M_PI * 180;
//        else
//            this->angle = 90 + astd::cos((p1.x - p2.x) / hypo) / M_PI * 180;
        if (p1.y > p2.y)
        {
            if (p1.x > p2.x)
            {
                this->angle = 90 - std::acos((p1.x - p2.x) / hypo) / M_PI * 180;
            }
            else
            {
                this->angle = 270 + std::acos(-(p1.x - p2.x) / hypo) / M_PI * 180;
            }
        }
        else
        {
            if (p1.x > p2.x)
            {
                this->angle = 90 + std::asin(-(p1.y - p2.y) / hypo) / M_PI * 180;
            }
            else
            {
                this->angle = 270 + std::asin((p1.y - p2.y) / hypo) / M_PI * 180;
            }
        }

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

    double hypotenuse = std::sqrt(
               pow(firstContactPoint.x - secondContactPoint.x, 2.0) +
                pow(firstContactPoint.y - secondContactPoint.y, 2.0)
                );

    if (hypotenuse < std::numeric_limits<double>::epsilon())
        return;

    this->rectangle.height = hypotenuse;

}

void PointableObject::update(bool isMovedByUser)
{
    if (this->first == nullptr || this->second == nullptr)
        return;

    Point contactPoint = first->getContactPoint(second);

    this->updateAngle();
    if (this->getType() == SPRING)
        this->updateLength();
    else if (isMovedByUser)
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
    //if (this->getType() == ROD)
    //{
        if (this->getFirstConnectable()->getType() == MATERIAL_POINT && this->getSecondConnectable()->getType() == STATIONARY_POINT)
        {
            ConnectableObject *tmp = this->first;
            this->first = this->second;
            this->second = tmp;
        }
    //}
}









