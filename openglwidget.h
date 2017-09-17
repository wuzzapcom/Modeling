#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include "modelingmodel.h"

class OpenGLWidget: public QGLWidget
{
public:

    OpenGLWidget(QWidget *parent/*, ModelingModel *m*/);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    ModelingModel *model;

};

#endif // OPENGLWIDGET_H
