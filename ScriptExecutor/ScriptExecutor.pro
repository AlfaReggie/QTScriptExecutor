QT += core gui widgets network qml

CONFIG += c++11 warn_on

TARGET = ScriptExecutor
TEMPLATE = app

SOURCES += \
    main.cpp \
    scriptcanvaswidget.cpp \
    scriptexecutor.cpp \
    scriptcanvas.cpp

HEADERS += \
    scriptcanvaswidget.h \
    scriptexecutor.h \
    scriptcanvas.h

FORMS += \
    scriptexecutor.ui
