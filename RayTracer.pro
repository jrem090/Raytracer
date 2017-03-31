#-------------------------------------------------
#
# Project created by QtCreator 2017-03-14T21:44:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RayTracer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vec3.cpp \
    ray.cpp \
    sphere.cpp \
    surface_list.cpp

HEADERS  += mainwindow.h \
    vec3.h \
    ray.h \
    surface.h \
    sphere.h \
    surface_list.h \
    camera.h \
    material.h \
    lambertian.h \
    metal.h \
    dielectric.h

FORMS    += mainwindow.ui

RESOURCES += traceout.ppm
