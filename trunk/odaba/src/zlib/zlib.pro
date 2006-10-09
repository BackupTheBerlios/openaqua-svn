
TARGET = odaba_zlib
CONFIG += odabalibs
include (../projects.pri)

QMAKE_CXXFLAGS += -xc


# Input
HEADERS += h/crc32.h \
           h/deflate.h \
           h/infblock.h \
           h/infcodes.h \
           h/inffast.h \
           h/inffixed.h \
           h/inflate.h \
           h/inftrees.h \
           h/infutil.h \
           h/trees.h \
           h/zconf.h \
           h/zconf.in.h \
           h/zlib.h \
           h/zutil.h
SOURCES += qlib/adler32.cpp \
           qlib/compress.cpp \
           qlib/crc32.cpp \
           qlib/deflate.cpp \
           qlib/gzio.cpp \
           qlib/inffast.cpp \
           qlib/inftrees.cpp \
           qlib/trees.cpp \
           qlib/uncompr.cpp \
           qlib/zutil.cpp

NOTUSED = qlib / infback.cpp \
           qlib/infblock.cpp \
           qlib/infcodes.cpp \
           qlib/infutil.cpp \
           qlib/maketree.cpp \
           qlib/minigzip.cpp \
           qlib/inflate.cpp \
