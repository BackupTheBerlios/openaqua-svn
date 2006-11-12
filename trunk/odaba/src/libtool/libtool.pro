TARGET = odaba_tool
CONFIG += odabalibs
include (../projects.pri)
macx: LIBS += -L../../lib  -lodaba_greta -lodaba_zlib -lodaba_sos
macx: LIBS += -lodaba_server

# Input
HEADERS += h/cEBbase.h \
           h/iUtilityServices.h \
           h/puti.h \
           h/sClientObject.hpp \
           h/sUtilityServices.h \
           h/sWinODABAService.hpp
SOURCES += qlib/ClientObject.cpp qlib/UtilityServices.cpp
