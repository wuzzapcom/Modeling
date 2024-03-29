#include "drawable_objects.h"

Rod::Rod(Rectangle rect)
    :PointableObject(rect)
{
    this->type = ROD;
}

Rod::Rod()
    :PointableObject(Rectangle(Point(0.0, 0.0), 0.0, 0.0))
{
    this->type = ROD;
}

QVector<Point*> Rod::draw()
{
    QVector<Point*> result = QVector<Point*>(2);

    result[0] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
                this->rectangle.leftTopPoint.y
                );
    result[1] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
                this->rectangle.leftTopPoint.y - this->rectangle.height
                );

    return rotate(result);
}

void Rod::move(Point point)
{
    this->rectangle.move(point);
}

void Rod::moveTo(Point point)
{
    this->rectangle.moveTo(point);
}

bool Rod::checkCursorInObject(Point point)
{
    return (point.x > this->rectangle.leftTopPoint.x) &&
            (point.x < (this->rectangle.leftTopPoint.x + this->rectangle.width)) &&
            (point.y < this->rectangle.leftTopPoint.y) &&
            (point.y > (this->rectangle.leftTopPoint.y - this->rectangle.height));
}

bool Rod::isModelIncompleted()
{
    return (this->first == nullptr) || (this->second == nullptr);
}

void Rod::write(QJsonObject &json)
{
    json["hash"] = QString::number(hash);
    json["type"] = static_cast<int>(this->type);
    json["x"] = rectangle.leftTopPoint.x;
    json["y"] = rectangle.leftTopPoint.y;
    json["width"] = rectangle.width;
    json["height"] = rectangle.height;
    json["angle"] = angle;
    json["first"] = QString::number(first->getHash());
    json["second"] = QString::number(second->getHash());
}

void Rod::readHash(const QJsonObject &json)
{
    bool ok;
    hash = json["hash"].toString().toLong(&ok);
    type = static_cast<DrawableType>(json["type"].toInt());
    qDebug() << "readHash()";
    qDebug() << "hash =" << hash;
    qDebug() << "type =" << type;
}

void Rod::read(const QJsonObject &json, QVector<DrawableObject *> objects)
{
    rectangle.leftTopPoint.x = json["x"].toDouble();
    rectangle.leftTopPoint.y = json["y"].toDouble();
    rectangle.width = json["width"].toDouble();
    rectangle.height = json["height"].toDouble();
    angle = json["angle"].toDouble();

    bool ok;
    long firstHash = json["first"].toString().toLong(&ok);
    long secondHash = json["second"].toString().toLong(&ok);

    for (int i = 0; i < objects.size(); i++)
    {
        if (firstHash == objects[i]->getHash())
        {
            first = (ConnectableObject*) objects[i];
        }
        if (secondHash == objects[i]->getHash())
        {
            second = (ConnectableObject*)objects[i];
        }
    }
}

double Rod::getDefaultLength()
{
    StationaryPoint *statPoint = nullptr;
    MaterialPoint *matPoint1 = nullptr;
    MaterialPoint *matPoint2 = nullptr;
    if (this->getFirstConnectable()->getType() == STATIONARY_POINT)
    {
        statPoint = (StationaryPoint*) this->getFirstConnectable();
        matPoint1 = (MaterialPoint*) this->getSecondConnectable();
    }
    else if (this->getSecondConnectable()->getType() == STATIONARY_POINT)
    {
        statPoint = (StationaryPoint*) this->getSecondConnectable();
        matPoint1 = (MaterialPoint*) this->getFirstConnectable();
    }
    else
    {
        matPoint1 = (MaterialPoint*) this->getFirstConnectable();
        matPoint2 = (MaterialPoint*) this->getSecondConnectable();
    }

    if (statPoint == nullptr)
    {
        double length1 = this->getRestingLength() + matPoint1->getRadius() + matPoint2->getRadius();
        double length2 = std::hypot(matPoint1->getCenter().x - matPoint2->getCenter().x, matPoint1->getCenter().y - matPoint2->getCenter().y);
        qInfo() << "length1" << length1;
        qInfo() << "length2" << length2;
        return length2;
    }else
    {
        double length1 = this->getRestingLength() + matPoint1->getRadius();
        double length2 = std::hypot(matPoint1->getCenter().x - statPoint->getCenter().x, matPoint1->getCenter().y - statPoint->getCenter().y);
        qInfo() << "length1" << length1;
        qInfo() << "length2" << length2;
        return length2;
    }
}

Rod::~Rod()
{

}
