QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    draw/cellcolor.cpp \
    draw/colorengine.cpp \
    draw/colormixer.cpp \
    engine.cpp \
    engine/fluidengine.cpp \
    engine/fluidenginetools.cpp \
    engine/tools.cpp \
    engine/types.cpp \
    gamescreen.cpp \
    gui/infomonitor.cpp \
    main.cpp \
    mainwindow.cpp \
    utils/strnum.cpp

HEADERS += \
    draw/cellcolor.h \
    draw/colorengine.h \
    draw/colormixer.h \
    draw/minmax.h \
    draw/paintflags.h \
    engine.h \
    engine/fluidengine.h \
    engine/fluidenginetools.h \
    engine/tools.h \
    engine/types.h \
    gamescreen.h \
    gui/infomonitor.h \
    mainwindow.h \
    structs/info.h \
    utils/strnum.h

FORMS += \
    mainwindow.ui

LIBS += -lpthread

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
