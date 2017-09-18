#include "drawableobject.h"

DrawableObject::DrawableObject()
{

    this->next = nullptr;

}

Point::Point(float new_x, float new_y)
{

    this->x = new_x;
    this->y = new_y;

}
