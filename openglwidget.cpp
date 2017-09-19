#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent, ModelingModel *m)
    :QGLWidget(parent)
    , model(m)
{

    model->addMaterialPoint();
    model->addSpring();

}

void OpenGLWidget::initializeGL()
{
    qglClearColor(Qt::black); // заполняем экран белым цветом
    glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
    glShadeModel(GL_FLAT); // убираем режим сглаживания цветов
    glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // фигуры будут закрашены с обеих сторон
}

void OpenGLWidget::resizeGL(int w, int h)
{

    glViewport(0, 0, w, h); // установка точки обзора
    glMatrixMode(GL_PROJECTION); // установка режима матрицы
    glLoadIdentity(); // загрузка матрицы

}

void OpenGLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана
    glMatrixMode(GL_MODELVIEW); // задаем модельно-видовую матрицу
    glLoadIdentity();           // загрузка единичную матрицу

    QColor halfGreen(0, 128, 0, 255); // устанавливаем цвет квадрата
    qglColor(halfGreen); // задаем цвет

    DrawableObject *object = model->draw();
    QVector<Point*> points;
    qInfo("paintGL");
    if (object == nullptr) qInfo("object is null");
    if (model == nullptr) qInfo("model is null");

    while (object != nullptr){
        glBegin(GL_LINE_STRIP);

        points = object->draw();

        for (int i = 0; i < points.length(); i++){

            glVertex2f(points[i]->x, points[i]->y);

        }


        glEnd();

        object = object->next;
    }

}
