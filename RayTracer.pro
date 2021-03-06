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

SOURCES +=\
    source/helpdialog.cpp \
    source/aabb.cpp \
    source/bvh_node.cpp \
    source/bvhviewer.cpp \
    source/bvhviewerdialog.cpp \
    source/camera.cpp \
    source/main.cpp \
    source/mainwindow.cpp \
    source/moving_sphere.cpp \
    source/perlin.cpp \
    source/ray.cpp \
    source/sphere.cpp \
    source/surface_list.cpp \
    source/utilities.cpp \
    source/vec3.cpp \
    source/plane.cpp \
    source/xy_rect.cpp \
    source/xz_rect.cpp \
    source/yz_rect.cpp \
    source/box.cpp \
    source/transformation.cpp \
    source/raytracer.cpp \
    source/constant_medium.cpp

HEADERS  += \
    source/helpdialog.h \
    source/aabb.h \
    source/bvh_node.h \
    source/bvhviewer.h \
    source/bvhviewerdialog.h \
    source/camera.h \
    source/checker_texture.h \
    source/constant_texture.h \
    source/dielectric.h \
    source/lambertian.h \
    source/mainwindow.h \
    source/material.h \
    source/metal.h \
    source/moving_sphere.h \
    source/noise_texture.h \
    source/perlin.h \
    source/ray.h \
    source/sphere.h \
    source/surface.h \
    source/surface_list.h \
    source/texture.h \
    source/utilities.h \
    source/vec3.h \
    source/image_texture.h \
    source/diffuse_light.h \
    source/plane.h \
    source/xy_rect.h \
    source/xz_rect.h \
    source/yz_rect.h \
    source/flip_normals.h \
    source/box.h \
    source/transformation.h \
    source/raytracer.h \
    source/constant_medium.h \
    source/isotropic.h

FORMS    += \
    ui/helpdialog.ui \
    ui/bvhviewerdialog.ui \
    ui/mainwindow.ui

RESOURCES += traceout.ppm \
    Textures.qrc
