#include "drawableobject.h"

DrawableObject::DrawableObject()
{

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

}

Rectangle::Rectangle()
{

    this->leftTopPoint = Point();
    this->width = 0.0f;
    this->height = 0.0f;

}

void Rectangle::move(Point point)
{

    this->leftTopPoint.x += point.x;
    this->leftTopPoint.y += point.y;

}

void Rectangle::moveTo(Point point)
{

    this->leftTopPoint.x = point.x;
    this->leftTopPoint.y = point.y;

}
