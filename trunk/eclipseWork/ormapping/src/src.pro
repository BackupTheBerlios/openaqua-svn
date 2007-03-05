# Diese Datei wurde mit dem qmake-Manager von KDevelop erstellt. 
# ------------------------------------------- 
# Unterordner relativ zum Projektordner: ./src
# Das Target ist eine Anwendung:  ormapping

HEADERS += ormsession.h \
           ormtransaction.h \
           ormexception.h 
SOURCES += ormsession.cpp \
           ormtransaction.cpp \
           ormexception.cpp 
PRECOMPILED_HEADER = all_headers.h
CONFIG *= ormapping_libs
QT += sql
DESTDIR = ../lib
TARGET = ormapping
include (../settings.pri)
