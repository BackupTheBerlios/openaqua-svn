
isEmpty(PATH_PREFIX) {
   message "Configure OXML"
   PATH_PREFIX=.
   TARGET = odaba_oxml
   CONFIG += odabalibs
   include (../projects.pri)
}


HEADERS += $$PATH_PREFIX/h/pOXML.h \
           $$PATH_PREFIX/h/sOXMLBase.hpp \
           $$PATH_PREFIX/h/sXDBHandle.hpp \
           $$PATH_PREFIX/h/sXDictionary.hpp \
           $$PATH_PREFIX/h/sXInti.hpp \
           $$PATH_PREFIX/h/sxml_RootBase.hpp \
           $$PATH_PREFIX/h/sXNode.hpp \
           $$PATH_PREFIX/h/sXRef.hpp


SOURCES += $$PATH_PREFIX/qlib/OXMLBase.cpp \
           $$PATH_PREFIX/qlib/XDBHandle.cpp \
           $$PATH_PREFIX/qlib/XDictionary.cpp \
           $$PATH_PREFIX/qlib/XInti.cpp \
           $$PATH_PREFIX/qlib/xml_RootBase.cpp \
           $$PATH_PREFIX/qlib/XRef.cpp
