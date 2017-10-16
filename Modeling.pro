#-------------------------------------------------
#
# Project created by QtCreator 2017-09-14T21:17:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += opengl

TARGET = Modeling
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    modelingmodel.cpp \
    openglwidget.cpp \
    drawableobject.cpp \
    materialpoint.cpp \
    spring.cpp \
    point.cpp \
    rectangle.cpp \
    stationarypoint.cpp \
    connectableobject.cpp \
    pointableobject.cpp \
    rod.cpp \
    arrow.cpp

HEADERS += \
        mainwindow.h \
    modelingmodel.h \
    openglwidget.h \
    drawableobject.h \
    materialpoint.h \
    spring.h \
    point.h \
    rectangle.h \
    common.h \
    stationarypoint.h \
    connectableobject.h \
    pointableobject.h \
    rod.h \
    drawableinheritor.h \
    arrow.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    imageresources.qrc
