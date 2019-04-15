#-------------------------------------------------
#
# Project created by QtCreator 2019-04-01T20:34:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3D-Renderer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        Mainwindow.cpp \
    renderer/Scene.cpp \
    renderer/Camera.cpp \
    renderer/Vect.cpp \
    renderer/Color.cpp \
    renderer/objects/Object.cpp \
    renderer/Ray.cpp \
    renderer/objects/Sphere.cpp \
    renderer/Material.cpp \
    renderer/Light.cpp \
    renderer/objects/Triangle.cpp

HEADERS += \
        Mainwindow.hpp \
    renderer/Scene.hpp \
    renderer/Camera.hpp \
    renderer/Vect.hpp \
    renderer/Color.hpp \
    renderer/objects/Object.hpp \
    renderer/Ray.hpp \
    renderer/objects/Sphere.hpp \
    renderer/Material.hpp \
    renderer/Light.hpp \
    renderer/objects/Triangle.hpp

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
