PRECOMPILED_HEADER = allcoaheaders.h

LIBS += -lopenaquaactions
LIBS += -lopenaquaframework
LIBS += -lopenaquagui

HEADERS =   travelworkbench.h \
            travelmainwindow.h \
            travelmainwindowmodel.h \
            travelmainwindowmodel.h \
            contact/contactwindow.h
            
SOURCES =   main.cpp \   
            travelworkbench.cpp \
            travelmainwindow.cpp \
            travelmainwindowmodel.cpp \
            travelsqlmainwindowmodel.cpp \
            contact/contactwindow.cpp

CONFIG  *= coaapps designer
QT      *= sql

RESOURCES = oatravel.qrc contact/contact.qrc

include (../../xml.pri)

