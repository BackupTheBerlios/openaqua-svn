TARGET = odaba_oxml
CONFIG += odabalibs
include (../projects.pri)

HEADERS += h/pOXML.h \
           h/sOXMLBase.hpp \
           h/sXDBHandle.hpp \
           h/sXDictionary.hpp \
           h/sXInti.hpp \
           h/sxml_RootBase.hpp \
           h/sXNode.hpp \
           h/sXRef.hpp
SOURCES += qlib/OXMLBase.cpp \
           qlib/XDBHandle.cpp \
           qlib/XDictionary.cpp \
           qlib/XInti.cpp \
           qlib/xml_RootBase.cpp \
           qlib/XRef.cpp
