

PRECOMPILED_HEADER = ../../gui/inc/CoaAllGui
include (../../xml.pri)
LIBS += -lopenaquaframework -lopenaquagui -lopenaquaactions
HEADERS = letterworkbench.h
SOURCES = main.cpp  letterworkbench.cpp
CONFIG += designer
RESOURCES = oaletter.qrc

