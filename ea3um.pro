#-------------------------------------------------
#
# Project created by QtCreator 2014-03-24T20:33:32
#
#-------------------------------------------------

QT       += core gui multimedia
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc

INCLUDEPATH += usr/include/opencv2/

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ea3um
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    banner.cpp \
    capturethread.cpp

HEADERS  += mainwindow.h \
    banner.h \
    capturethread.h

FORMS    += mainwindow.ui


linux-* {
    target.path = /usr/sbin
    INSTALLS += target
}

RESOURCES +=
