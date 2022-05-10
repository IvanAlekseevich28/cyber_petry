TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS+= -lOpenCL

SOURCES += \
        ../engine/mainengine.cpp \
        ../entities/field.cpp \
        main.cpp

HEADERS += \
    ../../common/opencl.h \
    ../../structs/size.h \
    ../engine/mainengine.h \
    ../entities/field.h \
    ../entities/liquids.h
