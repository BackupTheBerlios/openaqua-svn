
TARGET = linktest
CONFIG += odababins
include (../../projects.pri)
DESTDIR = .

LIBS = -L../../../lib/
LIBS +=      -ldl -lodaba_zlib 


HEADERS +=
SOURCES += main.cpp