TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lglut \
        -lGL \
        -lGLU
SOURCES += \
        main.cpp
