#-------------------------------------------------
#
# Project created by QtCreator 2014-09-23T08:54:57
#
#-------------------------------------------------

QT       += core gui quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lenny
TEMPLATE = app


SOURCES += main.cpp\
        lennygui.cpp \
    lennyparser.cpp

HEADERS  += lennygui.h \
    lennyparser.h

FORMS    += lennygui.ui

OTHER_FILES += \
    lenny-canvas.qml

RESOURCES += \
    resources.qrc
