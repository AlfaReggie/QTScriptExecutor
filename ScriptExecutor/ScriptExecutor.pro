QT += core gui widgets network

CONFIG += c++11 warn_on

TARGET = ScriptExecutor

TAMPLATE = app

SOURCE += \
    main.cpp \
    scriptexecutor.cpp

HEADER += \
    scriptexecutor.h

FORMS += \
    scriptexecutor.ui

HEADERS += \
    scriptcanvas.h

SOURCES += \
    scriptcanvas.cpp
