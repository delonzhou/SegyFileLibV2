#-------------------------------------------------
#
# Project created by QtCreator 2018-03-27T18:34:41
#
#-------------------------------------------------

QT       -= core gui

TARGET = core
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    iheader.cpp \
    iheaderfile.cpp \
    itracefile.cpp \
    itraceheaderfile.cpp \
    loadstrategies.cpp \
    segyheader.cpp \
    segytraceheader.cpp \
    types.cpp \
    utils.cpp

HEADERS += \
    cache.h \
    iheader.h \
    iheaderfile.h \
    itracedatafile.h \
    itracedataheaderfile.h \
    itracefile.h \
    itraceheaderfile.h \
    loadstrategies.h \
    segyfile.h \
    segyheader.h \
    segytraceheader.h \
    types.h \
    utils.h \
    tetraka.h \
    sutraceheader.h \
    sufile.h \
    concurrentsegyfile.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
