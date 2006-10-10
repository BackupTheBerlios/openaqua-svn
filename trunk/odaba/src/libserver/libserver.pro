TARGET = odaba_server
CONFIG += odabalibs
include (../projects.pri)
QMAKE_CXXFLAGS += -fpermissive
macx: LIBS += -L../../lib  -lodaba_greta -lodaba_zlib -lodaba_sos

PATH_PREFIX=../opa
include (../opa/opa.pro)
