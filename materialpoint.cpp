#include "common.h"
//#include "materialpoint.h"

MaterialPoint::MaterialPoint(Point c, float r)
    :ConnectableObject(),
      center(c),
      radius(r)
{

    this->type = MATERIAL_POINT;

}

MaterialPoint::MaterialPoint()
    :ConnectableObject(),
      center(Point(0.0f, 0.0f)),
             radius(0.0f)
{
    this->type = MATERIAL_POINT;
}

QVector<Point*> MaterialPoint::draw()
{
    //qInfo("MaterialPoint::draw()");
    QVector<Point*> points = QVector<Point*>(this->precision + 1);
    Point *point;
    float angle = 0.0f;
    float deltaAngle = 2 * M_PI / this->precision;

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

    if(fabs(connCenter.x - this->center.x) < std::numeric_limits<float>::epsilon())
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

    }else if (fabs(connCenter.y - this->center.y) < std::numeric_limits<float>::epsilon())
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

        float hypo = hypotf(
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
    json["hash"] = QString::number(hash);//QJsonValue(hash);
    json["x"] = QJsonValue(center.x);
    json["y"] = center.y;
    json["radius"] = radius;
    json["weight"] = weight;

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
}

void MaterialPoint::read(const QJsonObject &json, QVector<DrawableObject*> objects)
{
    center.x = json["x"].toDouble();
    center.y = json["y"].toDouble();
    radius = json["radius"].toDouble();
    weight = json["weight"].toInt();

    QJsonArray pointables = json["pointables"].toArray();

    for (int i = 0; i < pointables.size(); i++)
    {
        bool ok;
        long loadedHash = pointables.at(i).toString().toLong(&ok);
        for (int j = 0; j < objects.size(); j++)
        {
            if (loadedHash == objects[j]->getHash())
            {
                this->pointableObjects.append((PointableObject*) objects[j]);
            }
        }
    }

}







