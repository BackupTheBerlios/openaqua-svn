TARGET = odaba_tool
CONFIG += odabalibs
include (../projects.pri)

# Input
HEADERS += h/cEBbase.h \
           h/iUtilityServices.h \
           h/puti.h \
           h/sClientObject.hpp \
           h/sUtilityServices.h \
           h/sWinODABAService.hpp
SOURCES += qlib/ClientObject.cpp qlib/UtilityServices.cpp
