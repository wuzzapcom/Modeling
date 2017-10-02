#include "common.h"

Pendulum::Pendulum(Rectangle rect)
    :DrawableObject(),
      statPoint(rect),
      springableObject(nullptr)
{

    this->type = PENDULUM;

}


QVector<Point*> Pendulum::draw()
{
    //DEPENDS FROM StationaryPoint REALISATION

    QVector<Point*> points = this->statPoint.draw();

    points.append(points[2]);

    if(springableObject == nullptr){
        points.append(new Point(
                          points[2]->x,
                          points[2]->y + this->statPoint.rectangle.height
                ));
    }

    return points;

}

void Pendulum::move(Point point)
{

    this->statPoint.move(point);

}

void Pendulum::moveTo(Point point, void *caller)
{

    this->statPoint.moveTo(point, caller);

}

bool Pendulum::checkCursorInObject(Point point)
{

    this->statPoint.checkCursorInObject(point);

}

bool Pendulum::isModelIncompleted()
{

    return springableObject == nullptr;

}

void Pendulum::setSpringableObject(SpringableObject *springable)
{

    this->springableObject = springable;

}
