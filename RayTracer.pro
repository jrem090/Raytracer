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
    source/aabb.cpp \
    source/bvh_node.cpp \
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
    ui/custom_scene_widget.cpp \
    ui/scene_widget.cpp \
    ui/random_scene.cpp \
    ui/custom_scene/custom_item.cpp \
    ui/custom_scene/custom_sphere.cpp

HEADERS  += \
    source/aabb.h \
    source/bvh_node.h \
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
    ui/custom_scene_widget.h \
    ui/scene_widget.h \
    ui/random_scene.h \
    ui/custom_scene/custom_item.h \
    ui/custom_scene/custom_sphere.h

FORMS    += \
    ui/mainwindow.ui \
    ui/custom_scene_widget.ui \
    ui/scene_widget.ui \
    ui/random_scene.ui \
    ui/custom_scene/custom_item.ui \
    ui/custom_scene/custom_sphere.ui

RESOURCES += traceout.ppm
