#include "primitives.h"

Point::Point(double new_x, double new_y)
{

    this->x = new_x;
    this->y = new_y;

}

Point::Point()
{
    this->x = 0.0;
    this->y = 0.0;
}

Rectangle::Rectangle(Point leftTop, double width, double height)
{

    this->leftTopPoint = leftTop;
    this->width = width;
    this->height = height;
    this->angle = 0;

}

Rectangle::Rectangle()
{

    this->leftTopPoint = Point();
    this->width = 0.0;
    this->height = 0.0;
    this->angle = 0;

}

void Rectangle::move(Point point)
{

    this->leftTopPoint.x += point.x;
    this->leftTopPoint.y += point.y;

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
