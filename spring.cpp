#include "spring.h"

Spring::Spring(Rectangle rect)
    :DrawableObject(),
      rectangle(rect)
{
}

QVector<Point*> Spring::draw()
{

    /*
    points := make([]Point, 10)

     points[0] = Point{
      X: spring.Rect.LeftTopPoint.X + spring.Rect.Width/2,
      Y: spring.Rect.LeftTopPoint.Y,
     }

     points[1] = Point{
      X: spring.Rect.LeftTopPoint.X + spring.Rect.Width/2,
      Y: spring.Rect.LeftTopPoint.Y - spring.Rect.Height/10,
     }

     for i := 2; i < 8; i++ {

      var x float32

      if i%2 == 0 {
       x = spring.Rect.LeftTopPoint.X
      } else {
       x = spring.Rect.LeftTopPoint.X + spring.Rect.Width
      }

      points[i] = Point{
       X: x,
       Y: spring.Rect.LeftTopPoint.Y - float32(i)*spring.Rect.Height/10,
      }

     }

     points[8] = Point{
      X: spring.Rect.LeftTopPoint.X + spring.Rect.Width/2,
      Y: spring.Rect.LeftTopPoint.Y - 8*spring.Rect.Height/10,
     }

     points[9] = Point{
      X: spring.Rect.LeftTopPoint.X + spring.Rect.Width/2,
      Y: spring.Rect.LeftTopPoint.Y - spring.Rect.Height,
     }

     return points
    */

}

void Spring::move(Point point)
{

    this->rectangle.move(point);

}
