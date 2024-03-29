#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent, ModelingModel *m)
    :QGLWidget(parent)
    , model(m)
{

}

void OpenGLWidget::initializeGL()
{
    qglClearColor(Qt::white); // заполняем экран белым цветом
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

    this->model->completeModel();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    QColor blackColor(0, 0, 0, 255);
    QColor blueColor(0, 0, 255, 255);
    QColor redColor(255, 0, 0, 255);
    qglColor(blackColor);

    QVector<DrawableObject*> drawableObjects = model->getDrawableObjects();

    if (model->getSpeedVectorArrow() != nullptr && model->getSpeedVectorArrow()->getIsVisible())
        drawableObjects.push_back(model->getSpeedVectorArrow());


    for(int i = 0; i < drawableObjects.length(); i++){

        if (drawableObjects[i]->isModelIncompleted()){

            qglColor(redColor);

        }
        else{

            if (model->getSelectedObject() == drawableObjects[i]){

                    qglColor(blueColor);
                }
        }

        QVector<Point*> points = drawableObjects[i]->draw();

        glBegin(GL_LINE_STRIP);

        for(int j = 0; j < points.length(); j++){

            glVertex2f(points[j]->x, points[j]->y);

        }

        glEnd();

//        if (model->getSelectedObject() == drawableObjects[i])
            qglColor(blackColor);

    }


}
