#include "drawable_objects.h"
//#include "materialpoint.h"

//TODO add weight
MaterialPoint::MaterialPoint(Point c, double r)
    :ConnectableObject(),
      center(c),
      radius(r),
      weight(1),
      speedX(0.0),
      speedY(0.0),
      angularSpeed(0.0)
{

    this->type = MATERIAL_POINT;

}

MaterialPoint::MaterialPoint()
    :ConnectableObject(),
             center(Point(0.0, 0.0)),
             radius(0.0),
             weight(1),
             speedX(0.0),
             speedY(0.0),
             angularSpeed(0.0)
{
    this->type = MATERIAL_POINT;
}

QVector<Point*> MaterialPoint::draw()
{
    QVector<Point*> points = QVector<Point*>(this->precision + 1);
    Point *point;
    double angle = 0.0;
    double deltaAngle = 2 * PI / this->precision;

    for(int i = 0; i < precision + 1; i++){

        point = new Point(

                    this->center.x + this->radius * sin(angle),
                    this->center.y + this->radius * cos(angle)

                    );

        points[i] = point;

        angle += deltaAngle;

    }
    return points;
}

void MaterialPoint::move(Point point)
{

    this->center.x += point.x;
    this->center.y += point.y;

}

void MaterialPoint::moveTo(Point point)
{
    this->center.x = point.x;
    this->center.y = point.y;
}

bool MaterialPoint::checkCursorInObject(Point point)
{

    return (point.x - center.x) * (point.x - center.x) +
            (point.y - center.y) * (point.y - center.y) < radius * radius;

}


Point MaterialPoint::getContactPoint(ConnectableObject *connectable)
{
    Point connCenter = connectable->getCenter();

    if(std::abs(connCenter.x - this->center.x) < std::numeric_limits<double>::epsilon())
    {

        if (connCenter.y > this->center.y)
        {
            return Point(
                        this->center.x,
                        this->center.y + this->radius
                        );
        }else
        {
            return Point(
                        this->center.x,
                        this->center.y - this->radius
                        );
        }

    }else if (std::abs(connCenter.y - this->center.y) < std::numeric_limits<double>::epsilon())
    {

        if (connCenter.x > this->center.x)
        {
            return Point(
                        this->center.x + this->radius,
                        this->center.y
                        );
        }else
        {
            return Point(
                        this->center.x - this->radius,
                        this->center.y
                        );
        }

    }else
    {

        double hypo = std::hypot(
                    connCenter.x - this->center.x,
                    connCenter.y - this->center.y
                    );

        return Point(
                    this->center.x + this->radius * (connCenter.x - this->center.x) / hypo,
                    this->center.y + this->radius * (connCenter.y - this->center.y) / hypo
                    );
    }

}

Point MaterialPoint::getCenter()
{

    return this->center;

}

void MaterialPoint::write(QJsonObject &json)
{
    json["hash"] = QString::number(hash);
    json["type"] = static_cast<int>(this->type);
    json["x"] = QJsonValue(center.x);
    json["y"] = center.y;
    json["radius"] = radius;
    json["weight"] = weight;
    json["speedX"] = speedX;
    json["speedY"] = speedY;
    json["angularSpeed"] = angularSpeed;

    QJsonArray pointables;

    for(int i = 0; i < pointableObjects.length(); i++)
    {
        QJsonObject obj;
        obj[QString::number(i)] = QString::number(pointableObjects[i]->getHash());
        pointables.append(obj);
    }

    json["pointables"] = pointables;
}

void MaterialPoint::readHash(const QJsonObject &json)
{
    bool ok;
    hash = json["hash"].toString().toLong(&ok);
    type = static_cast<DrawableType>(json["type"].toInt());
    qDebug() << "readHash()";
    qDebug() << "hash =" << hash;
    qDebug() << "type =" << type;
}

void MaterialPoint::read(const QJsonObject &json, QVector<DrawableObject*> objects)
{
    center.x = json["x"].toDouble();
    center.y = json["y"].toDouble();
    radius = json["radius"].toDouble();
    weight = json["weight"].toInt();
    speedX = json["speedX"].toDouble();
    speedY = json["speedY"].toDouble();
    angularSpeed = json["angularSpeed"].toDouble();

    qDebug() << "read()";
    qDebug() << "x =" << center.x;
    qDebug() << "y =" << center.y;
    qDebug() << "radius =" << radius;
    qDebug() << "weight =" << weight;

    QJsonArray pointables = json["pointables"].toArray();

    for (int i = 0; i < pointables.size(); i++)
    {
        bool ok;
        long loadedHash = pointables[i].toObject()[QString::number(i)].toString().toLong(&ok);
        for (int j = 0; j < objects.size(); j++)
        {
            if (loadedHash == objects[j]->getHash())
            {
                this->pointableObjects.append((PointableObject*) objects[j]);
            }
        }
    }

}

bool MaterialPoint::isConnectedToRods()
{
    for (int i = 0; i < pointableObjects.size(); i++)
    {
        if (pointableObjects[i]->getType() == ROD)
            return true;
    }
    return false;
}

PointableObject *MaterialPoint::getRod()
{
    for (int i = 0; i < pointableObjects.size(); i++)
    {
        if (pointableObjects[i]->getType() == ROD)
            return pointableObjects[i];
    }
    qDebug() << "MaterialPoint::getRod(). Rod not found.";
    return nullptr;
}

MaterialPoint::~MaterialPoint()
{

}





