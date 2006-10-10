
TARGET = linktest
CONFIG += odababins
include (../../projects.pri)
DESTDIR = .

LIBS = -L../../../lib/
LIBS +=  -lodaba_adkctxi  -lodaba_server -lodaba_sos -ldl -lodaba_zlib -lodaba_greta


HEADERS +=
SOURCES += main.cpp