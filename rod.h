#ifndef ROD_H
#define ROD_H

class Rod: public PointableObject
{
public:
    Rod(Rectangle rect);
    Rod();

    double getAngle(){return this->angle;}

    //DrawableObject methods
    QVector<Point*> draw();
    void move(Point point);
    void moveTo(Point point);
    bool checkCursorInObject(Point point);
    bool isModelIncompleted();
    void write(QJsonObject &json);
    void readHash(const QJsonObject &json);
    void read(const QJsonObject &json, QVector<DrawableObject*> objects);
    double getDefaultLength();

private:

    /*
     * Fields from PointableObject:
     *
     * ConnectableObject *first;
     * ConnectableObject *second;
     * Point rotatedTopPoint;
     * Point rotatedBottomPoint;
     * double angle;
     * Rectangle rectangle;
    */


};

#endif // ROD_H
