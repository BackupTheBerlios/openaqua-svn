
include (../../xml.pri)
LIBS += -lopenaquaframework -lopenaquagui -lopenaquaactions
HEADERS = mainwindow.h
SOURCES = mainwindow.cpp main.cpp 
CONFIG += designer
RESOURCES = oaeditor.qrc

