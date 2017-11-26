#ifndef POINT_H
#define POINT_H

const double PI = 3.14159265358979;

struct Point{

    double x;
    double y;

    Point(double new_x, double new_y);
    Point();

};

struct Rectangle{

    Point leftTopPoint;
    double width;
    double height;
    int angle;

    Rectangle(Point leftTop, double width, double height);
    Rectangle();

    void move(Point point);
    void moveTo(Point point);
    Point getCenter();

};

#endif // POINT_H
