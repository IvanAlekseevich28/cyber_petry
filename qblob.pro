QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    draw/color.cpp \
    engine.cpp \
    engine/fluid.cpp \
    gamescreen.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    common.h \
    draw/color.h \
    engine.h \
    engine/fluid.h \
    gamescreen.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

LIBS += -lpthread

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
