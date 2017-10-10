#include "drawableobject.h"

long DrawableObject::ID_COUNTER = 0;

DrawableObject::DrawableObject()
{
    this->type = NONE;
    this->hash = DrawableObject::getNextID();
}
