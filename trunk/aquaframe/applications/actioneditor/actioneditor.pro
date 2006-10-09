PRECOMPILED_HEADER = allcoaheaders.h
LIBS += -lopenaquaframework

HEADERS =   workbench.h \
            mainwindow.h \
            actionmodel.h \
            actiondocument.h
            
            
SOURCES =   main.cpp \   
            workbench.cpp \
            mainwindow.cpp \
            actionmodel.cpp \
            actiondocument.cpp


CONFIG  *= coaapps designer
RESOURCES = actioneditor.qrc

include (../../xml.pri)

