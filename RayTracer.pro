#-------------------------------------------------
#
# Project created by QtCreator 2017-03-14T21:44:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RayTracer
TEMPLATE = app

#VPATH+=./materials ./textures ./surfaces

SOURCES += main.cpp\
        mainwindow.cpp \
    vec3.cpp \
    ray.cpp \
    sphere.cpp \
    surface_list.cpp \
    camera.cpp \
    utilities.cpp \
    moving_sphere.cpp \
    aabb.cpp \
    bvh_node.cpp \
    perlin.cpp

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
    dielectric.h \
    utilities.h \
    moving_sphere.h \
    aabb.h \
    bvh_node.h \
    texture.h \
    constant_texture.h \
    checker_texture.h \
    perlin.h \
    noise_texture.h

FORMS    += mainwindow.ui

RESOURCES += traceout.ppm
