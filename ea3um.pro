TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    settings.cpp

RESOURCES += qml.qrc

QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    settings.h

linux-* {
    target.path = /usr/sbin
    INSTALLS += target
}
