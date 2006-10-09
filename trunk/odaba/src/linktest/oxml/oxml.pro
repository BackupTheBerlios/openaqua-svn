
TARGET = linktest
CONFIG += odababins
include (../../projects.pri)
DESTDIR = .

LIBS = -L../../../lib/
LIBS +=      -lodaba_oxml -lodaba_opa -lodaba_opi -lodaba_ops -lodaba_functional_model -lodaba_oql -lodaba_sos -ldl -lodaba_zlib -lodaba_greta


HEADERS +=
SOURCES += main.cpp