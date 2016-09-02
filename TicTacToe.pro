TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    model/cell.cpp \
    model/field.cpp \
    model/model.cpp \
    viewmodel.cpp \
    ai/wincheck.cpp \
    player_factory.cpp \
    ai/ai_player_random.cpp \
    ai/ai_player_defender.cpp \
    ai/iplayer.cpp \
    ai/ai_player_aggressive.cpp

HEADERS += \
    model/cell.h \
    model/field.h \
    model/model.h \
    model/model_exeptions.h \
    viewmodel.h \
    ai/wincheck.h \
    ai/iplayer.h \
    player_factory.h \
    ai/human_player.h \
    ai/ai_player_random.h \
    ai/ai_player_defender.h \
    ai/ai_player_aggressive.h

RESOURCES += qml.qrc \
    rsrc.qrc

CONFIG += c++11
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

win32 {
    QMAKE_LFLAGS_RELEASE += -static -static-libgcc
}

# Default rules for deployment.
include(deployment.pri)

