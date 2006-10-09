
TARGET = odaba_greta
CONFIG += odabalibs
include (../projects.pri)
QMAKE_CXXFLAGS += -fpermissive
macx: INCLUDEPATH+=/usr/include/malloc


# Input
HEADERS += h/config.h h/regexpr2.h h/reimpl2.h h/restack.h h/syntax2.h
SOURCES += qlib/regexpr2.cpp qlib/syntax2.cpp
