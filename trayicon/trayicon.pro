TEMPLATE = app

QT += qml quick widgets xml

CONFIG += c++11

SOURCES += main.cpp \
    model.cpp

RESOURCES += qml.qrc

RC_FILE = trayicon.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    model.h
