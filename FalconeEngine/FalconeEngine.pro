#-------------------------------------------------
#
# Project created by QtCreator 2018-06-04T17:00:30
#
#-------------------------------------------------

QT       -= core gui

TARGET = FalconeEngine
TEMPLATE = lib

DEFINES += FALCONEENGINE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Core/behavior.cpp \
    Core/Component.cpp \
    Core/mathf.cpp \
    Core/Object.cpp \
    Core/rect.cpp \
    Core/Vector2.cpp \
    Core/Vector3.cpp \
    Managers/eventtemplate.cpp \
    Managers/ObjectControl.cpp \
    Managers/rendertemplate.cpp \
    Managers/scenesystemtemplate.cpp \
    Managers/scenetemplate.cpp \
    Managers/soundSystem.cpp \
    Managers/UISystem.cpp \
    Managers/uitemplate.cpp \
    Physics/boxcollider.cpp \
    Physics/collider.cpp \
    Physics/Physics.cpp \
    Physics/polycollider.cpp \
    Physics/rigidbody.cpp \
    Physics/spherecollider.cpp \
    Render/renderspritetemplate.cpp

HEADERS += \
    Core/behavior.h \
    Core/Component.h \
    Core/mathf.h \
    Core/Object.h \
    Core/rect.h \
    Core/Vector2.h \
    Core/Vector3.h \
    Managers/eventtemplate.h \
    Managers/ObjectControl.h \
    Managers/objectcontroltemplate.h \
    Managers/rendertemplate.h \
    Managers/scenesystemtemplate.h \
    Managers/scenetemplate.h \
    Managers/soundSystem.h \
    Managers/UISystem.h \
    Managers/uitemplate.h \
    Physics/boxcollider.h \
    Physics/collider.h \
    Physics/Physics.h \
    Physics/polycollider.h \
    Physics/rigidbody.h \
    Physics/spherecollider.h \
    Render/renderspritetemplate.h \
    Managers/eventdefinitions.h \
    falconeengine.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
