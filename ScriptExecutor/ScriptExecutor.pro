QT += core gui widgets network qml

CONFIG += c++11 warn_on

TARGET = ScriptExecutor

TAMPLATE = app

FORMS += \
    scriptexecutor.ui

SOURCES += main.cpp \
           scriptcanvas.cpp \
           scriptexecutor.cpp    # ← ДОЛЖНО БЫТЬ!

HEADERS += scriptcanvas.h \
           scriptexecutor.h      # ← ДОЛЖНО БЫТЬ!
