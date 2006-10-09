LIBS += -lopenaquaactions
LIBS += -lopenaquaframework 
LIBS += -lopenaquagui 
LIBS += -lopenaquadesignerplugins 
LIBS += -L$(QT4)/plugins/designer
HEADERS = 
SOURCES = main.cpp 
CONFIG  *= coaapps
include (../../xml.pri)

