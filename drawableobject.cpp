#include "drawableobject.h"

DrawableObject::DrawableObject()
{

}

bool DrawableObject::connectObjects(DrawableObject *first, DrawableObject *second)
{

    Spring *incompletedSpring;
    MaterialPoint *materialPoint;

    if (first->isModelIncompleted()){

        if (first->getType() == SPRING){

            incompletedSpring = (Spring*) first;

        }

        if (second->getType() == MATERIAL_POINT){

            materialPoint = (MaterialPoint*) second;

        }

    }

}

Point::Point(float new_x, float new_y)
{

    this->x = new_x;
    this->y = new_y;

}

Point::Point()
{
    this->x = 0.0f;
    this->y = 0.0f;
}

Rectangle::Rectangle(Point leftTop, float width, float height)
{

    this->leftTopPoint = leftTop;
    this->width = width;
    this->height = height;
    this->angle = 0;

}

Rectangle::Rectangle()
{

    this->leftTopPoint = Point();
    this->width = 0.0f;
    this->height = 0.0f;
    this->angle = 0;

}

void Rectangle::move(Point point)
{

    this->leftTopPoint.x += point.x - this->width / 2;
    this->leftTopPoint.y += point.y + this->height / 2;

}

void Rectangle::moveTo(Point point)
{

    this->leftTopPoint.x = point.x - this->width / 2;
    this->leftTopPoint.y = point.y + this->height / 2;

}

Point Rectangle::getCenter()
{

    return Point(
                this->leftTopPoint.x + this->width / 2,
                this->leftTopPoint.y - this->height / 2
                );

}




