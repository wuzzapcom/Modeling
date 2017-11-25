#include "drawable_abstract.h"

ConnectableObject::ConnectableObject()
    :DrawableObject(),
      pointableObjects(QVector<PointableObject*>())
{

}

void ConnectableObject::addPointable(PointableObject *p)
{
    this->pointableObjects.append(p);
}
