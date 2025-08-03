QT += core gui widgets network

CONFIG += c++11 warn_on

TARGET = ScriptExecutor

TAMPLATE = app

SOURCE += \
    main.cpp \
    scriptexecutor.cpp

FORMS += \
    scriptexecutor.ui

HEADERS += \
    scriptcanvas.h \
    scriptexecutor.h

SOURCES += \
    scriptcanvas.cpp \
    scriptexecutor.cpp
