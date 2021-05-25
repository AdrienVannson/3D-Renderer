QT += core gui widgets

TARGET = 3D-Renderer
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11

SOURCES += \
    image_utility.cpp \
    main.cpp \
    renderer/AccelerationStructure.cpp \
    renderer/Box.cpp \
    renderer/Camera.cpp \
    renderer/Color.cpp \
    renderer/Image.cpp \
    renderer/Light.cpp \
    renderer/Material.cpp \
    renderer/Object.cpp \
    renderer/Ray.cpp \
    renderer/Renderer.cpp \
    renderer/Scene.cpp \
    renderer/Stats.cpp \
    renderer/Vect.cpp \
    renderer/acceleration-structures/Octree.cpp \
    renderer/acceleration-structures/SlowIntersection.cpp \
    renderer/objects/Group.cpp \
    renderer/objects/Parallelogram.cpp \
    renderer/objects/SolidObject.cpp \
    renderer/objects/Sphere.cpp \
    renderer/objects/Triangle.cpp \
    renderer/objects/implicit-objects/ImplicitObject.cpp \
    scenes/monkeys.cpp \
    scenes/profile_picture.cpp \
    scenes/several_lights.cpp \
    scenes/sphere_animation.cpp \
    scenes/sphere_mirror.cpp \
    scenes/sphere_refraction.cpp \
    scenes/spheres_collisions.cpp \
    scenes/teapot.cpp \
    scenes/torus_knot.cpp \
    scenes/waves.cpp

HEADERS += \
    image_utility.hpp \
    renderer/AccelerationStructure.hpp \
    renderer/Box.hpp \
    renderer/Camera.hpp \
    renderer/Color.hpp \
    renderer/Image.hpp \
    renderer/Light.hpp \
    renderer/Material.hpp \
    renderer/Object.hpp \
    renderer/Ray.hpp \
    renderer/Renderer.hpp \
    renderer/Scene.hpp \
    renderer/Stats.hpp \
    renderer/Vect.hpp \
    renderer/acceleration-structures/Octree.hpp \
    renderer/acceleration-structures/SlowIntersection.hpp \
    renderer/objects/Group.hpp \
    renderer/objects/Parallelogram.hpp \
    renderer/objects/SolidObject.hpp \
    renderer/objects/Sphere.hpp \
    renderer/objects/Triangle.hpp \
    renderer/objects/implicit-objects/ImplicitObject.hpp \
    scenes/monkeys.hpp \
    scenes/profile_picture.hpp \
    scenes/several_lights.hpp \
    scenes/sphere_animation.hpp \
    scenes/sphere_mirror.hpp \
    scenes/sphere_refraction.hpp \
    scenes/spheres_collisions.hpp \
    scenes/teapot.hpp \
    scenes/torus_knot.hpp \
    scenes/waves.hpp

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
