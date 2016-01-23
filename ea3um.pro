#-------------------------------------------------
#
# Project created by QtCreator 2014-03-24T20:33:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ea3um
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    banner.cpp \
    gpio.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    banner.h \
    gpio.h \
    mythread.h

FORMS    += mainwindow.ui


linux-* {
    target.path = /usr/sbin
    INSTALLS += target
}

RESOURCES +=
