TEMPLATE     = app
target.path  = /usr/sbin
INSTALLS    += target
QT          += qml quick multimedia
CONFIG      += c++11
HEADERS     += settings.h   \
               filter.h
SOURCES     += main.cpp     \
               settings.cpp \
               filter.cpp
RESOURCES   += qml.qrc
INCLUDEPATH += usr/include/opencv2/

LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc

QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)


