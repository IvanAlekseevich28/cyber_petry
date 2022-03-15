QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/engine/algs/fluid.cpp \
    core/engine/algs/threads.cpp \
    core/engine/chunkengine.cpp \
    core/engine/mainengine.cpp \
    core/entities/cell.cpp \
    core/entities/field.cpp \
    core/entities/process.cpp \
    core/tools/fieldtools.cpp \
    draw/cellcolor.cpp \
    draw/colorengine.cpp \
    draw/colormixer.cpp \
    draw/fieldcolor.cpp \
    engine.cpp \
    gamescreen.cpp \
    gui/drawsettings.cpp \
    gui/infomonitor.cpp \
    main.cpp \
    mainwindow.cpp \
    utils/strnum.cpp

HEADERS += \
    core/engine/IEngine.h \
    core/engine/algs/alg.h \
    core/engine/algs/threads.h \
    core/engine/algs/types.h \
    core/engine/chunkengine.h \
    core/engine/mainengine.h \
    core/entities/cell.h \
    core/entities/field.h \
    core/entities/point.h \
    core/entities/process.h \
    core/tools/fieldtools.h \
    draw/cellcolor.h \
    draw/colorengine.h \
    draw/colormixer.h \
    draw/fieldcolor.h \
    draw/minmax.h \
    draw/paintflags.h \
    engine.h \
    gamescreen.h \
    gui/drawsettings.h \
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
