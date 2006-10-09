PRECOMPILED_HEADER = allcoaheaders.h
LIBS += -lopenaquaframework

HEADERS =   dialog.h testserver.h testthread.h actionmodel.h tcpproxy.h
            
           
SOURCES =   main.cpp dialog.cpp testserver.cpp testthread.cpp actionmodel.cpp tcpproxy.cpp
            

CONFIG  *= coaapps designer

include (../../xml.pri)

