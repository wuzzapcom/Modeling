//#include "stationarypoint.h"
#include "common.h"
StationaryPoint::StationaryPoint(Rectangle rect)
    :ConnectableObject(),
      rectangle(rect)
{
    this->type = STATIONARY_POINT;
}

StationaryPoint::StationaryPoint()
    :ConnectableObject(),
      rectangle(Rectangle())
{
    this->type = STATIONARY_POINT;
}

QVector<Point*> StationaryPoint::draw(){

    QVector<Point*> points = QVector<Point*>(4);

    points[0] = new Point(
                this->rectangle.leftTopPoint.x,
                this->rectangle.leftTopPoint.y
                );
    points[1] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width,
                this->rectangle.leftTopPoint.y
                );
    points[2] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
                this->rectangle.leftTopPoint.y - this->rectangle.height
                );
    points[3] = new Point(
                this->rectangle.leftTopPoint.x,
                this->rectangle.leftTopPoint.y
                );

    return points;

}

void StationaryPoint::move(Point point){

    this->rectangle.move(point);

}

void StationaryPoint::moveTo(Point point){

    this->rectangle.moveTo(point);

}

bool StationaryPoint::checkCursorInObject(Point point){

    return (point.x > this->rectangle.leftTopPoint.x) &&
            (point.x < (this->rectangle.leftTopPoint.x + this->rectangle.width)) &&
            (point.y < this->rectangle.leftTopPoint.y) &&
            (point.y > (this->rectangle.leftTopPoint.y - this->rectangle.height));

}

bool StationaryPoint::isModelIncompleted()
{

    return false;

}

Point StationaryPoint::getCenter()
{
    return Point(
            this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
            this->rectangle.leftTopPoint.y - this->rectangle.height
            );
}

Point StationaryPoint::getContactPoint(ConnectableObject *connectable)
{
    return Point(
            this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
            this->rectangle.leftTopPoint.y - this->rectangle.height
            );
}

void StationaryPoint::write(QJsonObject &json)
{
    json["hash"] = QString::number(hash);
    json["type"] = static_cast<int>(this->type);
    json["x"] = rectangle.leftTopPoint.x;
    json["y"] = rectangle.leftTopPoint.y;
    json["width"] = rectangle.width;
    json["height"] = rectangle.height;

    QJsonArray pointables;

    for (int i = 0; i < pointableObjects.size(); i++)
    {
        QJsonObject obj;
        obj[QString::number(i)] = QString::number(pointableObjects[i]->getHash());
        pointables.append(obj);
    }

    json["pointables"] = pointables;

}

void StationaryPoint::readHash(const QJsonObject &json)
{
    bool ok;
    hash = json["hash"].toString().toLong(&ok);
    type = static_cast<DrawableType>(json["type"].toInt());
    qDebug() << "readHash()";
    qDebug() << "hash =" << hash;
    qDebug() << "type =" << type;
}

void StationaryPoint::read(const QJsonObject &json, QVector<DrawableObject *> objects)
{
    rectangle.leftTopPoint.x = json["x"].toDouble();
    rectangle.leftTopPoint.y = json["y"].toDouble();
    rectangle.width = json["width"].toDouble();
    rectangle.height = json["height"].toDouble();

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




