TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    model/cell.cpp \
    model/field.cpp \
    model/model.cpp \
    viewmodel.cpp \
    ai/wincheck.cpp

HEADERS += \
    model/cell.h \
    model/field.h \
    model/model.h \
    model/model_exeptions.h \
    viewmodel.h \
    ai/wincheck.h \
    ai/ai_exeptions.h

RESOURCES += qml.qrc \
    rsrc.qrc

CONFIG += debug qml_debug c++11
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

