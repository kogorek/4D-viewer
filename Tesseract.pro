TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    mainloop.cpp \
    linearmath.cpp \
    camera.cpp \
    drawer.cpp

HEADERS += \
    mainloop.h \
    linearmath.h \
    camera.h \
    drawer.h

LIBS += -lSDL2 -lSDL2_ttf
