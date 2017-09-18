#include "materialpoint.h"

MaterialPoint::MaterialPoint(Point c, float r)
    :center(c),
      radius(r){}

QVector<Point*> MaterialPoint::draw(){
    return QVector<Point*>(0);
}
