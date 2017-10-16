#include "common.h"

Arrow::Arrow()
    :DrawableObject(),
    rectangle(Rectangle(Point(), 0.1f, 0.2f)),
    cursor(Point()),
    connected(nullptr),
    angle(0.0f),
    isVisible(false),
    rotatedTopPoint(Point()),
    rotatedBottomPoint(Point())
{

}

QVector<Point*> Arrow::draw()
{
    QVector<Point*> points = QVector<Point*>(5);

//    points[0] = new Point(
//                this->rectangle.leftTopPoint.x,
//                this->rectangle.leftTopPoint.y - this->rectangle.height / 4
//                );
//    points[1] = new Point(
//                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
//                this->rectangle.leftTopPoint.y
//                );
//    points[2] = new Point(
//                    this->rectangle.leftTopPoint.x + this->rectangle.width,
//                    this->rectangle.leftTopPoint.y - this->rectangle.height / 4
//                    );
//    points[3] = new Point(
//                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
//                this->rectangle.leftTopPoint.y
//                );
//    points[4] = new Point(
//                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
//                this->rectangle.leftTopPoint.y - this->rectangle.height
//                );
    points[0] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
                this->rectangle.leftTopPoint.y
                );
    points[1] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
                this->rectangle.leftTopPoint.y - this->rectangle.height
                );
    points[2] = new Point(
                this->rectangle.leftTopPoint.x,
                this->rectangle.leftTopPoint.y - this->rectangle.height * 3 / 4
                    );
    points[3] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width / 2,
                this->rectangle.leftTopPoint.y - this->rectangle.height
                );
    points[4] = new Point(
                this->rectangle.leftTopPoint.x + this->rectangle.width,
                this->rectangle.leftTopPoint.y - this->rectangle.height * 3 / 4
                );

    return rotate(points);
}

void Arrow::move(Point point)
{
    this->rectangle.move(point);
}

void Arrow::moveTo(Point point)
{
    this->rectangle.moveTo(point);
}

bool Arrow::checkCursorInObject(Point point)
{
    qWarning() << "Arrow::checkCurcorInObject(). Method should not be implemented";
    return false;
}

bool Arrow::isModelIncompleted()
{
    qWarning() << "Arrow::isModelIncompleted(). Method should not be implemented";
    return true;
}

void Arrow::write(QJsonObject &json)
{
     qWarning() << "Arrow::write(). Method should not be implemented";
}

void Arrow::readHash(const QJsonObject &json)
{
      qWarning() << "Arrow::readHash(). Method should not be implemented";
}

void Arrow::read(const QJsonObject &json, QVector<DrawableObject *> objects)
{
    qWarning() << "Arrow::read(). Method should not be implemented";
}

void Arrow::updateAngle()
{
    Point p1 = connected->getCenter();
    Point p2 = cursor;

    if(fabs(p1.x - p2.x) < std::numeric_limits<float>::epsilon())
    {
        if (p1.y > p2.y)
        {
            this->angle = 0.0f;
            return;
        }else
        {
            this->angle = M_PI;
            return;
        }
    }else if(fabs(p1.y - p2.y) < std::numeric_limits<float>::epsilon())
    {
        if (p1.x > p2.x)
        {
            this->angle = 3 * M_PI / 2;
            return;
        }else{
            this->angle = M_PI / 2;
            return;
        }
    }else
    {
        float hypo = hypotf(
                    p1.x - p2.x,
                    p1.y - p2.y
                    );

        if (p1.y > p2.y)
            this->angle = 90.0f - acosf((p1.x - p2.x) / hypo) / M_PI * 180;
        else
            this->angle = 90.0f + acosf((p1.x - p2.x) / hypo) / M_PI * 180;
    }
}

QVector<Point*> Arrow::rotate(QVector<Point *> points)
{
    Point center = this->rectangle.getCenter();

    QMatrix4x4 transformationMatrix;
    QVector3D radiusVector = QVector3D(center.x, center.y, 0.0);

    transformationMatrix.rotate(this->angle, 0.0, 0.0, 1.0);

    for (int i = 0; i < points.length(); i++){

        QVector3D point = QVector3D(points[i]->x, points[i]->y, 0.0);

        point -= radiusVector;
        point = point * transformationMatrix;
        point += radiusVector;

        points[i]->x = point.x();
        points[i]->y = point.y();

    }

    rotatedTopPoint = *points[0];
    rotatedBottomPoint = *points[points.size() - 2];

    return points;
}

void Arrow::updateLength()
{
    Point firstContactPoint = this->connected->getCenter();//this->connected->getContactPoint(cursor);
    Point secondContactPoint = cursor;

    float hypotenuse = sqrtf(
               pow(firstContactPoint.x - secondContactPoint.x, 2.0) +
                pow(firstContactPoint.y - secondContactPoint.y, 2.0)
                );

    if (hypotenuse < std::numeric_limits<float>::epsilon())
        return;

    this->rectangle.height = hypotenuse;
}

void Arrow::updateState(bool isVis, Point curs)
{
    this->isVisible = isVis;
    this->cursor = curs;
    this->updateAngle();
    this->updateLength();

    this->draw();

    this->moveTo(
                Point(this->connected->getCenter().x - (this->rotatedTopPoint.x - this->rectangle.getCenter().x),
                      this->connected->getCenter().y - (this->rotatedTopPoint.y - this->rectangle.getCenter().y)
                      ));

}
